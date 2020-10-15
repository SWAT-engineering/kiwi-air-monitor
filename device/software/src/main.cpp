#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <U8g2lib.h>
#include "MHZ19.h"                        
#include <SoftwareSerial.h> 
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "user-config.h"

#define SEALEVELPRESSURE_HPA (1013.25)

MHZ19 myMHZ19;
Adafruit_BME280 bme; // I2C

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

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, D3, D4);

SoftwareSerial mySerial(D2, D1); 

#define PUBLISHER(__target, __name) { \
  sprintf(feed_##__target, "devices/%s/sensor/%s", WiFi.macAddress().c_str(), __name); \
  __target = new Adafruit_MQTT_Publish(&mqtt, (const char *)feed_##__target); \
}


void setup() {
  Serial.begin(74880);
  mySerial.begin(9600);
  Wire.begin(D4, D3);

  if (!bme.begin(0x76, &Wire))
  {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x");
    Serial.println(bme.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
  }

  u8g2.begin();

  myMHZ19.begin(mySerial);
  myMHZ19.autoCalibration(false);
  myMHZ19.getCO2(); // clear cache


  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  sslClient.setInsecure();
  PUBLISHER(publishTemp, "Temperature");
  PUBLISHER(publishHumidity, "Humidity");
  PUBLISHER(publishPressure, "Pressure");
  PUBLISHER(publishCO2, "CO2");
  delay(100);
}



void renderScreen(float,float, uint16_t);
void reportWifi(float,float,float,int16_t);

static unsigned long nextDisplay = 0;
void loop() { 
  if (millis() > nextDisplay) {
    nextDisplay += 10000;
    float temp = bme.readTemperature();
    float humidity = bme.readHumidity();
    float pressure = bme.readPressure();
    int16_t co2 = myMHZ19.getCO2(true, true);
    renderScreen(temp, humidity, co2);
    reportWifi(temp, humidity, pressure, co2);
  }
}

static bool displayState = true;

void renderScreen(float temperature, float humidity, uint16_t co2) {
   u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_logisoso28_tf);	// choose a suitable font
  u8g2.setCursor(0,32);
  if (displayState) {
    u8g2.printf("%.1f\xb0%.1f%%", temperature, humidity);
  }
  else {
    u8g2.printf("C: %d", co2);
  }
  displayState = !displayState;
  u8g2.sendBuffer();					// transfer internal memory to the display
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

void reportWifi(float temperature, float humidity, float pressure, int16_t co2) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("No Wifi connection");
    return;
  }
  if (MQTT_connect()) {
    publishTemp->publish(temperature);
    publishHumidity->publish(humidity);
    publishPressure->publish(pressure);
    publishCO2->publish(co2);
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
