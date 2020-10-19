#include "output/led.hpp"


static const unsigned int AmountOfSteps = 64;
static const unsigned int totalTime = 2000;
static const unsigned int timeBetweenBreaths = 500;

BreathingLed::BreathingLed(): 
        lastTick{0}, position{-1}, currentLevel{Disabled}  {
    pixel = new Adafruit_NeoPixel(1, D3, NEO_GRB + NEO_KHZ800);
    pixel->begin();
    pixel->clear();
    pixel->show();
}

static uint32_t calculateColor(float position, uint32_t color);

unsigned long BreathingLed::render(unsigned long tick) {
    if (position < 0) {
        return 10*1000;
    }
    if (tick - lastTick > wait) {
        pixel->clear();
        if (++position < AmountOfSteps) {
            pixel->setPixelColor(0, calculateColor(position, color));
            wait = totalTime / AmountOfSteps;
        }
        else {
            position = 0;
            wait = timeBetweenBreaths;
        }
        pixel->show();
        lastTick = tick;
    }
    return wait - (tick - lastTick);
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
    position = 0;
    wait = 0;
    lastTick = millis();
    switch (level) {
        case WarningRising:
            color = 0xf46d43;
            break;
        case WarningDecreasing:
            color = 0xfdae61;
            break;
        case SevereWarning:
            color = 0xd73027;
            break;
        case Error:
            color = 0x74add1;
            break;
    }
    render(lastTick + 1);
}

void BreathingLed::stop() {
    position = -1;
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

static const uint8_t minBrightness = 64;
static const uint8_t maxBrightness = 128;

static uint32_t calculateColor(float position, uint32_t color) {
    double breath = minBrightness + (sin(PI * (position / AmountOfSteps)) * (maxBrightness - minBrightness));
    return applyBrightness(color, breath);
}