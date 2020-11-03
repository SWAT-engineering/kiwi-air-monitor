#include "output/mqtt.hpp"
#include <ESP8266WiFi.h>
#include "user-config.h"

Mqtt::Mqtt(Sensors *sensors, MqttConnection *mqtt, KiwiTimer &timer): sensors{sensors}, mqtt{mqtt} {
#ifdef KIWI_MQTT 
    EVERY(timer, 10*1000, Mqtt, publishAll);
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