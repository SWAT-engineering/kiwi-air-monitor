#pragma once
#include <Arduino.h>
#include "shared-timer.hpp"
#include "mqtt-connection.hpp"

class OTAUpdates {
public:
    OTAUpdates(KiwiTimer &timer, MqttConnection *mqtt);
private:
    MqttConnection *mqtt;
};