#include "service/wifi-connection.hpp"
#include "user-config.h"


static void addAccessPoints(ESP8266WiFiMulti &wifi);

WifiConnection::WifiConnection(KiwiTimer &timer): connected{false} {
    WiFi.persistent(false);
    WiFi.mode(WIFI_STA);
    addAccessPoints(wifi);
    EVERY(timer, 10*1000, WifiConnection, checkConnections);
}

static void addAccessPoints(ESP8266WiFiMulti &wifi) {
    wifi.addAP(KIWI_WIFI_SSID, KIWI_WIFI_PASSWORD);
}
#ifndef KIWI_WIFI_CONNECT_TIME
#define KIWI_WIFI_CONNECT_TIME 5000
#endif

bool WifiConnection::checkConnections() {
    bool oldConnected = connected;
    wl_status_t connectResult = wifi.run(KIWI_WIFI_CONNECT_TIME);
    connected = connectResult == WL_CONNECTED;
    if (oldConnected != connected) {
        Serial.printf("Wifi: %d\n", connected);
    }
    else if (!connected) {
        Serial.printf("Wifi not conneted: %d\n", connectResult);
    }
    return true;
}