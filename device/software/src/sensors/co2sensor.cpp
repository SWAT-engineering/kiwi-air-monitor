#include "sensors/co2sensor.hpp"

CO2Sensor::CO2Sensor() {
    hardware = new EspEasyMHZ19(D5, D8, false, FilterOff);
}


uint16_t CO2Sensor::measure() {
    return hardware->readCO2();
}