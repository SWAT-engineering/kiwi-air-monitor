#pragma once
#include <Arduino.h>
#include "wifi-connection.hpp"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "shared-timer.hpp"

class MqttConnection {
public:
    MqttConnection(WifiConnection *wifi, KiwiTimer &timer);
    bool publish(const char *measurement, double value);
    bool publish(const char *measurement, const char *value);
private:
    Client *client;
    Adafruit_MQTT_Client *mqtt;
    WifiConnection *wifi;

    char topicBuffer[64];
    char *measurementName;
    char payloadBuffer[42];
};