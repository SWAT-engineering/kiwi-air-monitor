#pragma once
#include <Arduino.h>
#include <U8g2lib.h>
#include "sensors/sensors.hpp"
#include "shared-timer.hpp"

constexpr u8g2_uint_t PLOT_SIZE = 32;
constexpr unsigned long PIXEL_DURATION = 60 * 1000;

class Display {
public:
    Display(Sensors *sensor, KiwiTimer &timer);
    void setVisible(bool show);

private:
    bool render();
    bool updateValues();
    U8G2 *u8g2;
    Sensors *source;
    bool visible;
    bool filled;
    uint16_t minutesPosition;
    double co2Values[PLOT_SIZE];
    void renderScreen();
    void displayValues();
    void plotGraph();
};
