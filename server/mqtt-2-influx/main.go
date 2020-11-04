/*
 * Copyright Go-IIoT (https://github.com/goiiot)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package main

import (
	"bytes"
	"errors"
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
	mqttURL     string = "mqtt:1883"
	mqttURLTest string = "localhost:8883"
	mqttRegex   string = "kiwi/([^/]+)/(sensor|state)/([^/]+)"

	influxURL      string = "influxdb:8086"
	influxURLTest  string = "localhost:8086"
	influxDatabase string = "kiwi"
)

var mqttTopics [2]string = [2]string{"kiwi/+/sensor/#", "kiwi/+/state/#"} //  '+' = mac, '#' = measurement \in {Temperatur, Pressure, Humidity, CO2}
var clientData map[string]Client

type sensorData struct {
	kind      string
	clientMac string
	value     string
}

type Config struct {
	Clients []Client `toml:"client"`
}

type Client struct {
	Mac  string                 `toml:"mac"`
	Name string                 `toml:"name"`
	Tags map[string]interface{} `toml:"tags"`
}

func parseMqttMessage(topic string, payload []byte) (sensorData, error) {
	regex, err := regexp.Compile(mqttRegex)
	if err != nil {
		return sensorData{}, err
	}
	return sensorData{regex.FindStringSubmatch(topic)[3], regex.FindStringSubmatch(topic)[1], string(payload)}, nil
}

func loadConfig() error {
	source, err := os.Open("clients.toml")
	if err != nil {
		return err
	}
	config := Config{}
	if err := toml.NewDecoder(source).Decode(&config); err != nil {
		return err
	}
	clientData = make(map[string]Client)
	for _, client := range config.Clients {
		clientData[client.Mac] = client
	}
	return nil
}

func addTags(data sensorData) (string, error) {
	client, found := clientData[data.clientMac]
	if found {
		return fmt.Sprintf("%s,device=\"%s\",name=\"%s\"%s value=%s", data.kind, data.clientMac, client.Name, createKeyValuePairs(client.Tags), data.value), nil
	} else {
		return "", errors.New("No configuration in clients.toml for device with mac " + data.clientMac)
	}
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
		// use RegexRouter for topic routing if not specified
		// will use TextRouter, which will match full text
		libmqtt.WithRouter(libmqtt.NewRegexRouter()),
		libmqtt.WithConnHandleFunc(connHandler),
		libmqtt.WithNetHandleFunc(netHandler),
		libmqtt.WithSubHandleFunc(subHandler),
		libmqtt.WithUnsubHandleFunc(unSubHandler),
		libmqtt.WithPubHandleFunc(pubHandler),
		libmqtt.WithPersistHandleFunc(persistHandler),
	)

	return client, err
}

func connHandler(client libmqtt.Client, server string, code byte, err error) {
	if err != nil {
		log.Printf("connect to server [%v] failed: %v", server, err)
		return
	}

	if code != libmqtt.CodeSuccess {
		log.Printf("connect to server [%v] failed with server code [%v]", server, code)
		return
	}

	// connected
	go func() {
		for _, topic := range mqttTopics {
			client.Subscribe([]*libmqtt.Topic{
				{Name: topic, Qos: libmqtt.Qos0},
			}...)
		}
	}()
}

func netHandler(client libmqtt.Client, server string, err error) {
	if err != nil {
		log.Printf("error happened to connection to server [%v]: %v", server, err)
	}
}

func persistHandler(client libmqtt.Client, packet libmqtt.Packet, err error) {
	if err != nil {
		log.Printf("session persist error: %v", err)
	}
}

func subHandler(client libmqtt.Client, topics []*libmqtt.Topic, err error) {
	if err != nil {
		for _, t := range topics {
			log.Printf("subscribe to topic [%v] failed: %v", t.Name, err)
		}
	} else {
		for _, t := range topics {
			log.Printf("subscribe to topic [%v] succeeded", t.Name)
		}
	}
}

func unSubHandler(client libmqtt.Client, topic []string, err error) {
	if err != nil {
		// handle unsubscribe failure
		for _, t := range topic {
			log.Printf("unsubscribe to topic [%v] failed: %v", t, err)
		}
	} else {
		for _, t := range topic {
			log.Printf("unsubscribe to topic [%v] succeeded", t)
		}
	}
}

func pubHandler(client libmqtt.Client, topic string, err error) {
	if err != nil {
		log.Printf("publish packet to topic [%v] failed: %v", topic, err)
	} else {
		log.Printf("publish packet to topic [%v] succeeded", topic)
	}
}

func main() {
	client, err := createClient()
	if err != nil {
		log.Fatal(err)
	}
	loadConfig()
	client.HandleTopic(".*", func(client libmqtt.Client, topic string, qos libmqtt.QosLevel, msg []byte) {
		data, err := parseMqttMessage(topic, msg)
		if err != nil {
			log.Fatal(err)
		}
		influxLine, err := addTags(data)
		if err != nil {
			log.Fatal(err)
		}
		log.Printf(influxLine)
		resp, err := http.Post("http://"+influxURL+"/write?db="+influxDatabase, "application/json", strings.NewReader(influxLine))
		if err != nil {
			log.Fatal(err)
		}
		resp.Body.Close()
	})

	// connect tcp server
	err = client.ConnectServer(mqttURL)
	if err != nil {
		panic("connection not established")
	}

	client.Wait()
}
