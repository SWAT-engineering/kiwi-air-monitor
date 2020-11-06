#include "output/display.hpp"
#include "output/logo.h"

Display::Display(Sensors *sensor, KiwiTimer &timer) : source{sensor} {
    #ifdef KIWI_SCREEN_64
    u8g2 = new U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE, D1, D2);
    #else
    u8g2 = new U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE, D1, D2);
    #endif
    u8g2->begin();
    EVERY(timer, 10*1000, Display, render);
    EVERY(timer, PIXEL_DURATION, Display, updateValues);
    for (uint16_t i = 0; i < PLOT_SIZE; i++) {
        co2Values[i] = NAN;
    }
}

bool Display::render() {
    u8g2->clearBuffer();
    if (source->getPresence() && visible) {
        if (!filled && millis() < 30000) {
            // draw logo
            u8g2->drawXBM((128 - KIWI_LOGO_WIDTH) / 2, 0, KIWI_LOGO_WIDTH, KIWI_LOGO_HEIGHT, KIWI_LOGO);
        } else {
            displayValues();
            plotGraph();
        }
    }
    u8g2->sendBuffer();
    return true;
}

void Display::setVisible(bool show) {
    visible = show;
}

bool Display::updateValues() {
    double value = source->getCO2();
    if (isnan(value)) {
        filled = false;
        return true;
    }
    co2Values[minutesPosition % PLOT_SIZE] = value;
    minutesPosition++;
    filled = filled || minutesPosition >= PLOT_SIZE;
    return true;
}

constexpr u8g2_uint_t GRAPH_X_OFFSET = 128 - PLOT_SIZE;

#define GET_VALUE(__i) (co2Values[(minutesPosition - (PLOT_SIZE - (__i))) % PLOT_SIZE])

void Display::displayValues() {
    u8g2->setFont(u8g2_font_logisoso16_tf);
    u8g2->setCursor(0,16);
    if (source->hasCO2()) {
        u8g2->printf("C: %.0f", source->getCO2());
    }
    else {
        u8g2->print("CO2: ??");
    }
    u8g2->setCursor(0,32);
    if (source->hasTemperature()) {
        u8g2->printf("%.1f\xb0", source->getTemperature());
    }
    if (source->hasHumidity()) {
        u8g2->printf("%.1f%%", source->getHumidity());
    }
}

void Display::plotGraph() {
    double rangeStart = GET_VALUE(0);
    double rangeEnd = rangeStart;
    for (u8g2_uint_t i = 1; i < PLOT_SIZE; i++) {
        double value = GET_VALUE(i);
        if (isnan(value)) {
            continue;
        } else if (value < rangeStart) {
            rangeStart = value;
        } else if (value > rangeEnd) {
            rangeEnd = value;
        }
    }
    double range = rangeEnd - rangeStart;
    if (range < 100) {
        range = 100;
    }
    for (u8g2_uint_t i = 0; i < PLOT_SIZE; i++) {
        double value = GET_VALUE(i);
        if (!isnan(value)) {
            double y = ((value - rangeStart) / range) * PLOT_SIZE;
            u8g2->drawVLine(GRAPH_X_OFFSET + i, (u8g2_uint_t)round(y), PLOT_SIZE);
        }
    }
}