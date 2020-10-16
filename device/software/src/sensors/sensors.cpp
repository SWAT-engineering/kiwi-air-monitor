#include "sensors/sensors.hpp"
#include "sensors/co2sensor.hpp"

#define TICK_RATE (10*1000)

Sensors::Sensors() {
    co2.begin();
    lastTick = 0;
}

unsigned long Sensors::update(unsigned long tick) {
    unsigned long sinceLastTime = tick - lastTick;
    if (sinceLastTime >= TICK_RATE) {
        uint16_t co2value = co2.measure();
        if (co2value > 0) {
            co2Smoothed.put(co2value);
        }
        lastTick += TICK_RATE;
    }
    return TICK_RATE - sinceLastTime;
}


bool Sensors::hasCO2() {
    return co2Smoothed.enoughData();
}

double Sensors::getCO2() {
    return co2Smoothed.get();
}


#ifdef KIWI_TEMPERATURE_SENSOR
bool Sensors::hasTemperature() {
    return temperatureSmoothed.enoughData();
}
double Sensors::getTemperature() {
    return temperatureSmoothed.get();
}
#else 
bool Sensors::hasTemperature() {
    return false;
}
double Sensors::getTemperature() {
    return sqrt(-1);
}
#endif

#ifdef KIWI_HUMIDITY_SENSOR
bool Sensors::hasHumidity() {
    return humiditySmoothed.enoughData();
}
double Sensors::getHumidity() {
    return humiditySmoothed.get();
}
#else 
bool Sensors::hasHumidity() {
    return false;
}
double Sensors::getHumidity() {
    return sqrt(-1);
}
#endif

#ifdef KIWI_PRESSURE_SENSOR
bool Sensors::hasPressure() {
    return pressureSmoothed.enoughData();
}
double Sensors::getPressure() {
    return pressureSmoothed.get();
}
#else 
bool Sensors::hasPressure() {
    return false;
}
double Sensors::getPressure() {
    return sqrt(-1);
}
#endif

#ifdef KIWI_PARTICLE_SENSOR 
bool Sensors::hasParticle() {
    return particleSmoothed.enoughData();
}
double Sensors::getParticle() {
    return particleSmoothed.get();
}
#else 
bool Sensors::hasParticle() {
    return false;
}
double Sensors::getParticle() {
    return sqrt(-1);
}
#endif

