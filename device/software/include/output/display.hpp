#pragma once
#include <Arduino.h>
#include <U8g2lib.h>
#include "sensors/sensors.hpp"

enum DisplayState: unsigned int;

class Display {
public:
    Display(Sensors *sensor);
    unsigned long render(unsigned long tick);
    void setVisible(bool show);

private:
    U8G2 *u8g2;
    Sensors *source;
    DisplayState state;
    bool visible;
    unsigned long lastTick;
    unsigned long currentScreenTime;
    void renderScreen(DisplayState state);
};
