#include "sensors/co2sensor.hpp"


void CO2Sensor::init() {
    if (connection != nullptr) {
        delete connection;
        connection = nullptr;
    }
    connection = new SoftwareSerial(D5, D8);
    connection->begin(9600);
    hardware.begin(*connection);
    hardware.autoCalibration(false);
    lastReset = millis();
    initialized = false;
    errorCount = 0;
}

bool CO2Sensor::isReady() {
    if (initialized) {
        return true;
    }
    initialized = connection != nullptr && (millis() - lastReset > (3 * 60 * 1000));
    return initialized;
}



uint16_t CO2Sensor::measure() {
    uint16_t result = hardware.getCO2(true, true);
    if (hardware.errorCode != RESULT_OK 
        || result < 300 || result > 3000 
        || !isReady()) {
        if (initialized) {
            // so we were initialized, but still failing, let's detect errors and restart partially if it happens to much
            if (++errorCount > 10) {
                Serial.println("Resetting serial connection to CO2 sensor");
                init();
            }
        }
        return 0;
    }
    return result;
}