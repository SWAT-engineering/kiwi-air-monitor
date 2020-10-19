#pragma once
#include <Arduino.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "sensors/sensors.hpp"

class Mqtt {
public:
    Mqtt(Sensors *sensors);
    unsigned long process(unsigned long tick);
private:
    Sensors *sensors;
    Client *client;
    Adafruit_MQTT_Client *mqtt;
    unsigned long lastTick;
    unsigned long lastPublish;

    bool publish(const char *measurement, double value, unsigned long tick);
    char topicBuffer[64];
    char *measurementName;
    char payloadBuffer[42];
};