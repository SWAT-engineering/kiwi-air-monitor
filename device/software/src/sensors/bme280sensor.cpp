#include "sensors/bme280sensor.hpp"
#include <Wire.h>

BME280Sensor::BME280Sensor(){

    valid = bme.begin(0x76, &Wire);

    if (!valid) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x");
        Serial.println(bme.sensorID(), 16);
        return;
    }
    Serial.println("Sensor found!");
    bme.setSampling(Adafruit_BME280::MODE_NORMAL,
                    Adafruit_BME280::SAMPLING_X8, // temperature
                    Adafruit_BME280::SAMPLING_X8, // pressure
                    Adafruit_BME280::SAMPLING_X8, // humidity
                    Adafruit_BME280::FILTER_OFF,
                    Adafruit_BME280::STANDBY_MS_1000);
}


void BME280Sensor::measure(float &temp, float &humidity, float &pressure) {
    if (!valid) {
        temp = NAN;
        humidity = NAN;
        pressure = NAN;
    }
    else {
        temp = bme.readTemperature();
        humidity = bme.readHumidity();
        pressure = bme.readPressure();
    }
}