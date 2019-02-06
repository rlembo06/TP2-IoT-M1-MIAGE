import Vue from "vue";
import VueFirestore from "vue-firestore";
import firebase from "firebase/app";
import "firebase/firestore";

Vue.use(VueFirestore);
const config = {
  apiKey: "AIzaSyCnVikE2LPIIBZSRww9ui883XPZUlV9_dk",
  authDomain: "tp2-iot-m1-miage.firebaseapp.com",
  databaseURL: "https://tp2-iot-m1-miage.firebaseio.com",
  projectId: "tp2-iot-m1-miage",
  storageBucket: "tp2-iot-m1-miage.appspot.com",
  messagingSenderId: "161819819470"
};

export default firebase.initializeApp(config).firestore();
