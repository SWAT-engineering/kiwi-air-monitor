#pragma once
#include <Arduino.h>
#include "EspEasyMHZ19.hpp"

class CO2Sensor {
private:
    EspEasyMHZ19 *hardware;
public:
    CO2Sensor();
    uint16_t measure();
};