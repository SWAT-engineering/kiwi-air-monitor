#include <Arduino.h>
#include "sensors/rcwl0516sensor.hpp"

Rcwl0516Sensor::Rcwl0516Sensor(KiwiTimer &timer) {
      pinMode(D0, INPUT);
      lastSeen = 0;
      timer.every(1000, [](void * self) -> bool {
          return static_cast<Rcwl0516Sensor *>(self)->sense();
      }, static_cast<void *>(this));
}
bool Rcwl0516Sensor::presenceDetected() {
    // if we've seen movement in the last 15 minutes, we assume there is activity
    return (millis() - lastSeen) < (15 * 60 * 1000);
}
bool Rcwl0516Sensor::sense() {
    if (digitalRead(D0) == HIGH) {
        lastSeen = millis();
    }
    return true;
}