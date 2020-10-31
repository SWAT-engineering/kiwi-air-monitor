#include "output/mqtt.hpp"
#include <ESP8266WiFi.h>
#include "user-config.h"

Mqtt::Mqtt(Sensors *sensors, MqttConnection *mqtt, KiwiTimer &timer): sensors{sensors}, mqtt{mqtt} {
#ifdef KIWI_MQTT 
    timer.every(10*1000, [](void * self) -> bool {
          return static_cast<Mqtt *>(self)->publishAll();
      }, static_cast<void *>(this));
#endif
}


bool Mqtt::publishAll() {
    mqtt->publish("sensor/Temperature", sensors->getTemperature());
    mqtt->publish("sensor/Humidity", sensors->getHumidity());
    mqtt->publish("sensor/Pressure", sensors->getPressure());
    mqtt->publish("sensor/CO2", sensors->getCO2());
    if (sensors->hasPresence()) {
        mqtt->publish("sensor/Presence", sensors->getPresence() ? "true" : "false");
    }
    return true;
}