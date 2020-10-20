#include "output/display.hpp"
#include "output/logo.h"

enum DisplayState: unsigned int {
    INIT = 0,
    BOOT,
    #ifdef KIWI_SCREEN_64
    SHOW_ALL,
    #else
    SHOW_TEMPERATURE,
    SHOW_CO2,
    #endif
    SLEEP
};

static unsigned long displayTime[] = {
    0,
    50 * 1000,
    #ifdef KIWI_SCREEN_64
    20 * 1000,
    #else
    5 * 1000,
    5 * 1000,
    #endif
    10 * 1000
};

static DisplayState nextState[] = {
    /* INIT =>*/  BOOT,
#ifdef KIWI_SCREEN_64
    /* BOOT =>*/  SHOW_ALL,
    /* SHOW_ALL =>*/ SLEEP
    /* SLEEP =>*/ SHOW_ALL
#else
    /* BOOT =>*/  SHOW_CO2,
    /* SHOW_TEMPERATURE =>*/  SLEEP,
    /* SHOW_CO2 =>*/SHOW_TEMPERATURE,
    /* SLEEP =>*/ SHOW_CO2
#endif
};


Display::Display(Sensors *sensor) : source{sensor}, visible{true},
        state{INIT}, lastTick{0}, currentScreenTime{0}  {
    #ifdef KIWI_SCREEN_64
    u8g2 = new U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE, D1, D2);
    #else
    u8g2 = new U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE, D1, D2);
    #endif
    u8g2->begin();
}

unsigned long Display::render(unsigned long tick) {
    if (!visible) {
        return 10*1000;
    }
    if (tick - lastTick > currentScreenTime) {
        state = nextState[state];
        renderScreen(state);
        lastTick += currentScreenTime;
        currentScreenTime = displayTime[state];
    }
    return currentScreenTime - (tick - lastTick);
}
void Display::setVisible(bool show) {
    if (!visible && show) {
        state = BOOT;
        lastTick = millis();
        currentScreenTime = displayTime[state];
        renderScreen(BOOT);
        visible = true;
    }
    else {
        visible = false;
        u8g2->clearDisplay();
    }
}


void Display::renderScreen(DisplayState state) {
    u8g2->clearBuffer();
    switch (state)
    {
    case BOOT:
        u8g2->drawXBM((128 - KIWI_LOGO_WIDTH) / 2, 0, KIWI_LOGO_WIDTH, KIWI_LOGO_HEIGHT, KIWI_LOGO);
        break;
#ifdef KIWI_SCREEN_64
    case SHOW_ALL:
        break;
#else
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
#endif
    case SLEEP:
        break;
    }
    u8g2->sendBuffer();
}