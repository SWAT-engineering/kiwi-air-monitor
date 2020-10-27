#pragma once
#include <Arduino.h>
#include <ESP8266WiFiMulti.h>
#include "shared-timer.hpp"


class WifiConnection {
public:
    WifiConnection(KiwiTimer &timer);
    bool isConnected() { return connected; }
private:
    bool checkConnections();
    ESP8266WiFiMulti wifi;
    bool connected;
};