#pragma once
#include <Arduino.h>
#include "sensors/sensors.hpp"
#include "shared-timer.hpp"
#include "sensors/smoothed.hpp"

enum ThresholdSeverity {
    NONE_EXCEEDED,
    LEVEL1_INCREASING,
    LEVEL1_DECREASING,
    LEVEL2
};

constexpr uint8_t ThresholdWindow = 32;

class Thresholds {
public:
    Thresholds(Sensors *sensor, KiwiTimer &timer);
    ThresholdSeverity getSeverity() {
        return severity;
    }
private:
    ThresholdSeverity severity = NONE_EXCEEDED;
    uint8_t windowPosition = 0;
    double window[ThresholdWindow];
    Smoothed<double, 6> co2Smoothed; // double smoothing, take the smoothed value of the last minute

    Sensors *sensor;
    bool measure();
    bool refreshThresholds();
};