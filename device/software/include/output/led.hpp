#pragma once
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include "shared-timer.hpp"
#include "thresholds.hpp"

enum WarningLevel {
    Disabled = 0,
    LightWarning,
    SevereWarning,
    Error,
};

class BreathingLed {
public:
    BreathingLed(Thresholds* thresh, KiwiTimer *timer);

    void start(WarningLevel level);
    void stop();

private:
    KiwiTimer *timer;
    Thresholds *thresh;
    bool render();
    bool updateThresholds();

    unsigned long blinkStart;
    uint32_t color;
    Timer<>::Task activeLed = (Timer<>::Task)NULL;
    WarningLevel currentLevel;
    Adafruit_NeoPixel *pixel;
};