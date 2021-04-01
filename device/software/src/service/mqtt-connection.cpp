#include "service/mqtt-connection.hpp"
#include <ESP8266WiFi.h>
#include "user-config.h"
#include <ESP8266WiFiMulti.h>

MqttConnection::MqttConnection(WifiConnection *wifi, KiwiTimer &timer): wifi{wifi} {
#ifdef KIWI_MQTT 
#ifdef KIWI_MQTT_SECURE
    client = new WiFiClientSecure();
    // TODO: add cert option
    ((WiFiClientSecure*)client)->setInsecure();
#else
    client = new WiFiClient();
#endif

    mqtt = new Adafruit_MQTT_Client(client, KIWI_MQTT_SERVER, KIWI_MQTT_PORT, KIWI_MQTT_USERNAME, KIWI_MQTT_PASSWORD);

    int offset = sprintf(topicBuffer, "kiwi/%s/", WiFi.macAddress().c_str());
    measurementName = &(topicBuffer[offset]);

    EVERY(timer, 1000, MqttConnection, process);
#endif
}

void MqttConnection::setWill(const char *subTopic, const char *value) {
#ifdef KIWI_MQTT 
    char *fullMessage = new char[64];
    sprintf(topicBuffer, "kiwi/%s/%s", WiFi.macAddress().c_str(),subTopic);
    mqtt->will(fullMessage, value);
#endif
}

bool MqttConnection::subscribe(const char *topic, SubscribeCallbackBufferType callback) {
#ifdef KIWI_MQTT 
    auto sub = new Adafruit_MQTT_Subscribe(mqtt, topic);
    sub->setCallback(callback);
    return mqtt->subscribe(sub);
#else
    return true;
#endif
}

static bool connect(Adafruit_MQTT_Client *mqtt) {
    if (mqtt->connected()) {
        return true;
    }

    int res = mqtt->connect();
    if (res != 0) {
        Serial.printf("Not connecting to mqtt: %d\n", res);
        mqtt->disconnect();
        return false;
    }
    return true;
}

bool MqttConnection::isConnected() {
    return mqtt->connected();
}

bool MqttConnection::publish(const char *measurement, double value, uint8_t qos) {
    if (isnan(value)) {
        return false;
    }
    dtostrf(value, 0, 2, payloadBuffer);
    return publish(measurement, payloadBuffer, qos);
}

bool MqttConnection::publish(const char *measurement, const char* value, uint8_t qos) {
#ifdef KIWI_MQTT 
    if (wifi->isConnected() && connect(mqtt) && value != nullptr) {
        strcpy(measurementName, measurement);
        return mqtt->publish(topicBuffer, value, qos);
    }
    return false;
#else
    return true;
#endif
}

bool MqttConnection::process() {
    if (wifi->isConnected() && connect(mqtt)) {
        while (true) {
            Adafruit_MQTT_Subscribe *sub = mqtt->readSubscription(100);
            if (sub == nullptr) {
                return true;
            }
            sub->callback_buffer((char *)sub->lastread, sub->datalen);
        }
    }
    return true;
}