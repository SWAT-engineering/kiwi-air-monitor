#include "service/mqtt-connection.hpp"
#include <ESP8266WiFi.h>
#include "user-config.h"
#include <ESP8266WiFiMulti.h>

MqttConnection::MqttConnection(WifiConnection *wifi, KiwiTimer &timer): wifi{wifi} {
#ifdef KIWI_MQTT 
#ifdef KIWI_MQTT_SECURE
    client = new WiFiClientSecure();
    // TODO: add cert option
    ((WiFiClientSecure*)client)->setInsecure();
#else
    client = new WiFiClient();
#endif

    mqtt = new Adafruit_MQTT_Client(client, KIWI_MQTT_SERVER, KIWI_MQTT_PORT, KIWI_MQTT_USERNAME, KIWI_MQTT_PASSWORD);

    int offset = sprintf(topicBuffer, "kiwi/%s/", WiFi.macAddress().c_str());
    measurementName = &(topicBuffer[offset]);

/*
    timer.every(10*1000, [](void * self) -> bool {
          return static_cast<Mqtt *>(self)->publishAll();
      }, static_cast<void *>(this));
      */
#endif
}

static bool connect(Adafruit_MQTT_Client *mqtt) {
    if (mqtt->connected()) {
        return true;
    }

    int res = mqtt->connect();
    if (res != 0) {
        mqtt->disconnect();
        return false;
    }
    return true;
}

bool MqttConnection::publish(const char *measurement, double value) {
    if (isnan(value)) {
        return false;
    }
    dtostrf(value, 0, 2, payloadBuffer);
    return publish(measurement, payloadBuffer);
}

bool MqttConnection::publish(const char *measurement, const char* value) {
    if (wifi->isConnected() && connect(mqtt)) {
        strcpy(measurementName, measurement);
        return mqtt->publish(topicBuffer, value, 0);
    }
    return false;
}