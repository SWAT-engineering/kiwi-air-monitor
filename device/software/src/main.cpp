#include <Arduino.h>
#include <Wire.h>
#include "shared-timer.hpp"
#include "user-config.h"
#include "sensors/sensors.hpp"
#include "output/display.hpp"
#include "output/led.hpp"
#include "output/mqtt.hpp"


KiwiTimer timer;
Sensors *sensors;
Display *display;
BreathingLed *led;
Mqtt *mqtt;

/*
CO2: TX: D8, RX: D5
I2C: SCL/SCK: D1 & SDA: D2
Led: D4
Extra Temp: D7
Dust: tx: D3. rx: D6
*/

void setup() {
  Serial.begin(74880);
  // setup I2C on the correct pins
  Wire.begin(D2, D1);
  sensors = new Sensors(timer);
  display = new Display(sensors);
  led = new BreathingLed();
  mqtt = new Mqtt(sensors);
}


unsigned long min(unsigned long a, unsigned long b) {
  return a > b ? a : b;
}

static void checkThresholds() {
  double co2 = sensors->getCO2();
  if (!isnan(co2)) {
    if (co2 > 700) {
      led->start(SevereWarning);
    }
    else if (co2 > 500) {
      led->start(WarningRising);
    }
    else if (co2 < 500) {
      led->stop();
    }
  }
  else {
    led->start(Error);
  }
}

void loop() { 
  unsigned long tick = millis();
  unsigned long sleepTime = 10*1000;
  sleepTime = min(sleepTime, sensors->update(tick));
  sleepTime = min(sleepTime, display->render(tick));
  sleepTime = min(sleepTime, led->render(tick));
  sleepTime = min(sleepTime, mqtt->process(tick));
  delay(10);
}