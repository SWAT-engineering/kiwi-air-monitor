#pragma once
#include <Arduino.h>
#include "wifi-connection.hpp"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "shared-timer.hpp"

class MqttConnection {
public:
    MqttConnection(WifiConnection *wifi, KiwiTimer &timer);
    // should be called before the timer is first ticked (so during setup)
    void setWill(const char *subTopic, const char *value);
    // should be called before the timer is first ticked (so during setup)
    bool subscribe(const char *topic, SubscribeCallbackBufferType callback);
    // nan is dropped
    bool publish(const char *subTopic, double value, uint8_t qos = 0);
    // null is dropped
    bool publish(const char *subTopic, const char *value, uint8_t qos = 0);
private:
    Client *client;
    Adafruit_MQTT_Client *mqtt;
    WifiConnection *wifi;
    bool process();

    char topicBuffer[64];
    char *measurementName;
    char payloadBuffer[42];

    char willBuffer[64];
    char willPayload[42];
};