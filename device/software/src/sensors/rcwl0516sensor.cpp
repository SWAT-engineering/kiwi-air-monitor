#include <Arduino.h>
#include "sensors/rcwl0516sensor.hpp"

#define RCWL_PIN (D6)
#define RECENT_MOVEMENT (2 * 60 * 1000ul)
#define AMOUNT_OF_MEASUREMENTS (sizeof(lastSeen) / sizeof(lastSeen[0]))

Rcwl0516Sensor::Rcwl0516Sensor(KiwiTimer &timer): seenOffset{0} {
      pinMode(RCWL_PIN, INPUT);
      unsigned long now = millis();
      for (unsigned int i = 0; i < AMOUNT_OF_MEASUREMENTS; i++) {
          lastSeen[i] = now;
      }
      EVERY(timer, 2500, Rcwl0516Sensor, sense);
}
bool Rcwl0516Sensor::presenceDetected() {
    // if we've seen movement in the last X minutes, we assume there is activity
    return (millis() - lastSeen[seenOffset]) < RECENT_MOVEMENT;
}
bool Rcwl0516Sensor::sense() {
    if (digitalRead(RCWL_PIN) == HIGH) {
        lastSeen[seenOffset] = millis();
        seenOffset = (seenOffset + 1) % AMOUNT_OF_MEASUREMENTS;
    }
    return true;
}