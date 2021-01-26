#pragma once
#include <Arduino.h>
#include "MHZ19.h"
#include <SoftwareSerial.h>

class CO2Sensor {
private:
    MHZ19 hardware;
    SoftwareSerial *connection;
    bool initializing;
    unsigned long initializingStarted;
    unsigned int errors;
    void init();
public:
    CO2Sensor();
    uint16_t measure();
};