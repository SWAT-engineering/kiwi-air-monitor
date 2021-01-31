#include "sensors/co2sensor.hpp"

constexpr unsigned long INIT_TIME = 3 * 60 * 1000;

CO2Sensor::CO2Sensor() {
    connection = nullptr;
    init();
}

void CO2Sensor::init() {
    if (connection != nullptr) {
        delete connection;
    }
    connection = new SoftwareSerial(D5, D8);
    if (connection == nullptr) {
        return;
    }
    connection->begin(9600);
    hardware.begin(*connection);
    hardware.autoCalibration(true);
    hardware.setFilter(false, true);
    initializing = true;
    initializingStarted = millis();
    errors = 0;
}


uint16_t CO2Sensor::measure() {
    uint16_t value = hardware.getCO2(true, true);
    if (initializing) {
        initializing = (millis() - initializingStarted) < INIT_TIME;
        if (initializing) {
            return 0;
        }
    }
    if (hardware.errorCode == RESULT_OK) {
        if (value > 100 && value < 5000) {
            errors = 0;
            return value;
        }
    }
    errors++;
    if (errors > 180) { // half an hour of error readings
        init();
    }
    return 0;
}