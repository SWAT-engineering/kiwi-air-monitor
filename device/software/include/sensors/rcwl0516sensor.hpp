#pragma once
#include <Arduino.h>
#include "shared-timer.hpp"

class Rcwl0516Sensor {
public:
    Rcwl0516Sensor(KiwiTimer &timer);
    bool presenceDetected();
private:
    bool sense();
    unsigned long lastSeen[8];
    size_t seenOffset;
};