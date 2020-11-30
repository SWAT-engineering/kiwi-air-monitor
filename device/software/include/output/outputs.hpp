#pragma once
#include <Arduino.h>
#include "sensors/sensors.hpp"
#include "service/mqtt-connection.hpp"
#include "service/status.hpp"
#include "shared-timer.hpp"
#include "mqtt.hpp"
#include "display.hpp"
#include "led.hpp"
#include "thresholds.hpp"

class Outputs {
public:
    Outputs(Sensors *sensors, MqttConnection *conn, Status *status, KiwiTimer &timer, KiwiTimer *highResTimer);
private:
    Mqtt *mqtt;
    Display *display;
    BreathingLed *led;
    Thresholds *thresholds;
};