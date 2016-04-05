# Paaspop ’10 seconds of fame’

### Arduino

#### IDE
De code voor de Arduino bevindt zich in het bestand paaspop.ino. Om deze te kunnen compileren heb je de NeoPixel library van Adafruit nodig. Deze zit bijgeleverd in de map Adafruit-NeoPixel. Je moet deze map kopiëren naar je Arduino library folder (onder Windows: Documenten/Arduino/libraries).
Vervolgens moet je in de Arduino IDE aangeven dat je de library gebruikt. Dit kun je doen door bovenin naar Schets > Bibliotheek gebruiken te gaan en daar Adafruit NeoPixel te selecteren. Zie je de library niet staan? Start de Arduino IDE opnieuw op.

#### Aansluiten
Het script staat standaard geprogrammeerd om de NeoPixel op pin 6 aan te sturen. Je kunt dit veranderen door de var neoPin te veranderen in de juiste pin. Ook de pin waarop de Raspberry Pi is aangesloten kun je wijzigen (piPin).

#### Werking systeem
Wanneer er op de knop wordt gedrukt stuurt de Raspberry Pi een hoog signaal uit naar de Arduino. De Arduino vangt deze op en laat de LED cirkel oplichten. De Raspberry Pi begint met opnemen en ondertussen laat het Arduino script de LED cirkel ‘aflopen’. Omdat de Raspberry Pi de opgenomen video moet converteren laten we de Arduino nog een laad indicatie weergeven. De precieze laadtijd is niet geïmplementeerd, dus we laten de Arduino voor ongeveer 10 seconden een laad cirkel weergeven.

### Raspberry Pi

#### Script
Het Python script voor de Raspberry Pi heet switch.py. Zorg dat deze tijdens het opstarten op de achtergrond wordt uitgevoerd. Het script zal proberen een USB stick te mounten en vervolgens wachten op de input van de knop.

#### Aansluiten
Zie ook (http://www.raspberrypi-spy.co.uk/wp-content/uploads/2014/07/Raspberry-Pi-GPIO-Layout-Model-B-Plus.png "Raspberry Pi GPIO pin scheme"). Je kunt in het script aangeven op welke pins de button en de Arduino aangesloten is. De knop kan je aansluiten met een pin op de ground, en een pin op willekeurige plek (voorkeur pin 12 (GPIO18)). De Arduino kan je ook aansluiten op een willekeurige pin. Je kunt vervolgens ook nog instellen hoe lang er opgenomen moet worden.

De camera kun je met de flatcable aansluiten op de Raspberry Pi. Als het goed is werkt deze vanzelf. Doet deze het niet? Check dan je Raspberry Pi settings (sudo raspi-config) om de camera aan te zetten.

#### Werking systeem
De Raspberry Pi wacht op input van de knop. Op het moment dat de knop wordt ingedrukt gaat hij x seconden video opnemen op de USB stick (intern geheugen te traag). Nadat hij klaar is met opnemen converteerd hij de video naar mp4. 