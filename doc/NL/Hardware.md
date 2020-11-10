# Hardware

## Bestellijst 
De hardware is ontworpen rondom een ESP8266 platform. De kosten voor alle componentne zijn ongeveer 45-50 euro per apparaat. Hieronder links naar de verschillende componenten (hoeft niet perse daar gekocht te worden). 

- [Wemos/LOLIN D1 Mini V3(ESP8266)](https://www.tinytronics.nl/shop/nl/communicatie/wi-fi/wemos-d1-mini-v2-esp8266-12f-ch340) 
- [Winsen MH-Z19B CO2 Sensor](https://www.tinytronics.nl/shop/nl/sensoren/temperatuur-lucht-vochtigheid/winsen-mh-z19b-co2-sensor-met-kabel): zorg ervoor dat je de __B versie__ koopt. Dit is een NDIR-type CO2 sensor, die na calibratie een goede sensitiviteit heeft. De nauwkeurigheid is echter niet vergelijkbaaar met een industriele sensor (4 a 5 keer zo duur). De echte CO2 waarde kan ongeveer 50 ppm hoger of lager zijn, maar de trend en de grove waardes zijn voor dit doeleinde meer dan genoeg.
- [BME280 I2C Temperature/Humidity Sensor](https://www.tinytronics.nl/shop/nl/sensoren/temperatuur-lucht-vochtigheid/bme280-digitale-barometer-druk-en-vochtigheid-sensor-module): zorg ervoor dat je een versie aanschaft die geconfigureerd is voor I2C, of zorg ervoor dat je het om kunt zetten van SPI naar I2C. BMP280 is ook prima. [Tests](http://www.kandrsmith.org/RJS/Misc/Hygrometers/calib_many.html) hebben laten zien dat de metingen accuraat en stabiel zijn. Afhankelijk hoe de sensor geconfigureerd wordt, zal de temperatuur een beetje onder of boven de echte waar zijn.
- [RCWL-0516 movement sensor](https://www.tinytronics.nl/shop/en/communication/rf/microwave-movement-sensor-rcwl-0516) een kleine sensor die beweging tot 7 m kan detecteren. In dit project wordt deze vooral gebruikt om te detecteren of er mensen aanwezig zijn en of het dus nodig is om iets op het display van de kiwi air monitor te laten zien (of dat het scherm uit kan).
- [SSD1306 128x32 OLED screen I2C](https://www.tinytronics.nl/shop/nl/display/oled/0.91-inch-oled-display-128*32-pixels-wit-i2c): zorg ervoor dat het een I2C versie is en een SSD1306 chipset heeft. Merk maakt niet veel uit. 
- [WS2812B RGB Led](https://www.tinytronics.nl/shop/nl/verlichting/led-digitaal/ws2812b-digitale-5050-rgb-led-printplaat-los-wit): Per apparaat is maar een ledje nodig, maar je kunt ook een hele strip kopen en er andere leuke dingen mee doen. 

Onderdelen die ook nodig zijn, maar waarvan we aannemen dat je die al hebt:
- USB oplader (500ma zou genoeg moeten zijn)
- Micro-USB kabel
- Kabeltjes om de sensors vast te maken aan de hoofdunit (ESP8266)
- Breadboard en kabeltjes om te experimenteren
- Soldeerbout
  
TODO: Hier moet iets komen over de keuze van stroomverbruik (powerbank, voeding?)

## Montage instructies

### Schema
![Wire schema](../../device/design/components_schem.png)

Hieronder een samenvatting van de verbindingen:
| Component | Component side | Wemos D1 Mini |
| --- | --- | --- |
| MH-Z19B | VCC | 5V |
| | GND | G (GND) |
| | TX | D8 |
| | RX | D5 |
| BME280 & SSD1306 | VCC | 3.3V |
| | GND | G |
| | SCL/SCK | D1 |
| | SDA | D2 |
|WS2812B | VDD | 5V |
| | VSS | G |
| | DIN | D4|
| RCWL-0516 | VCC/VIN | 5V |
| | VOUT | D0 |
| | GND | G |
|SDS011 (opt) | VCC | 5V |
| | GND | G |
| | TX | D3 |
| | RX | D6 |
|DS18B20 (opt) | GND (left) | G |
| | DQ (middle) | D7 |
| | VDD (right) | 5V |


Hieronder ook het schema voor experimenten met breadboard view.

![Breadboard view](../../device/design/components_bb.png)

TODO: nog extra uitleg?

## Behuizing
Om de electronica te beschermen en netjes weg te werken, is het goed om er een behuizing om heen te maken. Er is een ontwerp gemaakt in de vorm van een kiwi vogel dat met een 3D-printer afgedrukt kan worden. In dit model passen precies alle componenten die hierboven beschreven zijn. Als je geen 3D printer tot je beschikking hebt of liever zelf iets anders maakt. Zie hieronder dan ook een aantal tips waar je aan moet denken bij het ontwerp.

### 3D-printen van behuizing
TODO: link naar 3D model + extra uitleg? eventueel een foto?
### Adviezen voor eigen ontwerp
TODO: toevoegen adviezen
