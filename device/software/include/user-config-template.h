#ifndef __USER_CONFIG
#define __USER_CONFIG
#include <Arduino.h>

#define KIWI_OTA_UPDATE

#define KIWI_LEVEL1 (800)
#define KIWI_LEVEL2 (1200)

#define KIWI_MQTT

#define KIWI_WIFI_SSID ""
#define KIWI_WIFI_PASSWORD "" // leave empty string if not encrypted wifi

#define KIWI_MQTT_SERVER "" 
#define KIWI_MQTT_PORT 1883
#define KIWI_MQTT_USERNAME "iot" // remove if no auth
#define KIWI_MQTT_PASSWORD "FOwUiwgvorfTVZoCybC4" // remove if no auth
#define KIWI_MQTT_SECURE // remove if no tls enabled

#define KIWI_BME280_SENSOR
#define KIWI_RCWL_SENSOR

#define KIWI_OTA_URL "" // static url 

const uint8_t KIWI_OTA_PUBLIC_KEY[] = { // DER encoded public key as a byte array
};
const size_t KIWI_OTA_PUBLIC_KEY_len = 294;

#endif