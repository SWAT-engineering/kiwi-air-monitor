# Sensor software
De software voor de Kiwi air monitor is ontwikkeld voor dit project en maakt gebruik van de volgende frameworks en libraries:

- [ESP8266 Arduino Core](https://github.com/esp8266/Arduino) 
- [olikraus' U8g2](https://github.com/olikraus/U8g2)
- [Adafruit MQTT](https://github.com/adafruit/Adafruit_MQTT_Library)
- [Adafruit BME280](https://github.com/adafruit/Adafruit_BME280_Library)
- [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
- [Arduino Timer](https://github.com/contrem/arduino-timer)
- [WifWafs MH-Z19](https://github.com/WifWaf/MH-Z19)

## Configuratie instructies

Het project wordt gecompileerd met [Platform IO](https://platformio.org/). 

TODO: beschrijf hier de configuratie instructies

## Uploaden van firmware
De ESP8266 kan geprogrameerd worden dmv de USB aansluiting en als WiFi & MQTT geconfigureerd zijn, kan erna ook online updates uitgevoerd worden (OTA). 

### Eerste keer uploaden

Na het compileren en configureren van de Kiwi software, moet de USB kabel aan de computer worden aangesloten, en de firmware ge-upload worden.

TODO: script schrijven die dit makkelijk maakt

### Updates uitvoeren via wifi (OTA)
Als de firmware eenmaal op het apparaat staat, kunnen updates gedaan worden via wifi. 

Hiervoor moeten de volgende zaken geconfigureerd worden:

- MQTT & WIFI setup voor de Kiwi
- Signing key for the updates geconfigureeerd voor de Kiwi
- Http server waar de firmware op zal bevinden

TODO: script voor compilate & signing schrijven


## Monitoring dashboard (optioneel)
Het is mogelijk om de metingen door te sturen naar een monitoring dashboard (grafana & influxdb).
Dit biedt het de mogelijkheid om tijdstrends van de gemeten waardes per ruimte in kaart te brengen.
Hieronder volgen instructies hoe je zo'n dashboard aan kunt maken en inrichten. 
De code voor een voorbeeld-dashboard is beschikbaar in de [server directory](../../server/) van deze github repository.

### Architectuur
De verbinding met de Kiwi loopt via MQTT, dit berichten protocol ontkoppeld de Kiwi van iedereen die er interesse in heeft.
Daarnaast kan er ook gecommuniceerd worden richting de Kiwi's via MQTT.
Hierdoor wordt het mogelijk om van een afstand updates te installeren of settings aan te passen.

Een simpele forwarder stuurd MQTT berichten door naar een influx database. Deze forwarder kan ook extra annotaties aan metingen hangen, zoals de naam van een klaslokaal of een gebouw code.
Vervolgens kun je zelf een dashboard maken met [granfana](https://grafana.com/). Een initiële configuratie wordt al geboden in onze voorbeeld server setup.

In [server/mqtt.md](../../server/mqtt.md) staat beschreven welke berichten er gepubliceerd worden op de MQTT server en welke gestuurd kunnen worden richting de Kiwi.

### Voorbeeld server installatie

Als voorbeeld setup hebben wij een kleine server installatie klaargezet. Middels docker-compose kan deze op elke Linux, Windows, of OSX omgeving gedraaid worden. Het moet zelfs mogelijk zijn om een recente raspberry-pi 4 als server te gebruiken hiervoor.

De server directory bevat:
- `demo-config`: een docker configuratie voor mqtt, influx, een forwarder van mqtt naar influx, en grafana voor het visualiseren van het dashboard. 
- `mqtt-2-influx`: een forwarder die de metingen van de Kiwi air monitor (eventueel met extra tags) doorstuurt naar de `kiwi` database voor influx.
- `generator`: een klein programmaatje dat een kiwi sensor simuleert. Dit is nuttig voor het ontwikkelen en testen van de server kant.
- `doc`: een paar extra details over de mqtt berichten die niet passen in deze meer high-level handleiding.

De configuratie van de mqtt-2-influx forwarder wordt uitgelegd in de handleiding in die directory.


## Wil je bijdragen aan software ontwikkelingen?
Heb je ideeën om de software uit te breiden of aan te passen? Bijdrages zijn welkom, neem even contact met ons op van te voren om af te stemmen.