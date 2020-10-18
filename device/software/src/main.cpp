#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h> 
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "user-config.h"
#include "sensors/sensors.hpp"
#include "output/display.hpp"

#define SEALEVELPRESSURE_HPA (1013.25)

Sensors *sensors;
Display *display;

WiFiClientSecure sslClient;
Adafruit_MQTT_Client mqtt(&sslClient, MQTT_SERVER, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD);
Adafruit_MQTT_Publish *publishTemp;
static char feed_publishTemp[256];
Adafruit_MQTT_Publish *publishHumidity;
static char feed_publishHumidity[256];
Adafruit_MQTT_Publish *publishPressure;
static char feed_publishPressure[256];
Adafruit_MQTT_Publish *publishCO2;
static char feed_publishCO2[256];


#define PUBLISHER(__target, __name) { \
  sprintf(feed_##__target, "kiwi/%s/sensor/%s", WiFi.macAddress().c_str(), __name); \
  __target = new Adafruit_MQTT_Publish(&mqtt, (const char *)feed_##__target); \
}


static unsigned long lastTick = 0;
static unsigned long sleepTime = 1;
void setup() {
  Serial.begin(74880);
  // setup I2C on the correct pins
  Wire.begin(D4, D3);
  sensors = new Sensors();
  display = new Display(sensors);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  sslClient.setInsecure();
  PUBLISHER(publishTemp, "Temperature");
  PUBLISHER(publishHumidity, "Humidity");
  PUBLISHER(publishPressure, "Pressure");
  PUBLISHER(publishCO2, "CO2");
}


unsigned long min(unsigned long a, unsigned long b) {
  return a > b ? a : b;
}

//void renderScreen(double,double, double);
void reportWifi(double,double,double,double);

static unsigned long lastMQTTReport = 0;
#define MQTT_EVERY (10*1000)
void loop() { 
  unsigned long tick = millis();
  if (tick - lastTick >= sleepTime) {
    sleepTime = sensors->update(tick);
    sleepTime = min(sleepTime, display->render(tick));
    if (tick - lastMQTTReport >= MQTT_EVERY) {
      lastMQTTReport += MQTT_EVERY;
      sleepTime = min(sleepTime, lastMQTTReport - tick);
      double temp = sensors->getTemperature();
      double humidity = sensors->getHumidity();
      double pressure = sensors->getPressure();
      double co2 = sensors->getCO2();
      reportWifi(temp, humidity, pressure, co2);
    }
    lastTick = tick;
  }
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
bool MQTT_connect() {

  // Stop if already connected.
  if (mqtt.connected()) {
    return true;
  }

  Serial.print("Connecting to MQTT... ");

  int8_t ret = mqtt.connect();
  if (ret != 0) {
    Serial.println("Error connection to MQTT:");
    Serial.println(mqtt.connectErrorString(ret));
    mqtt.disconnect();
    return false;
  }
  Serial.println("MQTT Connected!");
  return true;
}

void reportWifi(double temperature, double humidity, double pressure, double co2) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("No Wifi connection");
    return;
  }
  if (MQTT_connect()) {
    if (!isnan(temperature)) {
      publishTemp->publish(temperature);
    }
    if (!isnan(humidity)) {
      publishHumidity->publish(humidity);
    }
    if (!isnan(pressure)) {
      publishPressure->publish(pressure);
    }
    if (!isnan(co2)) {
      publishCO2->publish(co2);
    }
  }
}


void scanWifi() {
  Serial.print("Scan start ... ");
  int n = WiFi.scanNetworks();
  Serial.print(n);
  Serial.println(" network(s) found");
  for (int i = 0; i < n; i++) {
    Serial.println(WiFi.SSID(i));
  }
  Serial.println();
}
