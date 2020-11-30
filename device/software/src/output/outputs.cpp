#include "output/outputs.hpp"

Outputs::Outputs(Sensors *sensors, MqttConnection *conn, Status *status, KiwiTimer &timer, KiwiTimer *highResTimer) {
    mqtt = new Mqtt(sensors, conn, timer);
    thresholds = new Thresholds(sensors, timer);
    display = new Display(sensors, status, timer);
    led = new BreathingLed(thresholds, timer, highResTimer);
}