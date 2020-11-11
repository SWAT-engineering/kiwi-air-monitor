#include "output/outputs.hpp"

Outputs::Outputs(Sensors *sensors, MqttConnection *conn, KiwiTimer &timer) {
    mqtt = new Mqtt(sensors, conn, timer);
    thresholds = new Thresholds(sensors, timer);
    display = new Display(sensors, timer);
    led = new BreathingLed(thresholds, &timer);
}