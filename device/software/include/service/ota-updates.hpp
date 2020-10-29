#pragma once
#include <Arduino.h>
#include "shared-timer.hpp"
#include "mqtt-connection.hpp"
#include "wifi-connection.hpp"

#define MD5_TEXT_SIZE (32)

class OTAUpdates {
public:
    OTAUpdates(WifiConnection *wifi, MqttConnection *mqtt, KiwiTimer &timer);
private:
    bool checkOta();
    bool reportState();
    MqttConnection *mqtt;
    WifiConnection *wifi;
    char currentSum[MD5_TEXT_SIZE + 1];
};