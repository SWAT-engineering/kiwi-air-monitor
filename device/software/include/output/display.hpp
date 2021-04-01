#pragma once
#include <Arduino.h>
#include <U8g2lib.h>
#include "sensors/sensors.hpp"
#include "shared-timer.hpp"
#include "service/status.hpp"

constexpr u8g2_uint_t PLOT_SIZE = 32;
constexpr unsigned long PIXEL_DURATION = 120 * 1000;

class Display {
public:
    Display(Sensors *sensor, Status *status, KiwiTimer &timer);

private:
    Status *status;
    bool render();
    bool updateValues();
    U8G2 *u8g2;
    Sensors *source;
    bool filled = false;
    uint16_t minutesPosition = 0;
    double co2Values[PLOT_SIZE];
    void renderScreen();
    void renderLogo();
    bool displayValues();
    void plotGraph();
    double maxValue();
};
