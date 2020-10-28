#include "service/wifi-connection.hpp"
#include "user-config.h"


static void addAccessPoints(ESP8266WiFiMulti &wifi);

WifiConnection::WifiConnection(KiwiTimer &timer): connected{false} {
    WiFi.persistent(false);
    WiFi.mode(WIFI_STA);
    addAccessPoints(wifi);
    timer.every(10000, [](void *self) -> bool {
        return static_cast<WifiConnection *>(self)->checkConnections();
    }, static_cast<void*>(this));

}

static void addAccessPoints(ESP8266WiFiMulti &wifi) {
    wifi.addAP(KIWI_WIFI_SSID, KIWI_WIFI_PASSWORD);
}
#ifndef KIWI_WIFI_CONNECT_TIME
#define KIWI_WIFI_CONNECT_TIME 5000
#endif

bool WifiConnection::checkConnections() {
    connected = wifi.run(KIWI_WIFI_CONNECT_TIME) == WL_CONNECTED;
    return true;
}