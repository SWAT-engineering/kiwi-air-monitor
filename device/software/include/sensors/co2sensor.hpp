#pragma once
#include <Arduino.h>
#include "MHZ19.h"
#include <SoftwareSerial.h>

class CO2Sensor {
private:
    MHZ19 hardware;
    SoftwareSerial *connection;
    void init();
    unsigned long lastReset;
    unsigned int errorCount;
    bool initialized;
    bool isReady();
public:
    CO2Sensor() { init(); }
    uint16_t measure();
};