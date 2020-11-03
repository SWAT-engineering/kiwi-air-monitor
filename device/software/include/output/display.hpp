#pragma once
#include <Arduino.h>
#include <U8g2lib.h>
#include "sensors/sensors.hpp"
#include "shared-timer.hpp"

enum DisplayState: unsigned int;

class Display {
public:
    Display(Sensors *sensor, KiwiTimer &timer);
    void setVisible(bool show);

private:
    bool render();
    U8G2 *u8g2;
    Sensors *source;
    DisplayState state;
    bool visible;
    uint16_t screenShownCount;
    void renderScreen(DisplayState state);
};
