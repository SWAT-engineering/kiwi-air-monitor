#include "output/led.hpp"


static const unsigned int AmountOfSteps = 64;
static const unsigned long totalTime = 2000;
static const unsigned int timeBetweenBreaths = 500;

#define DEMO(__timer, __after,__level) \
    (__timer).in(__after, [](void * self) -> bool { \
        static_cast<BreathingLed *>(self)->start(__level); \
        return false; \
    }, static_cast<void *>(this))
BreathingLed::BreathingLed(Thresholds *thres, KiwiTimer &timer, KiwiTimer *highFreqTimer): timer{highFreqTimer}, thresh{thres}, currentLevel{Disabled} {
    pixel = new Adafruit_NeoPixel(1, D3, NEO_GRB + NEO_KHZ800);
    pixel->begin();
    pixel->clear();
    pixel->show();
    EVERY(timer, 10*1000, BreathingLed, updateThresholds);
    DEMO(timer, 100, LightWarning);
    DEMO(timer, 4000, SevereWarning);
    DEMO(timer, 8000, Disabled);
}


bool BreathingLed::updateThresholds() {
    switch (thresh->getSeverity()) {
        case NONE_EXCEEDED: stop(); return true;
        case LEVEL1: start(LightWarning); return true;
        case LEVEL2: start(SevereWarning); return true;
    }
    return true;
}

static uint32_t calculateColor(float position, uint32_t color);

bool BreathingLed::render() {
    unsigned long tick = millis();
    unsigned long position = (tick - blinkStart) % totalTime;
    pixel->clear();
    pixel->setPixelColor(0, calculateColor(((float)position) / totalTime, color));
    pixel->show();
    return true;
}

void BreathingLed::start(WarningLevel level) {
    if (level == currentLevel) {
        return;
    }
    if (level == Disabled) {
        stop();
        return;
    }
    currentLevel = level;
    blinkStart = millis();
    switch (level) {
        case LightWarning:
            color = 0xFFF7BC;
            break;
        case SevereWarning:
            color = 0x993404;
            break;
        case Error:
            color = 0x1965B0;
            break;
    }
    if (activeLed == (Timer<>::Task)NULL){
        activeLed = EVERY((*timer), 1000/25, BreathingLed, render);
    }
}

void BreathingLed::stop() {
    if (activeLed != (Timer<>::Task)NULL){
        timer->cancel(activeLed);
        activeLed = (Timer<>::Task)NULL;
    }
    currentLevel = Disabled;
    pixel->clear();
    pixel->show();
}


#define CHANNEL_BRIGHT(c, b)  ((uint32_t) Adafruit_NeoPixel::gamma8(((c) * (b)) >> 8))

static uint32_t applyBrightness(uint32_t color, uint8_t brightness) {
  return 
    CHANNEL_BRIGHT(color & 0xFF, brightness)
    | CHANNEL_BRIGHT((color >> 8) & 0xFF, brightness) << 8
    | CHANNEL_BRIGHT((color >> 16) & 0xFF, brightness) << 16
    ;
}

static const uint8_t minBrightness = 48;
static const uint8_t maxBrightness = 250;

static uint32_t calculateColor(float position, uint32_t color) {
    double breath = minBrightness + (sin(PI * position) * (maxBrightness - minBrightness));
    return applyBrightness(color, breath);
}