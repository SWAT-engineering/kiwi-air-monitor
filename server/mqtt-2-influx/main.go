// SPDX-License-Identifier: GPL-3.0-or-later
// mqtt-2-influx transforms kiwi mqtt messages and annotates them into influxdb
// Copyright (C) 2020  Marie-Saphira Flug
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

package main

import (
	"bytes"
	"crypto/tls"
	"fmt"
	"log"
	"net/http"
	"os"
	"regexp"
	"strings"
	"time"
	"net/url"

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
	mqtt              *url.URL
	influxWriteStatement string
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
	matches := regex.FindStringSubmatch(topic)
	return sensorData{matches[3], matches[1], string(payload)}, nil
}

func loadConfig() error {
	source, err := os.Open("./conf/clients.toml")
	if err != nil {
		return err
	}
	defer source.Close()
	config := Config{}
	if err := toml.NewDecoder(source).Decode(&config); err != nil {
		return err
	}

	mqttURL := "mqtt://mqtt:1883"
	if len(config.Server.MqttAddress) > 0 {
		mqttURL = config.Server.MqttAddress
	} 
	mqtt, err = url.Parse(mqttURL)
	if err != nil {
		return err
	}

	influxURL := "http://influxdb:8086"
	if len(config.Server.InfluxAddress) > 0 {
		influxURL = config.Server.InfluxAddress
	}

	influxWriteStatement = influxURL + "/write?db=" + influxDatabase
	clientData = make(map[string]Client)
	for _, client := range config.Clients {
		clientData[client.Mac] = client
	}
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
			fmt.Fprintf(b, ",%s=\"%s\"", key, strings.Replace(value.(string), "\"", `\"`, -1))
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
	extraOptions := make([]libmqtt.Option, 0)
	if mqtt.Scheme == "mqtts" {
		extraOptions = append(extraOptions,libmqtt.WithCustomTLS(&tls.Config{InsecureSkipVerify: true, ClientAuth: tls.NoClientCert}))
	}
	if mqtt.User != nil {
		pw, _ := mqtt.User.Password()
		extraOptions = append(extraOptions,libmqtt.WithIdentity(mqtt.User.Username(), pw))

	}
	return libmqtt.NewClient(
		// enable keepalive (10s interval) with 20% tolerance
		append(extraOptions,
			libmqtt.WithKeepalive(10, 1.2),
		// enable auto reconnect and set backoff strategy
		libmqtt.WithAutoReconnect(true),
		libmqtt.WithBackoffStrategy(time.Second, 5*time.Second, 1.2),
		libmqtt.WithRouter(libmqtt.NewRegexRouter()),
		)...
	)
}

func main() {
	regex, err := regexp.Compile(mqttRegex)
	if err != nil {
		log.Fatal(err)
	}

	// load config from clients.toml
	err = loadConfig()
	if err != nil {
		log.Fatal(err)
	}

	client, err := createClient()
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
		resp, err := http.Post(influxWriteStatement, "application/json", strings.NewReader(influxLine))
		if err != nil {
			log.Println(err)
			return
		}
		defer resp.Body.Close()
		if resp.StatusCode != 200 {
			log.Println("Error sending to influx: {}", resp.Status)
		}
	})

	// connect tcp server
	// TODO there needs to be a warning when connection didn't work
	err = client.ConnectServer(mqtt.Host)
	if err != nil {
		log.Println(err)
	}
	// subscribe to topics
	topics := make([]*libmqtt.Topic, len(getMqttTopics()))
	for index, topic := range getMqttTopics() {
		topics[index] = &libmqtt.Topic{Name: topic, Qos: libmqtt.Qos0}
	}
	client.Subscribe(topics...)

	log.Println("Registerd MQTT topics, waiting for updates")
	client.Wait()
}
