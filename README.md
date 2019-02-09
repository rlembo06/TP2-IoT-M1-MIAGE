# TP2 - IoT - M1 MIAGE - Requêtes Client / ESP32

[Consignes (Cliquer)](http://www.i3s.unice.fr/~menez/M1Miage/TP2/tp2.pdf)

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
- [URI de températures (Cliquer)](https://firestore.googleapis.com/v1/projects/tp2-iot-m1-miage/databases/(default)/documents/temperatures)
- [URI de luminosités (Cliquer)](https://firestore.googleapis.com/v1/projects/tp2-iot-m1-miage/databases/(default)/documents/brightnesses)

![alt text](https://firebasestorage.googleapis.com/v0/b/tp2-iot-m1-miage.appspot.com/o/data-temperatures.png?alt=media&token=881811ba-e223-4980-a389-319899310aa3)

### Contrôle :
Le contrôle est économe car il se réveil toutes les 20 min (actuellement), et poste ses captures de températures et de luminosités.