#include "sensors/co2sensor.hpp"


void CO2Sensor::begin() {
    if (hardware != nullptr) {
        return;
    }
    hardware = new EspEasyMHZ19(D2, D1, true, FilterMedium);
}

uint16_t CO2Sensor::measure() {
    if (hardware == nullptr) {
        return 0;
    }
    return hardware->readCO2();
}