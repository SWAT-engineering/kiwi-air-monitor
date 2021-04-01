#pragma once
#include <Arduino.h>
#include "wifi-connection.hpp"
#include "mqtt-connection.hpp"
#include "shared-timer.hpp"

class Status {
public:
    Status(WifiConnection *wifi, MqttConnection *mqtt, KiwiTimer &timer);
    bool shouldShowScreen();
    bool wifiConnected();
    bool mqttConnected();

private:
    WifiConnection *wifi;
    MqttConnection *mqtt;
    bool update();
};