#pragma once
#include <Arduino.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "sensors/sensors.hpp"
#include "shared-timer.hpp"

class Mqtt {
public:
    Mqtt(Sensors *sensors, KiwiTimer &timer);
private:
    Sensors *sensors;
    Client *client;
    Adafruit_MQTT_Client *mqtt;

    bool publishAll();
    void publish(const char *measurement, double value);
    void publish(const char *measurement, const char *value);
    char topicBuffer[64];
    char *measurementName;
    char payloadBuffer[42];
};