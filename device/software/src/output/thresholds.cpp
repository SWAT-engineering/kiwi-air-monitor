#include "output/thresholds.hpp"
#include "user-config.h"

Thresholds::Thresholds(Sensors *sensor, KiwiTimer &timer): sensor{sensor} {
    EVERY(timer, 10*1000, Thresholds, measure);
    EVERY(timer, 60*1000, Thresholds, refreshThresholds);
}

bool Thresholds::measure() {
    if (sensor->hasCO2()) {
        double co2 = sensor->getCO2();
        if (!isnan(co2)) {
            co2Smoothed.put(co2);
        }
    }
    return true;
}

bool Thresholds::refreshThresholds() {
    if (!co2Smoothed.enoughData()) {
        return true;
    }
    double lastCO2 = co2Smoothed.get();
    if (lastCO2 < KIWI_LEVEL1) {
        severity = NONE_EXCEEDED;
    }
    else if (lastCO2 < KIWI_LEVEL2) {
        severity = LEVEL1;
    }
    else {
        severity = LEVEL2;
    }
    return true;
}

