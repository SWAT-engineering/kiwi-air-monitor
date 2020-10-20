<p align="center">
    <img src="doc/logo.png" alt="Kiwi Monitor logo" />
</p>


Kiwi monitor is an open source CO2/Humidity/Temperature sensor intended for monitoring the indoor air quality. Kiwi was created to support teachers with a notification to ventilate their classroom.

## Features

- Monitor CO2, Humidity, Temperature, Atmospheric Pressure 
- Display current measurements and its trend on a small display
- Blink a warning light if certain thresholds are reached (> 1000ppm CO2 for example)
- Optionally: publish sensor readings to a (self hosted) MQTT server to allow building wide monitoring
- Optionally: measure PM2.5 & PM10 concentrations
- Optionally: partial remote control via MQTT
- Over the Air updates of new firmware


## Hardware

The hardware is build around the ESP8266 platform. The costs (in the Netherlands) are roughly €45-50 per device. The bill of materials and schemas can be found in the [device/design directory](device/design/).

## Software

### Kiwi monitor

The software is custom made (GPLv3 licensed), based on the following frameworks and libraries:

- [ESP8266 Arduino Core](https://github.com/esp8266/Arduino) 
- [WifWaf's MH-Z19](https://github.com/WifWaf/MH-Z19)
- [olikraus' U8g2](https://github.com/olikraus/U8g2)
- [Adafruit MQTT](https://github.com/adafruit/Adafruit_MQTT_Library)
- [Adafruit BME280](https://github.com/adafruit/Adafruit_BME280_Library)
- [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)

The project is compiled using [Platform IO](https://platformio.org/). During compilation your specific unit is configured (WiFi, MQTT).

The documentation related to MQTT messages can be found in the [server directory](server/).

### MQTT-to-influxdb Forwarder

To help with a basic setup, we provide a simple forwarder of MQTT messages to an influxdb. Afterwards you can create a dashboard in [granfana](https://grafana.com/) to your own liking.


## Quality of measurements

Due to the cost-cutting concern, we've focussed more on precision instead of accuracy. Meaning that if a value increases, it should indeed represent an increase in that property, but it's okay to be offset from an expensive measurement. So you might get a temperature of 20.4C even though it's actually 20.9C but if it increases to 20.5C it indeed is now 21.0C.

The sensors used specifically:

- Unlike many cheaper CO2 sensors, the MH-Z19B is a NDIR style CO2 sensor, that after initial calibration has quite a good sensitivity. However, the accuracy cannot compete with industrial grade sensors (which cost 4 or 5 times as much). For our purposes, it might be 50 ppm off, but the trend and the rough values are more than enough.
- The BME280 is a cheap sensor that measures humidity, temperature and atmospheric pressure. [Tests](http://www.kandrsmith.org/RJS/Misc/Hygrometers/calib_many.html) have shown it to be accurate and stable. Depeding on how you configure it, the temperature is either a bit over the actual value or under. To save power and spare the chip, we've configured it in a sleep mode.
- The optionally DS18B20 temperature sensor provides a more accurate temperature measurement. In most cases it's not needed, but we have room in both the code and the board to add this.
- The optional SDS011 is a sensor that is also used in [Luftdaten](https://luftdaten.info/) project and is advised by [the Dutch government](https://www.samenmetenaanluchtkwaliteit.nl/sensoren-voor-fijn-stof-pm25pm10).
