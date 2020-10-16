#include "sensors/bme280sensor.hpp"
#include <Wire.h>

BME280Sensor::BME280Sensor(){
    Wire.begin(D4, D3);

    valid = bme.begin(0x76, &Wire);

    if (!valid) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x");
        Serial.println(bme.sensorID(), 16);
    }
    bme.setSampling(Adafruit_BME280::MODE_FORCED,
                    Adafruit_BME280::SAMPLING_X1, // temperature
                    Adafruit_BME280::SAMPLING_X1, // pressure
                    Adafruit_BME280::SAMPLING_X1, // humidity
                    Adafruit_BME280::FILTER_OFF);
}


void BME280Sensor::measure(float &temp, float &humidity, float &pressure) {
    if (!valid) {
        temp = NAN;
        humidity = NAN;
        pressure = NAN;
    }
    else {
        bme.takeForcedMeasurement();
        temp = bme.readTemperature();
        humidity = bme.readHumidity();
        pressure = bme.readPressure();
    }
}