#pragma once
#include <Arduino.h>
#include "co2sensor.hpp"
#include "bme280sensor.hpp"
#include "user-config.h"
#include "smoothed.hpp"

class Sensors {
public:
    // call this inside setup
    Sensors();
    bool hasCO2();
    bool hasTemperature();
    bool hasHumidity();
    bool hasPressure();
    bool hasParticle();

    double getCO2();
    double getTemperature();
    double getHumidity();
    double getPressure();
    double getParticle();

    unsigned long lastTick;

    unsigned long update(unsigned long tick);

private:
    CO2Sensor co2;
    Smoothed<uint16_t, 6> co2Smoothed;
#ifdef KIWI_BME280_SENSOR
    BME280Sensor bme;
    Smoothed<float, 6> tempSmoothed;
    Smoothed<float, 6> humiditySmoothed;
    Smoothed<float, 6> pressureSmoothed;
#endif
#ifdef KIWI_PARTICLE_SENSOR
    ParticleSensor particle;
    Smoothed<float, 6> particleSmoothed;
#endif
};