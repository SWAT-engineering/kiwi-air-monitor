#include "service/status.hpp"

Status::Status(MqttConnection *mqtt, KiwiTimer &timer): mqtt(mqtt) {
    EVERY(timer, 60*1000, Status, update);
}

bool Status::update() {
    mqtt->publish("state/Active", "true");
    mqtt->publish("state/Memory", ESP.getFreeHeap());
    mqtt->publish("state/Voltage", ESP.getVcc() / 1024.0);
}