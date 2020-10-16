#pragma once
#include <Arduino.h>
#include "co2sensor.hpp"
#include "user-config.h"
#include "smoothed.hpp"

class Sensors {
public:
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
#ifdef KIWI_TEMPERATURE_SENSOR
    TemperatureSensor temp;
    Smoothed<float, 6> tempSmoothed;
#endif
#ifdef KIWI_HUMIDITY_SENSOR
    HumiditySensor humidity;
    Smoothed<float, 6> humiditySmoothed;
#endif
#ifdef KIWI_PRESSURE_SENSOR
    PressureSensor pressure;
    Smoothed<float, 6> pressureSmoothed;
#endif
#ifdef KIWI_PARTICLE_SENSOR
    ParticleSensor particle;
    Smoothed<float, 6> particleSmoothed;
#endif
};