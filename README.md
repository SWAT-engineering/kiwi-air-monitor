<p align="center">
    <img src="doc/logo.png" alt="Kiwi Monitor logo" />
</p>


Kiwi air monitor is an open source CO2/Humidity/Temperature sensor intended for monitoring the indoor air quality. Kiwi air monitor was initiated by [swat.engineering](https://www.swat.engineering) to support teachers and school organizations with the ventilation of the class rooms. 

## Features

- Monitor CO2, Humidity, Temperature, Atmospheric Pressure 
- Display current measurements and its trend on a small display
- Blink a warning light if certain thresholds are reached (> 800ppm CO2 for example)
- Optionally: publish sensor readings to a (self hosted) MQTT server to allow building wide monitoring
- Optionally: partial remote control via MQTT
- Optionally: Updating firmware over wifi (OTA) 
- Optionally: Docker-compose based Dashboard & MQTT server setup

Due to the cost-cutting concern, we have focussed more on precision instead of accuracy. Meaning that if a value increases, it should indeed represent an increase in that property, but it is acceptable to have a bias with respect to more expensive measurements. So you might get a temperature of 20.4 degrees C even though it iss actually 20.9 degrees C but if it increases to 20.5 degrees C it indeed is now 21.0 degrees C.


## Hardware

The hardware is build around the ESP8266 platform. The costs (in the Netherlands) are roughly €45-50 per device. The list of components and schemas can be found in [doc/NL/Hardware.md](doc/NL/Hardware.md).

## Documentation
Please check out the documentation for further details and instructions about hardware and software, and user manuals:

1. [Dutch](doc/NL/)
2. [English](doc/ENG/) 

## Server

We've developed a small server setup (docker-compose based) so you can get started yourself. Checkout the [server/](server/) directory and the corresponding [documentation](docs/NL/Software.md).

## License

The software and 3D models are all [GPLv3 licensed](LICENSE). We use libraries with  compatible licenses. See [Software documentation](doc/NL/Software.md) for a list of which libraries are used.

