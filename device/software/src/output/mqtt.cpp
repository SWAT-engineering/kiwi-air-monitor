#include "output/mqtt.hpp"
#include <ESP8266WiFi.h>
#include "user-config.h"

Mqtt::Mqtt(Sensors *sensors, KiwiTimer &timer): sensors{sensors} {
    #ifdef KIWI_MQTT 
    #ifdef KIWI_MQTT_SECURE
    client = new WiFiClientSecure();
    // TODO: add cert option
    ((WiFiClientSecure*)client)->setInsecure();
    #else
    client = new WiFiClient();
    #endif
    mqtt = new Adafruit_MQTT_Client(client, KIWI_MQTT_SERVER, KIWI_MQTT_PORT, KIWI_MQTT_USERNAME, KIWI_MQTT_PASSWORD);

    WiFi.persistent(false);
    WiFi.mode(WIFI_STA);
    WiFi.begin(KIWI_WIFI_SSID, KIWI_WIFI_PASSWORD);

    int offset = sprintf(topicBuffer, "kiwi/%s/", WiFi.macAddress().c_str());
    measurementName = &(topicBuffer[offset]);

    timer.every(10*1000, [](void * self) -> bool {
          return static_cast<Mqtt *>(self)->publishAll();
      }, static_cast<void *>(this));
    #endif
}

static bool connect(Adafruit_MQTT_Client *mqtt) {
    if (mqtt->connected()) {
        return true;
    }

    int res = mqtt->connect();
    if (res != 0) {
        Serial.print("Error connecting to mqtt: ");
        Serial.println(mqtt->connectErrorString(res));
        mqtt->disconnect();
        return false;
    }
    return true;
}

void Mqtt::publish(const char *measurement, double value) {
    if (isnan(value)) {
        return;
    }
    dtostrf(value, 0, 2, payloadBuffer);
    publish(measurement, payloadBuffer);
}

void Mqtt::publish(const char *measurement, const char* value) {
    strcpy(measurementName, measurement);
    mqtt->publish(topicBuffer, value, 0);
}


bool Mqtt::publishAll() {
    if (WiFi.status() == WL_CONNECTED && connect(mqtt)) {
        publish("sensor/Temperature", sensors->getTemperature());
        publish("sensor/Humidity", sensors->getHumidity());
        publish("sensor/Pressure", sensors->getPressure());
        publish("sensor/CO2", sensors->getCO2());
        if (sensors->hasPresence()) {
            publish("sensor/Presence", sensors->getPresence() ? "true" : "false");
        }
        publish("state/Active", true);
    }
    return true;
}