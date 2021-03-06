#pragma once
#include <Arduino.h>
#include "mqtt-connection.hpp"
#include "shared-timer.hpp"

class Status {
public:
    Status(MqttConnection *mqtt, KiwiTimer &timer);
    bool shouldShowScreen();

private:
    MqttConnection *mqtt;
    bool update();
};