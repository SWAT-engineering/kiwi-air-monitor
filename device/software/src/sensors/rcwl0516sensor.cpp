#include <Arduino.h>
#include "sensors/rcwl0516sensor.hpp"

#define RECENT_MOVEMENT (5 * 60 * 1000ul)
#define AMOUNT_OF_MEASUREMENTS (sizeof(lastSeen) / sizeof(lastSeen[0]))

Rcwl0516Sensor::Rcwl0516Sensor(KiwiTimer &timer): seenOffset{0} {
      pinMode(D0, INPUT);
      for (unsigned int i = 0; i < AMOUNT_OF_MEASUREMENTS; i++) {
          lastSeen[i] = -(2 * RECENT_MOVEMENT);
      }
      timer.every(500, [](void * self) -> bool {
          return static_cast<Rcwl0516Sensor *>(self)->sense();
      }, static_cast<void *>(this));
}
bool Rcwl0516Sensor::presenceDetected() {
    // if we've seen movement in the last X minutes, we assume there is activity
    return (millis() - lastSeen[seenOffset]) < RECENT_MOVEMENT;
}
bool Rcwl0516Sensor::sense() {
    if (digitalRead(D0) == HIGH) {
        lastSeen[seenOffset] = millis();
        seenOffset = (seenOffset + 1) % AMOUNT_OF_MEASUREMENTS;
    }
    return true;
}