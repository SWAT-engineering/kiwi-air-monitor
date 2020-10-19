#pragma once
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

enum WarningLevel {
    WarningRising = 0,
    WarningDecreasing,
    SevereWarning,
    Error,
    Disabled
};

class BreathingLed {
public:
    BreathingLed();

    void start(WarningLevel level);
    void stop();

    unsigned long render(unsigned long tick);
private:
    unsigned long lastTick;
    unsigned long wait;
    uint32_t color;
    float position;
    WarningLevel currentLevel;
    Adafruit_NeoPixel *pixel;
};