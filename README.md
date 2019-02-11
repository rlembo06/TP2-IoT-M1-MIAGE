# TP2 - IoT - M1 MIAGE - Requêtes Client / ESP32

- <a href="https://tp2-iot-m1-miage.firebaseapp.com/" target="_blank">Notre client web hébergé sur Firebase</a>
- <a href="http://www.i3s.unice.fr/~menez/M1Miage/TP2/tp2.pdf" target="_blank">Consignes du TP</a>

## Membres du projet :

- Romain LEMBO
- Victor MONSCH

## Executer le projet :

```
npm install
npm run start
```

## Description du projet :

### Architecture :
Données stockées dans une API REST Firestore (Google), ces données sont envoyées par la carte ESP 32 via des méthodes POST.
Un client web (développé en JavaScript avec le framework Vue.js) affiche les données via les URI de l'API REST Firestore, notamment avec des méthodes GET.

![alt text](https://firebasestorage.googleapis.com/v0/b/tp2-iot-m1-miage.appspot.com/o/archi-tp.png?alt=media&token=4ca6190d-f11a-47ee-b154-349526511bf9)

### Données :
Les données de températures ou de luminosités ont toutes un attribut temporel pour les afficher de manière chronologique dans un graphique.
De plus, chaque valeur possède un attribut pour identifier de quelle carte ESP32 cela provient (Adresse MAC).

Exemples : 
- <a href="https://firestore.googleapis.com/v1/projects/tp2-iot-m1-miage/databases/(default)/documents/temperatures" target="_blank">URI de températures</a>
- <a href="https://firestore.googleapis.com/v1/projects/tp2-iot-m1-miage/databases/(default)/documents/brightnesses" target="_blank">URI de luminosités</a>


![Communication Firestore](https://firebasestorage.googleapis.com/v0/b/tp2-iot-m1-miage.appspot.com/o/data-temperatures.png?alt=media&token=881811ba-e223-4980-a389-319899310aa3)

### Client VueJS :

### Client ESP :
1- Lorsque le client s'allume/se réveille, il  récolte les données de ses capteurs de luminosité et de température et émet des requêtes HTTP POST vers notre Firestore afin de stocker ces données. Il vérifie que ces requêtes ont fonctionné et affichent un message en cas de succès (HTTP 200). 
2- Ensuite, il va récupérer un document spécifique de Firestore en HTTP GET afin de vérifier les seuils des deux capteurs. Si les deux valeurs des capteurs sont au dessus des seuils récupérés de la configuration, il allume la led. Dans tous les cas, il affiche un message sur le moniteur série qui explique si les condition sont remplies ou pas. Cette partie est censée être fonctionnelle (le code est présent et testé), mais il existe un conflit avec le format de réponse du Firestore et HTTPClient.getString() qui déclenche une boucle infinie.
3- Une fois le contrôle des configurations effectué, le client se lance dans une boucle pendant X secondes durant lesquelles il restera éveillé, tout en gardant la led allumée si elle l'a été précédemment.
4- Enfin, le client s'endort (deep sleep) pendant Y secondes après s'être déconnecté du WiFi.
5- Lorsqu'il sort de son hibernation, le client relance la méthode setup() et repart du point 1.
