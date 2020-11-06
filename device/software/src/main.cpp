#include <Arduino.h>
#include <Wire.h>
#include "shared-timer.hpp"
#include "user-config.h"
#include "sensors/sensors.hpp"
#include "output/display.hpp"
#include "output/led.hpp"
#include "output/mqtt.hpp"
#include "output/thresholds.hpp"
#include "service/wifi-connection.hpp"
#include "service/ota-updates.hpp"
#include "service/mqtt-connection.hpp"
#include "service/status.hpp"


KiwiTimer timer;
WifiConnection *wifi;
Sensors *sensors;
Display *display;
BreathingLed *led;
Mqtt *mqtt;
MqttConnection *mqttCon;
OTAUpdates *ota;
Status *status;
Thresholds *thresh;

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
  wifi = new WifiConnection(timer);
  mqttCon = new MqttConnection(wifi, timer);
  ota = new OTAUpdates(wifi, mqttCon, timer);
  sensors = new Sensors(timer);
  thresh = new Thresholds(sensors, timer);
  display = new Display(sensors, timer);
  led = new BreathingLed(&timer);
  mqtt = new Mqtt(sensors, mqttCon, timer);
  status = new Status(mqttCon, timer);
  
}


void loop() { 
  delay(timer.tick());
}