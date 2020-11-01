#include "sensors/sensors.hpp"
#include "sensors/co2sensor.hpp"

#define TICK_RATE (10*1000)

Sensors::Sensors(KiwiTimer &timer) {
#ifdef KIWI_RCWL_SENSOR
    rcwl = new Rcwl0516Sensor(timer);
#endif
    EVERY(timer, 10*1000, Sensors, update);
}


#define PUT_OR_MARK(sm, v) \
    if (!isnan(v)) { \
        sm.put(v); \
    } else { \
        sm.markError(); \
    }


bool Sensors::update() {
    uint16_t co2value = co2.measure();
    if (co2value > 0) {
        co2Smoothed.put(co2value);
    }
    else {
        co2Smoothed.markError();
    }
    #ifdef KIWI_BME280_SENSOR
    float temp;
    float humidity;
    float pressure;
    bme.measure(temp, humidity, pressure);
    PUT_OR_MARK(tempSmoothed, temp);
    PUT_OR_MARK(humiditySmoothed, humidity);
    PUT_OR_MARK(pressureSmoothed, pressure);
    #endif
    return true;
}


bool Sensors::hasCO2() {
    return co2Smoothed.enoughData();
}

double Sensors::getCO2() {
    return co2Smoothed.get();
}


#ifdef KIWI_BME280_SENSOR
bool Sensors::hasTemperature() {
    return tempSmoothed.enoughData();
}
double Sensors::getTemperature() {
    return tempSmoothed.get();
}
bool Sensors::hasHumidity() {
    return humiditySmoothed.enoughData();
}
double Sensors::getHumidity() {
    return humiditySmoothed.get();
}
bool Sensors::hasPressure() {
    return pressureSmoothed.enoughData();
}
double Sensors::getPressure() {
    return pressureSmoothed.get();
}
#else 
bool Sensors::hasTemperature() {
    return false;
}
double Sensors::getTemperature() {
    return NAN;
}
bool Sensors::hasHumidity() {
    return false;
}
double Sensors::getHumidity() {
    return NAN;
}
bool Sensors::hasPressure() {
    return false;
}
double Sensors::getPressure() {
    return NAN;
}
#endif

#ifdef KIWI_RCWL_SENSOR
bool Sensors::getPresence() {
    return rcwl->presenceDetected();
}

bool Sensors::hasPresence() {
    return true;
}
#else
bool Sensors::getPresence() {
    return false;
}

bool Sensors::hasPresence() {
    return false;
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
    return NAN;
}
#endif

