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
    connected = wifi.run(KIWI_WIFI_CONNECT_TIME) == WL_CONNECTED;
    if (oldConnected != connected) {
        Serial.printf("Wifi: %d\n", connected);
    }
    return true;
}