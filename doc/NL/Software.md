# Sensor software
De software voor de Kiwi air monitor is ontwikkeld voor dit project (GPLv3 licensed) en maakt gebruik van de volgende frameworks en libraries:

- [ESP8266 Arduino Core](https://github.com/esp8266/Arduino) 
- [WifWaf's MH-Z19](https://github.com/WifWaf/MH-Z19)
- [olikraus' U8g2](https://github.com/olikraus/U8g2)
- [Adafruit MQTT](https://github.com/adafruit/Adafruit_MQTT_Library)
- [Adafruit BME280](https://github.com/adafruit/Adafruit_BME280_Library)
- [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)

## Configuratie instructies

Het project wordt gecompileerd met [Platform IO](https://platformio.org/). 

TODO: beschrijf hier de configuratie instructies

## Uploaden van firmware
TODO: korte intro?

### Eerste keer uploaden
TODO: hier beschrijven hoe de firmware de eerste keer op het apparaat gezet moet worden (via kabel)

### Updates uitvoeren via wifi (OTA)
Als de firmware eenmaal op het apparaat staat, kunnen updates gedaan worden via wifi. 

TODO: hier duidelijker beschrijven wat er moet gebeuren.


## Monitoring dashboard (optional)
Het is mogelijk om de metingen door te sturen naar een monitoring dashboard (MQTT server). Hierdoor wordt het mogelijk om van een afstand updates te installeren of settings aan te passen. Daarnaast biedt het de mogelijkheid om tijdstrends van de gemeten waardes per ruimte in kaart te brengen. Hieronder volgen instructies hoe je zo'n dashboard aan kunt maken en inrichten. De code voor een voorbeeld-dashboard is beschikbaar in de [server directory](../server/) van deze github repository. Via een simpele forwarder worden MQTT berichten doorgestuurd naar een influx database. Vervolgens kun je zelf een dashboard maken met [granfana](https://grafana.com/).


De server directory bevat:
- `demo-config`: een docker configuratie voor mqtt, influx, een forwarder van mqtt naar influx, en grafana voor het visualiseren van het dashboard. 
- `mqtt-2-influx`: een forwarder die de metingen van de Kiwi air monitor (eventueel met extra tags) doorstuurt naar de `kiwi` database voor influx.
- `generator`: een klein programmaatje dat een kiwi sensor simuleert. Dit is nuttig voor het ontwikkelen en testen van de server kant. 

TODO: ben niet zeker van of deze nodig blijft of dat het voldoende is om dat hier te zetten.
- `doc`: documentation about the mqtt messages, and several setup related documentation and advice


TODO: hier instructies uitbreiden. Wat doen we met de info in de readme files van bijvoorbeeld generator en demo-config? Daar gewoon laten staan misschien. Lijkt teveel detail om hierin te stoppen.

TODO: eventueel ideeen voor uitbreiding noemen.

## Wil je bijdragen aan software ontwikkelingen?
Heb je ideeën om de software uit te breiden of aan te passen? Alle bijdrages zijn welkom!

TODO: hier beschrijven hoe dat handigste werkt

