#include <Arduino.h>
#if !defined(CALIBRATE) && !defined(MONITOR)
#include <Wire.h>
#include "shared-timer.hpp"
#include "user-config.h"
#include "sensors/sensors.hpp"
#include "output/outputs.hpp"
#include "service/wifi-connection.hpp"
#include "service/ota-updates.hpp"
#include "service/mqtt-connection.hpp"
#include "service/status.hpp"

ADC_MODE(ADC_VCC);

KiwiTimer timer;
KiwiTimer highResTimer;

bool tickNormalTimer(void *) {
  highResTimer.in(timer.tick(), tickNormalTimer);
  return false;
}

WifiConnection *wifi;
Sensors *sensors;
Outputs *outputs;

MqttConnection *mqttCon;
OTAUpdates *ota;
Status *status;

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
  status = new Status(mqttCon, timer);
  outputs = new Outputs(sensors, mqttCon, status, timer, &highResTimer);
  highResTimer.in(10, tickNormalTimer);
}



void loop() { 
  delay(highResTimer.tick());
}
#elif defined(CALIBRATE) 

#include "EspEasyMHZ19.hpp"
#include <SoftwareSerial.h>

static unsigned long start;
static bool reset;
static bool blinkLedState;
static unsigned long lastRead;

// CO2 sensors wire:
// rx  tx
// d5  d8
// d1  d3
// d2  d4
// d6  d0

static EspEasyMHZ19 *sensors[4];
void setup() {
    Serial.begin(74880);
    Serial.println("Starting up MHZ19 connections");
    sensors[0] = new EspEasyMHZ19(D5, D8, true, FilterOff);
    sensors[1] = new EspEasyMHZ19(D1, D3, true, FilterOff);
    sensors[2] = new EspEasyMHZ19(D2, D4, true, FilterOff);
    sensors[3] = new EspEasyMHZ19(D6, D0, true, FilterOff);
    start = millis();
    reset = false;
    lastRead = 0;
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.println("Starting co2 sensors, wait 3min before we see first values pop up");
}

constexpr unsigned long calibrateAfter =30*60*1000;

void loop() {
    if (!reset  && (millis() - start) > calibrateAfter) {
      for (int i = 0; i < 4; i++) {
        EspEasyMHZ19 *s = sensors[i];
        if (s->isReady() && s->readCO2() > 0) {
          Serial.printf("Calibrating: %d\n", i);
          s->calibrateZero();
        }
      }
      reset = true;
    }
    if (reset) {
      if (blinkLedState) {
        digitalWrite(LED_BUILTIN, HIGH);
      }
      else {
        digitalWrite(LED_BUILTIN, LOW);
      }
      blinkLedState = !blinkLedState;
    }
    if (millis() - lastRead > (30 * 1000)) {
      if (reset) {
        Serial.println("Calibrated!");
      }
      else {
        Serial.printf("Time till calibration: %d\n", (calibrateAfter - (millis() - start)) / (60*1000));
      }
      for (int i = 0; i < 4; i++) {
        uint16_t value = sensors[i]->readCO2();
        if (value > 0) {
          Serial.printf("CO2 - %d: %d\n", i, value);
        }
      }
      lastRead += 30*1000;
    }
    delay(1000);
}
#elif defined(MONITOR) 

#include "EspEasyMHZ19.hpp"
#include <SoftwareSerial.h>
#include "user-config.h"
#include "shared-timer.hpp"
#include "service/wifi-connection.hpp"
#include "service/mqtt-connection.hpp"

KiwiTimer timer;
static unsigned long lastRead;
WifiConnection *wifi;
MqttConnection *mqttCon;

// CO2 sensors wire:
// rx  tx
// d5  d8 --> disable ABC
// d1  d3 --> disable ABC
// d2  d4 --> enable ABC
// d6  d0 --> enable ABC

static EspEasyMHZ19 *sensors[4];



#define PUBLISH(x, v) if (v > 0) mqttCon->publish(x, v);

void report(double values[4]) {
  PUBLISH("sensor/CO2_Compare1", values[0]);
  PUBLISH("sensor/CO2_Compare2", values[1]);
  PUBLISH("sensor/CO2_Compare3", values[2]);
  PUBLISH("sensor/CO2_Compare4", values[3]);
}


bool sense(void * unused) {
  double values[4];
  for (int i = 0; i < 4; i++) {
    values[i] = 0;
    if (sensors[i] && sensors[i]->isReady()) {
      uint16_t co2 = sensors[i]->readCO2();
      if (co2 > 0) {
        values[i] = co2;
        Serial.println(co2);
      }
    }
  }
  report(values);
  return true;
}

bool resetSensor(void *unused) {
  sensors[3]->reset();
  return false;
}

void setup() {
  Serial.begin(74880);
  wifi = new WifiConnection(timer);
  mqttCon = new MqttConnection(wifi, timer);
  Serial.println("Starting up MHZ19 connections");
  //sensors[0] = new EspEasyMHZ19(D5, D8, false, FilterOff);
  //sensors[1] = new EspEasyMHZ19(D1, D3, true, FilterOff);
  //sensors[2] = new EspEasyMHZ19(D2, D4, false, FilterOff);
  sensors[3] = new EspEasyMHZ19(D6, D0, false, FilterOff);
  lastRead = 0;
  timer.every(10 * 1000, sense, NULL);
  timer.in(3 * 60 * 1000, resetSensor, NULL);
}


void loop() {
  delay(timer.tick());
}

#endif