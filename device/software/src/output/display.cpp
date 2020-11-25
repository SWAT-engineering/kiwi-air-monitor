#include "output/display.hpp"
#include "output/logo.h"

Display::Display(Sensors *sensor, Status *status, KiwiTimer &timer) : status{status}, source{sensor} {
    #ifdef KIWI_SCREEN_64
    u8g2 = new U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE, D1, D2);
    #else
    u8g2 = new U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE, D1, D2);
    #endif
    u8g2->begin();
    EVERY(timer, 10*1000, Display, render);
    EVERY(timer, PIXEL_DURATION, Display, updateValues);
    for (u8g2_uint_t i = 0; i < PLOT_SIZE; i++) {
        co2Values[i] = 0;
    }
    u8g2->clearBuffer();
    renderLogo();
    u8g2->sendBuffer();
}

void Display::renderLogo() {
    u8g2->drawXBM((128 - KIWI_LOGO_WIDTH) / 2, 0, KIWI_LOGO_WIDTH, KIWI_LOGO_HEIGHT, KIWI_LOGO);
}

bool Display::render() {
    u8g2->clearBuffer();
    if (!filled && millis() < 30000) {
        // still booting up draw logo
        renderLogo();
    }
    else if ((!source->hasPresence() || source->getPresence()) && status->shouldShowScreen()) {
        if (displayValues()) {
            plotGraph();
        }
        else {
            // nothing to show yet, so also just draw the logo
            renderLogo();
        }
    }
    u8g2->sendBuffer();
    return true;
}

bool Display::updateValues() {
    if (!source->hasCO2()) {
        return true;
    }
    double value = source->getCO2();
    if (value < 100 || isnan(value) || value > 5000) {
        // skip invalid co2 values
        return true;
    }
    co2Values[minutesPosition % PLOT_SIZE] = value;
    minutesPosition++;
    filled = filled || minutesPosition >= PLOT_SIZE;
    return true;
}

constexpr u8g2_uint_t GRAPH_X_OFFSET = 128 - PLOT_SIZE;


bool Display::displayValues() {
    u8g2->setFont(u8g2_font_logisoso16_tf);
    u8g2->setCursor(0,16);
    bool anyThingRendered = false;

    if (source->hasCO2()) {
        u8g2->printf("CO2: %.0f", source->getCO2());
        anyThingRendered = true;
    }
    u8g2->setCursor(0,32);
    u8g2->setFont(u8g2_font_fur14_tf);
    if (source->hasTemperature()) {
        u8g2->printf("%.1f\xb0 ", source->getTemperature());
        anyThingRendered = true;
    }
    if (source->hasHumidity()) {
        u8g2->printf("%.f%%", source->getHumidity());
        anyThingRendered = true;
    }
    return anyThingRendered;
}

#define GET_VALUE(__i) (co2Values[(minutesPosition - (PLOT_SIZE - (__i))) % PLOT_SIZE])

static double max(double a, double b)
{
    return a > b ? a : b;
}

static void fixRange(double &rangeStart, double &rangeEnd) {
    if (rangeEnd - rangeStart < 100) {
        rangeStart -= 50;
        rangeEnd += 50;
    }
    if (rangeEnd - rangeStart < 200) {
        rangeStart -= 25;
        rangeEnd += 25;
    }
    if (rangeStart < 350) {
        rangeStart = 350;
        rangeEnd = max(500, rangeEnd);
    }
}

void Display::plotGraph() {
    if (!filled) {
        return;
    }
    double rangeStart = 5000;
    double rangeEnd = 0;
    for (u8g2_uint_t i = 1; i < PLOT_SIZE; i++) {
        double value = GET_VALUE(i);
        if (isnan(value)) {
            continue;
        } else if (isnan(rangeStart)) {
            rangeStart = value;
            rangeEnd = value;
        } else if (value < rangeStart) {
            rangeStart = value;
        } else if (value > rangeEnd) {
            rangeEnd = value;
        }
    }
    if (isnan(rangeStart)) {
        return;
    }
    fixRange(rangeStart, rangeEnd);
    double range = rangeEnd - rangeStart;
    for (u8g2_uint_t i = 0; i < PLOT_SIZE; i++) {
        double value = GET_VALUE(i);
        if (!isnan(value)) {
            double y = PLOT_SIZE - ((max(0, (value - rangeStart)) / range) * PLOT_SIZE);
            u8g2->drawVLine(GRAPH_X_OFFSET + i, (u8g2_uint_t)round(y), PLOT_SIZE);
        }
    }
}