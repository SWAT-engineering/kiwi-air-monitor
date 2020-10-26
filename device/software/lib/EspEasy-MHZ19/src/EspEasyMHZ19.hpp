#pragma once

#include <Arduino.h>


enum MHZ19_Filter {
    FilterOff = 1,
    FilterOffAllSamples = 2,
    FilterFast = 3,
    FilterMedium = 4,
    FilterSlow = 5
};

class P049_data_struct;
class EspEasyMHZ19 {
    private:
        uint8_t rx, tx;
        bool abcDisabled;
        int filter;
        void init();

        P049_data_struct* hardware;
        unsigned int prevValue;
        bool initializing;
        unsigned long lastReset;
        unsigned long lastABCSet;
    public:
        EspEasyMHZ19(uint8_t rx, uint8_t tx, bool abcDisabled, int filter): 
                rx{rx}, tx{tx}, 
                abcDisabled{abcDisabled}, filter{filter},
                hardware{nullptr} {
            init();
        }

        bool calibrateZero();
        bool reset();
        bool isReady();

        // either returns 0 on error, or the actual co2 value
        uint16_t readCO2();
};