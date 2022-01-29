#pragma once
#include <Arduino.h>
#include "shared-timer.hpp"
#include "user-config.h"

#ifndef RCWL_SENSITIVITY
#define RCWL_SENSITIVITY 8
#endif


class Rcwl0516Sensor {
public:
    Rcwl0516Sensor(KiwiTimer &timer);
    bool presenceDetected();
private:
    bool sense();
    unsigned long lastSeen[RCWL_SENSITIVITY];
    size_t seenOffset;
};