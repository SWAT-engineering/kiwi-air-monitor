#include "service/status.hpp"

Status::Status(MqttConnection *mqtt, KiwiTimer &timer): mqtt(mqtt) {
    timer.every(60*1000, [](void *self) -> bool {
          return static_cast<Status *>(self)->update();
      }, static_cast<void *>(this));
}

bool Status::update() {
    mqtt->publish("state/Active", "true");
    mqtt->publish("state/Memory", ESP.getFreeHeap());
}