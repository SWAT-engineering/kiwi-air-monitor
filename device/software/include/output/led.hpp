#pragma once
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include "shared-timer.hpp"

enum WarningLevel {
    WarningRising = 0,
    WarningDecreasing,
    SevereWarning,
    Error,
    Disabled
};

class BreathingLed {
public:
    BreathingLed(KiwiTimer *timer);

    void start(WarningLevel level);
    void stop();

private:
    KiwiTimer *timer;
    bool render();
    unsigned long blinkStart;
    uint32_t color;
    Timer<>::Task activeLed;
    WarningLevel currentLevel;
    Adafruit_NeoPixel *pixel;
};