#pragma once
#include <Arduino.h>
#include "sensors/sensors.hpp"
#include "shared-timer.hpp"
#include "sensors/smoothed.hpp"

enum ThresholdSeverity {
    NONE_EXCEEDED,
    LEVEL1,
    LEVEL2
};

class Thresholds {
public:
    Thresholds(Sensors *sensor, KiwiTimer &timer);
    ThresholdSeverity getSeverity() {
        return severity;
    }
private:
    ThresholdSeverity severity = NONE_EXCEEDED;
    Smoothed<double, 18> co2Smoothed; // smoothed value of the last 3 minute

    Sensors *sensor;
    bool measure();
    bool refreshThresholds();
};