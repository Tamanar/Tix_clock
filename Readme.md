# Fabrication Tix clock

*Il existe deux versions. Une version ou le changement d'heure été/hiver ce fait via un interrupteur et une version bluetooth où, il est possible de changer la couleur des différent pannels et le changement d'heure ce via une application, bluetooth electronic.*

**Étape Hardware :**
- Fabriquer/trouver votre contenant pour votre électronique (soit en bois soit tout imprimé en 3D)
- Imprimer le support pour les Leds
- Découper une planche pour coller les leds. Faire attention aux sens des leds
- Braser(souder) les leds entre elles (faite bien attention pour le fil de donnée de bien suivre les flèches)
- Relier le fil de données (pin 6 par défaut) à l'arduino
- Relier le DS3231 à l'arduino (A4 A5 par défaut)

- Si Version bluetooth:
    - Brancher le module bluetooth sur le RX et le TX sur l'arduino(pensez à croiser les fils (Rx sur tx et inversment))
- Si version simple
    - Brancher l'interrupteur sur l'arduino (pin 8 par défaut) et sur le 5V
    - Penser à mettre une résistance de pull-down entre le pin 8 et la masse


**Étape Software:**

- Si version Bluetooth
    - Avec un programme tierce programmer votre recépteur bluetooth. (Ce n'est pas le but ici Cf cette [vidéo](https://www.youtube.com/watch?v=iC564i0wf0k))
    - Télécharger sur Android l'application **Bluetooth Electronics** 
    - Télécharger sur votre téléphone le fichier **tix_clock.kwl**
    - Sur l'application, en haut à gauche, sur la disquette, faîtes `load panels` et choisissez le fichier précédent.

- Télécharger [Arduino](https://www.arduino.cc/en/Main/Software)
- Aller dans croquis -> inclure une bibliothèque -> ajouter la bibliothèque zip -> choisir `DS3231.zip` et `FastLED-master.zip`    
 - Dans la boucle setup décommenter `rtc.setTime(11,47 , 00);`, mettre l'heure actuel.
- Téléverser le programme dans l'arduino pour mettre à l'heure le DS3231
- Commenter de nouveau `rtc.setTime(11,47 , 00);` 
- Téléverser de nouveau le programme. Sinon à chaque fois que l'arduino rebootera il rénitialisera le DS3231
