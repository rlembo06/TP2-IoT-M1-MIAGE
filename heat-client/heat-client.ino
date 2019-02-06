#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define MICRO_FACTOR 1000000
#define SLEEP_TIME 20
//#define TIME_TO_UP 10

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
  const int connectionTimeout = 180;
 
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
  JsonObject& macAddress = jsonBuffer.createObject(); 

  temperatureInCelsius["doubleValue"] = temperature;
  fields["temperatureInCelsius"] = temperatureInCelsius;

  macAddress["stringValue"] = WiFi.macAddress();
  fields["macAddress"] = macAddress;
  
  root["fields"] = fields;

  char jsonMessageBuffer[300];
  root.prettyPrintTo(jsonMessageBuffer, sizeof(jsonMessageBuffer));
  Serial.print("Attempting to create a document with a value of ");
  Serial.print(temperature);
  Serial.print(" from address ");
  Serial.print(WiFi.macAddress());
  Serial.print(". \n");
  
  int httpStatus = client.POST(jsonMessageBuffer);

  if (httpStatus == 200) {
    Serial.println("Firestore responded successfully.");
    ledBlink(10);
  }

  client.end();
}

void hibernate() {
  Serial.println("Hibernating now.");
  
  WiFi.disconnect();
  //esp_wifi_stop();
  //esp_sleep_enable_timer_wakeup(SLEEP_TIME * MICRO_FACTOR);
  
  esp_deep_sleep(SLEEP_TIME * MICRO_FACTOR);
  Serial.print("Should be asleep now, here goes hoping you don't see this...");
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

    hibernate();
  }
}

void loop(){
}
