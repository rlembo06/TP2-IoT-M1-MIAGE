#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const int ledPin = 23;
const int tempPin = 19;
const int lightPin = A0;

const int serial = 9600;

void ledBlink(int numberOfBlinks) {
  for (int i=0; i<numberOfBlinks; i++) {
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
}

void connectWifi(){
  const char* wifiSsid = "victor-mobile";
  const char* wifiPass = "parasite";
  const int connectionTimeout = 15;
 
 WiFi.begin(wifiSsid, wifiPass);
 Serial.print("Connecting to WiFi...");


 int connectionTimer = 0;
 while(WiFi.status() != WL_CONNECTED && connectionTimer < connectionTimeout){
   Serial.print(".");
   connectionTimer += 1;
   delay(1000);
 }

 if (WiFi.status() == WL_CONNECTED) {
  Serial.print("Connection successful in "); 
 }
 else {
  Serial.print("Connection timeout in ");  
 } 

 Serial.print(connectionTimer);
 Serial.print("s. \n");    
}

void createTemperatureEntry(double temperature) {
  char* restUrl = "https://firestore.googleapis.com/v1/projects/tp2-iot-m1-miage/databases/(default)/documents/temperatures";
  HTTPClient client;
  
  client.begin(restUrl);
  client.addHeader("Content-Type", "application/json");
  client.addHeader("Content-Length", "100");

  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject(); 
  JsonObject& fields = jsonBuffer.createObject(); 
  JsonObject& temperatureInCelsius = jsonBuffer.createObject(); 

  temperatureInCelsius["doubleValue"] = temperature;
  fields["temperatureInCelsius"] = temperatureInCelsius;
  root["fields"] = fields;

  char jsonMessageBuffer[300];
  root.prettyPrintTo(jsonMessageBuffer, sizeof(jsonMessageBuffer));
  Serial.println(jsonMessageBuffer);
  
  int httpStatus = client.POST(jsonMessageBuffer);
  Serial.println(httpStatus);

  if (httpStatus == 200) {
    ledBlink(10);
  }

  String Contents = client.getString();
  Serial.print(Contents);
  Serial.print("\n");

  client.end();
}

void setup(){ 
  pinMode(ledPin , OUTPUT) ;
  Serial.begin(serial);
  while (!Serial);

  connectWifi();

  if (WiFi.status() == WL_CONNECTED) {
    ledBlink(2);

    int sensorValue = analogRead(lightPin) ; // temporary while we don't have the temperature sensor... TODO fix
    createTemperatureEntry(sensorValue);
  }
}

void loop(){
}
