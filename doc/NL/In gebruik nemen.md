# In gebruik nemen

Als je de hardware en software geinstalleerd en geconfigureerd hebt, komt de volgende stap: het klaar maken voor gebruik. In dit document staat uitgelegd hoe de Kiwi air monitor gecalibreerd moet worden, waar je rekening mee moet houden bij het ophangen van de kiwi en hoe je software updates kunt uitvoeren. De handleiding voor de eindgebruikers is in een appart document te vinden. 

## Calibratie
De CO2 sensor moet eenmalig gecalibreerd worden. Doe dit *voor* je de Kiwi-air-monitor aan de muur hangt, want de calibratie gebeurd bij voorkeur buiten, en zonder enige encapsulatie van de sensor.

Volg hiervoor de volgende stappen:

- Sluit een of meerdere co2 sensors zoals beschreven in het calibratie schema
- Upload het calibratie programma naar die esp8266
- Ontkoppel de esp8266
- Neem het mee naar buiten op een droge dag, sluit de esp8266 aan op stroom.
- Wacht 30 minuten, het ledje op de esp8266 zal gaan knipperen om aan te geven dat de calibratie voltooid is.


## Ophangen
Bij het ophangen van de sensor moet een geschikte plek gezocht worden in de ruimte. Houd hierbij rekening met het volgende:

TODO: lijstje met criteria voor het ophangen van de kiwi

## Onderhoud (updates)

- Updates voor de software kunnen automatisch lopen, mits dit is geconfigureerd via wifi & mqtt.
- Het ontwerp van de Kiwi is modulair, als een component beschadigd raakt, kan het makkelijk vervangen worden mits er van onze voorgestelde kabel boom gebruik is gemaakt.