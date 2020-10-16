#pragma once
#include <Arduino.h>
#include <Wire.h>
//#include "MHZ19.h"                        
//#include <SoftwareSerial.h> 
#include "EspEasyMHZ19.hpp"

class CO2Sensor {
private:
    EspEasyMHZ19 *hardware;
public:
    void begin();
    uint16_t measure();
};