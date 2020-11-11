package main

import (
	"bytes"
	"fmt"
	"log"
	"net/http"
	"os"
	"regexp"
	"strings"
	"time"

	"github.com/goiiot/libmqtt"
	"github.com/pelletier/go-toml"
)

const (
	mqttRegex      string = "kiwi/([^/]+)/(sensor|state)/([^/]+)"
	influxDatabase string = "kiwi"
)

func getMqttTopics() []string {
	return []string{"kiwi/+/sensor/#", "kiwi/+/state/#"}
}

var (
	clientData           map[string]Client
	mqttURL              string = "mqtt:1883"
	influxURL            string = "influxdb:8086"
	influxWriteStatement string = "http://" + influxURL + "/write?db=" + influxDatabase
)

type sensorData struct {
	kind      string
	clientMac string
	value     string
}

type Config struct {
	Clients []Client `toml:"client"`
	Server  Server   `toml:"server"`
}

type Client struct {
	Mac  string                 `toml:"mac"`
	Name string                 `toml:"name"`
	Tags map[string]interface{} `toml:"tags"`
}

type Server struct {
	MqttAddress   string `toml:"mqttAddress"`
	InfluxAddress string `toml:"influxAddress"`
}

func parseMqttMessage(topic string, payload []byte, regex *regexp.Regexp) (sensorData, error) {
	return sensorData{regex.FindStringSubmatch(topic)[3], regex.FindStringSubmatch(topic)[1], string(payload)}, nil
}

func loadConfig() error {
	source, err := os.Open("./conf/clients.toml")
	if err != nil {
		return err
	}
	config := Config{}
	if err := toml.NewDecoder(source).Decode(&config); err != nil {
		return err
	}
	if len(config.Server.MqttAddress) > 0 {
		mqttURL = config.Server.MqttAddress
	}
	if len(config.Server.InfluxAddress) > 0 {
		influxURL = config.Server.InfluxAddress
	}
	clientData = make(map[string]Client)
	for _, client := range config.Clients {
		clientData[client.Mac] = client
	}
	defer source.Close()
	return nil
}

func createInfluxLine(data sensorData) string {
	client, found := clientData[data.clientMac]
	if found {
		return fmt.Sprintf("%s,device=\"%s\",name=\"%s\"%s value=%s", data.kind, data.clientMac, client.Name, createKeyValuePairs(client.Tags), data.value)
	}
	return fmt.Sprintf("%s,device=\"%s\" value=%s", data.kind, data.clientMac, data.value)
}

func createKeyValuePairs(m map[string]interface{}) string {
	b := new(bytes.Buffer)
	for key, value := range m {
		switch value.(type) {
		case string:
			fmt.Fprintf(b, ",%s=\"%s\"", key, value)
		case float64:
			fmt.Fprintf(b, ",%s=%.2f", key, value)
		case int64:
			fmt.Fprintf(b, ",%s=%d", key, value)
		default:
			fmt.Fprintf(b, ",%s=\"%s\"", key, value)
		}
	}
	return b.String()
}

func createClient() (libmqtt.Client, error) {
	var (
		client libmqtt.Client
		err    error
	)

	client, err = libmqtt.NewClient(
		// enable keepalive (10s interval) with 20% tolerance
		libmqtt.WithKeepalive(10, 1.2),
		// enable auto reconnect and set backoff strategy
		libmqtt.WithAutoReconnect(true),
		libmqtt.WithBackoffStrategy(time.Second, 5*time.Second, 1.2),
		libmqtt.WithRouter(libmqtt.NewRegexRouter()),
	)

	return client, err
}

func main() {
	client, err := createClient()
	if err != nil {
		log.Fatal(err)
	}

	regex, err := regexp.Compile(mqttRegex)
	if err != nil {
		log.Fatal(err)
	}

	// load config from clients.toml
	err = loadConfig()
	if err != nil {
		log.Fatal(err)
	}

	client.HandleTopic(".*", func(client libmqtt.Client, topic string, qos libmqtt.QosLevel, msg []byte) {
		data, err := parseMqttMessage(topic, msg, regex)
		if err != nil {
			log.Println(err)
			return
		}
		influxLine := createInfluxLine(data)
		log.Printf(influxLine)
		resp, err := http.Post(influxWriteStatement, "application/json", strings.NewReader(influxLine))
		if err != nil {
			log.Println(err)
		}
		resp.Body.Close()
	})

	// connect tcp server
	err = client.ConnectServer(mqttURL)
	if err != nil {
		log.Println(err)
	}

	// subscribe to topics
	topics := make([]*libmqtt.Topic, len(getMqttTopics()))
	for index, topic := range getMqttTopics() {
		topics[index] = &libmqtt.Topic{Name: topic, Qos: libmqtt.Qos0}
	}
	client.Subscribe(topics...)

	client.Wait()
}
