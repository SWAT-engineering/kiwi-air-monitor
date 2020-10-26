#pragma once
#include <Arduino.h>
//#include "MHZ19.h"
#include "EspEasyMHZ19.hpp"
#include <SoftwareSerial.h>

class CO2Sensor {
private:
    EspEasyMHZ19 *hardware;
public:
    CO2Sensor();
    uint16_t measure();
};