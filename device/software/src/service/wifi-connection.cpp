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
    #ifdef KIWI_WIFI_SSID
    wifi.addAP(KIWI_WIFI_SSID, KIWI_WIFI_PASSWORD);
    #endif
    #ifdef KIWI_WIFI_SSID2
    wifi.addAP(KIWI_WIFI_SSID2, KIWI_WIFI_PASSWORD2);
    #endif
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
        Serial.printf("Wifi not connected: %d\n", connectResult);
    }
    return true;
}