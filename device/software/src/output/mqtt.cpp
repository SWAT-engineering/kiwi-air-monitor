#include "output/mqtt.hpp"
#include <ESP8266WiFi.h>
#include "user-config.h"

static const unsigned long tickRate = 10*1000;


Mqtt::Mqtt(Sensors *sensors): sensors{sensors}, lastTick{0} {
    #ifdef KIWI_MQTT 
    #ifdef KIWI_MQTT_SECURE
    client = new WiFiClientSecure();
    // TODO: add cert option
    ((WiFiClientSecure*)client)->setInsecure();
    #else
    client = new WiFiClient();
    #endif
    mqtt = new Adafruit_MQTT_Client(client, KIWI_MQTT_SERVER, KIWI_MQTT_PORT, KIWI_MQTT_USERNAME, KIWI_WIFI_PASSWORD);

    WiFi.persistent(false);
    WiFi.mode(WIFI_STA);
    WiFi.begin(KIWI_WIFI_SSID, KIWI_WIFI_PASSWORD);

    int offset = sprintf(topicBuffer, "kiwi/%s/sensor/", WiFi.macAddress().c_str());
    measurementName = &(topicBuffer[offset]);
    #endif
}

static bool connect(Adafruit_MQTT_Client *mqtt) {
  if (mqtt->connected()) {
    return true;
  }

  if (mqtt->connect() != 0) {
    mqtt->disconnect();
    return false;
  }
  return true;
}

bool Mqtt::publish(const char *measurement, double value, unsigned long tick) {
    if (isnan(value)) {
        return false;
    }
    strcpy(measurementName, measurement);
    dtostrf(value, 0, 2, payloadBuffer);
    if (mqtt->publish(topicBuffer, payloadBuffer, 0)) {
        lastPublish = tick;
        return true;
    }
    return false;
}

unsigned long Mqtt::process(unsigned long tick) {
    #ifdef KIWI_MQTT
    if (tick - lastTick >= tickRate) {
        if (WiFi.status() == WL_CONNECTED && connect(mqtt)) {
            publish("Temperature", sensors->getTemperature(), tick);
            publish("Humidity", sensors->getHumidity(), tick);
            publish("Pressure", sensors->getPressure(), tick);
            publish("CO2", sensors->getCO2(), tick);
            if (tick - lastPublish > 50*1000) {
                mqtt->ping();
                lastPublish = tick;
            }
        }
        lastTick += tickRate;
        return lastTick - tick;
    }
    return tickRate - (tick - lastTick);
    #else
    return 10000;
    #endif
}