#include "sensors/co2sensor.hpp"


CO2Sensor::CO2Sensor() {
    hardware = new EspEasyMHZ19(D2, D1, true, FilterMedium);
}

uint16_t CO2Sensor::measure() {
    return hardware->readCO2();
}