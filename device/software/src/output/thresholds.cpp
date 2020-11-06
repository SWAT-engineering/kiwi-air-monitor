#include "output/thresholds.hpp"
#include "user-config.h"

Thresholds::Thresholds(Sensors *sensor, KiwiTimer &timer): sensor{sensor} {
    EVERY(timer, 10*1000, Thresholds, measure);
    EVERY(timer, 60*1000, Thresholds, refreshThresholds);
    for (uint_fast8_t i = 0; i < ThresholdWindow; i++) {
        window[i] = 0;
    }
}

bool Thresholds::measure() {
    double co2 = sensor->getCO2();
    if (!isnan(co2)) {
        co2Smoothed.put(co2);
    }
    return true;
}

static double secondHighest(double window[ThresholdWindow]) {
    double max = window[0]; 
    double prevmax = max; 
    for (uint_fast8_t i = 1; i < ThresholdWindow; i++) {
        if (window[i] > max) {
            prevmax = max;
            max = window[i];
        }
    }
    return prevmax;
}

bool Thresholds::refreshThresholds() {
    if (!co2Smoothed.enoughData()) {
        return true;
    }
    double lastCO2 = co2Smoothed.get();
    window[windowPosition] = lastCO2;
    windowPosition = (windowPosition + 1) % ThresholdWindow;
    if (lastCO2 < KIWI_LEVEL1) {
        if (severity != NONE_EXCEEDED && lastCO2 > (KIWI_LEVEL1 * 0.95)) {
            // avoid hysteris
            severity = LEVEL1_DECREASING;
        }
        else {
            severity = NONE_EXCEEDED;
        }
        return true;
    }
    if (lastCO2 >= KIWI_LEVEL2) {
        severity = LEVEL2;
        return true;
    }
    // we are above level 1, lets find out if it's decreasing
    double noOutlierMax = secondHighest(window);
    if (noOutlierMax < KIWI_LEVEL1 * 1.05) {
        severity = lastCO2 <= noOutlierMax ? LEVEL1_DECREASING : LEVEL1_INCREASING;
    }
    else {
        double decreasingLevel = KIWI_LEVEL1 + ((noOutlierMax - KIWI_LEVEL1) * 0.5);
    // if we aren't half-way towards our threshold, we aren't decreasing hard enough
        severity = lastCO2 <= decreasingLevel ? LEVEL1_DECREASING : LEVEL1_INCREASING;
    }
    return true;
}

