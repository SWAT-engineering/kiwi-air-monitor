#pragma once
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

class BME280Sensor {
private:
    bool valid;
    Adafruit_BME280 bme;
public:
    BME280Sensor();
    void measure(float &temp, float &humidity, float &pressure);
};