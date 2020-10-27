#pragma once
#include <Arduino.h>
#include "shared-timer.hpp"
#include "mqtt-connection.hpp"
#include "wifi-connection.hpp"

class OTAUpdates {
public:
    OTAUpdates(WifiConnection *wifi, MqttConnection *mqtt, KiwiTimer &timer);
private:
    MqttConnection *mqtt;
    WifiConnection *wifi;
};