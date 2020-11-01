#include "output/display.hpp"
#include "output/logo.h"

enum DisplayState: unsigned int {
    INIT = 0,
    BOOT,
    SHOW_CO2,
    SHOW_TEMPERATURE,
    SLEEP
};

static const DisplayState nextState[] = {
    /* INIT =>*/  BOOT,
    /* BOOT =>*/  SHOW_CO2,
    /* SHOW_CO2 =>*/SHOW_TEMPERATURE,
    /* SHOW_TEMPERATURE =>*/  SLEEP,
    /* SLEEP =>*/ SHOW_CO2
};


// we cycle the screen every 10 seconds, how many cycles should we show the same screen
static const uint16_t screenCycles[] {
    /* INIT */ 0,
    /* BOOT */ 2,
    /* SHOW_CO2 */1,
    /* SHOW_TEMPERATURE*/1,
    /* SLEEP*/2
};


Display::Display(Sensors *sensor, KiwiTimer &timer) : source{sensor}, visible{true},
        state{INIT}, screenShownCount{0}  {
    #ifdef KIWI_SCREEN_64
    u8g2 = new U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE, D1, D2);
    #else
    u8g2 = new U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE, D1, D2);
    #endif
    u8g2->begin();
    EVERY(timer, 10*1000, Display, render);
}

bool Display::render() {
    if (!visible) {
        return true;
    }
    screenShownCount++;
    if (screenCycles[state] > screenShownCount) {
        state = nextState[state];
        screenShownCount = 0;
    }
    renderScreen(state);
    return true;
}

void Display::setVisible(bool show) {
    visible = show;
    screenShownCount = UINT16_MAX;
}


void Display::renderScreen(DisplayState state) {
    u8g2->clearBuffer();
    switch (state)
    {
    case BOOT:
        u8g2->drawXBM((128 - KIWI_LOGO_WIDTH) / 2, 0, KIWI_LOGO_WIDTH, KIWI_LOGO_HEIGHT, KIWI_LOGO);
        break;
    case SHOW_TEMPERATURE:
        u8g2->setFont(u8g2_font_logisoso26_tf);	// choose a suitable font
        u8g2->setCursor(0,32);
        u8g2->printf("%.1f\xb0%.1f%%", source->getTemperature(), source->getHumidity());
        break;
    case SHOW_CO2:
        u8g2->setFont(u8g2_font_logisoso28_tf);	// choose a suitable font
        u8g2->setCursor(0,32);
        u8g2->printf("C: %.0f", source->getCO2());
        break;
    case SLEEP:
        break;
    }
    u8g2->sendBuffer();
}