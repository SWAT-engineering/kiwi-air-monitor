#pragma once
#include <Arduino.h>
#include "sensors/sensors.hpp"
#include "service/mqtt-connection.hpp"
#include "shared-timer.hpp"

class Mqtt {
public:
    Mqtt(Sensors *sensors, MqttConnection *mqtt, KiwiTimer &timer);
private:
    Sensors *sensors;
    MqttConnection *mqtt;

    bool publishAll();
};