#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define MILLI_FACTOR 1000
#define MICRO_FACTOR 1000000
#define SLEEP_TIME 60 * 2
#define UP_TIME 60 * 1

const int ledPin = 19;
const int temperaturePin = 23;
const int brightnessPin = A0;

const int serial = 9600;

OneWire oneWire(temperaturePin);
DallasTemperature temperatureSensor(&oneWire);

void ledOn() {
  digitalWrite(ledPin, HIGH);
}

void ledBlink(int numberOfBlinks) {
  for (int i = 0; i < numberOfBlinks; i++) {
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
}

void connectWifi() {
  const char * wifiSsid = "victor-mobile";
  const char * wifiPass = "parasite";
  const int connectionTimeout = 30;

  WiFi.begin(wifiSsid, wifiPass);
  Serial.print("Connecting to WiFi...");

  int connectionTimer = 0;
  while (WiFi.status() != WL_CONNECTED && connectionTimer < connectionTimeout) {
    Serial.print(".");
    connectionTimer += 1;
    delay(1000);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Connection successful in ");
  } else {
    Serial.print("Connection timeout in ");
  }

  Serial.print(connectionTimer);
  Serial.print("s. \n");
}

void createTemperatureEntry(double temperature) {
  char * restUrl = "https://firestore.googleapis.com/v1/projects/tp2-iot-m1-miage/databases/(default)/documents/temperatures";
  HTTPClient client;

  client.begin(restUrl);
  client.addHeader("Content-Type", "application/json");
  client.addHeader("Content-Length", "100");

  StaticJsonBuffer<300> jsonBuffer;
  JsonObject & root = jsonBuffer.createObject();
  JsonObject & fields = jsonBuffer.createObject();
  JsonObject & temperatureInCelsius = jsonBuffer.createObject();
  JsonObject & macAddress = jsonBuffer.createObject();

  temperatureInCelsius["doubleValue"] = temperature;
  fields["temperatureInCelsius"] = temperatureInCelsius;

  macAddress["stringValue"] = WiFi.macAddress();
  fields["macAddress"] = macAddress;

  root["fields"] = fields;

  char jsonMessageBuffer[300];
  root.prettyPrintTo(jsonMessageBuffer, sizeof(jsonMessageBuffer));
  Serial.print("Attempting to create a temperature document with a value of ");
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

void createBrightnessEntry(double brightness) {
  char * restUrl = "https://firestore.googleapis.com/v1/projects/tp2-iot-m1-miage/databases/(default)/documents/brightnesses";
  HTTPClient client;

  client.begin(restUrl);
  client.addHeader("Content-Type", "application/json");
  client.addHeader("Content-Length", "100");

  StaticJsonBuffer<300> jsonBuffer;
  JsonObject & root = jsonBuffer.createObject();
  JsonObject & fields = jsonBuffer.createObject();
  JsonObject & brightnessInLux = jsonBuffer.createObject();
  JsonObject & macAddress = jsonBuffer.createObject();

  brightnessInLux["doubleValue"] = brightness; // TODO convert brightness unit to a lux one
  fields["brightnessInLux"] = brightnessInLux;

  macAddress["stringValue"] = WiFi.macAddress();
  fields["macAddress"] = macAddress;

  root["fields"] = fields;

  char jsonMessageBuffer[300];
  root.prettyPrintTo(jsonMessageBuffer, sizeof(jsonMessageBuffer));
  Serial.print("Attempting to create a brightness document with a value of ");
  Serial.print(brightness);
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

JsonObject & getConfigurations() {
  char * restUrl = "https://firestore.googleapis.com/v1/projects/tp2-iot-m1-miage/databases/(default)/documents/configurations/cB1CljpmA9o0lRsUvuQh";
  //char * restUrl = "http://httpbin.org/ip";
  //char * restUrl = "https://httpbin.org/json";
  HTTPClient client;

  /*char * certificate = "-----BEGIN CERTIFICATE-----\n" \
"MIIDujCCAqKgAwIBAgILBAAAAAABD4Ym5g0wDQYJKoZIhvcNAQEFBQAwTDEgMB4G\n" \
"A1UECxMXR2xvYmFsU2lnbiBSb290IENBIC0gUjIxEzARBgNVBAoTCkdsb2JhbFNp\n" \
"Z24xEzARBgNVBAMTCkdsb2JhbFNpZ24wHhcNMDYxMjE1MDgwMDAwWhcNMjExMjE1\n" \
"MDgwMDAwWjBMMSAwHgYDVQQLExdHbG9iYWxTaWduIFJvb3QgQ0EgLSBSMjETMBEG\n" \
"A1UEChMKR2xvYmFsU2lnbjETMBEGA1UEAxMKR2xvYmFsU2lnbjCCASIwDQYJKoZI\n" \
"hvcNAQEBBQADggEPADCCAQoCggEBAKbPJA6+Lm8omUVCxKs+IVSbC9N/hHD6ErPL\n" \
"v4dfxn+G07IwXNb9rfF73OX4YJYJkhD10FPe+3t+c4isUoh7SqbKSaZeqKeMWhG8\n" \
"eoLrvozps6yWJQeXSpkqBy+0Hne/ig+1AnwblrjFuTosvNYSuetZfeLQBoZfXklq\n" \
"tTleiDTsvHgMCJiEbKjNS7SgfQx5TfC4LcshytVsW33hoCmEofnTlEnLJGKRILzd\n" \
"C9XZzPnqJworc5HGnRusyMvo4KD0L5CLTfuwNhv2GXqF4G3yYROIXJ/gkwpRl4pa\n" \
"zq+r1feqCapgvdzZX99yqWATXgAByUr6P6TqBwMhAo6CygPCm48CAwEAAaOBnDCB\n" \
"mTAOBgNVHQ8BAf8EBAMCAQYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUm+IH\n" \
"V2ccHsBqBt5ZtJot39wZhi4wNgYDVR0fBC8wLTAroCmgJ4YlaHR0cDovL2NybC5n\n" \
"bG9iYWxzaWduLm5ldC9yb290LXIyLmNybDAfBgNVHSMEGDAWgBSb4gdXZxwewGoG\n" \
"3lm0mi3f3BmGLjANBgkqhkiG9w0BAQUFAAOCAQEAmYFThxxol4aR7OBKuEQLq4Gs\n" \
"J0/WwbgcQ3izDJr86iw8bmEbTUsp9Z8FHSbBuOmDAGJFtqkIk7mpM0sYmsL4h4hO\n" \
"291xNBrBVNpGP+DTKqttVCL1OmLNIG+6KYnX3ZHu01yiPqFbQfXf5WRDLenVOavS\n" \
"ot+3i9DAgBkcRcAtjOj4LaR0VknFBbVPFd5uRHg5h6h+u/N5GJG79G+dwfCMNYxd\n" \
"AfvDbbnvRG15RjF+Cv6pgsH/76tuIMRQyV+dTZsXjAzlAcmgQWpzU/qlULRuJQ/7\n" \
"TBj0/VLZjmmx6BEP3ojY+x1J96relc8geMJgEtslQIxq/H5COEBkEveegeGTLg==\n" \
"-----END CERTIFICATE-----\n";*/

  client.begin(restUrl);

  int httpStatus = client.GET();

  if (httpStatus == 200) {
    String httpContent = client.getString();
    Serial.print(httpContent);
    
    StaticJsonBuffer<300> jsonBuffer;
    JsonObject & configurations = jsonBuffer.parseObject(httpContent);
    
    Serial.print("Configurations are now set to a temperature switch of ");
    Serial.print(configurations["fields"]["temperatureSwitch"].as<double>());
    Serial.print(" and a brightness switch of ");
    Serial.print(configurations["fields"]["brightnessSwitch"].as<double>());
    Serial.print(". \n");

    ledBlink(10);

    return configurations;
  }

  client.end();
}

void checkConfigurations(double temperatureValue, double brightnessValue) {
  JsonObject & configurations = getConfigurations();

  if (temperatureValue > configurations["fields"]["temperatureSwitch"] && brightnessValue > configurations["fields"]["brightnessValue"]) {
    Serial.println("Configuration requirements are met : both our temperature and brightness values are high enough.");
    ledOn();
  }
  else {
    Serial.println("Configuration requirements are not met : at least one of our temperature and brightness values wasn't high enough.");
  }
}

void stayAwake() {
  Serial.print("Staying awake for ");
  Serial.print(UP_TIME);
  Serial.print("s. \n");
    
  delay(UP_TIME * MILLI_FACTOR);
}

void hibernate() {
  WiFi.disconnect();

  Serial.print("Hibernating now for ");
  Serial.print(SLEEP_TIME);
  Serial.print("s. \n");

  esp_deep_sleep(SLEEP_TIME * MICRO_FACTOR);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(serial);
  while (!Serial);

  connectWifi();

  if (WiFi.status() == WL_CONNECTED) {
    ledBlink(2);
    
    double brightnessValue = analogRead(brightnessPin);
    
    temperatureSensor.requestTemperaturesByIndex(0); 
    double temperatureValue = temperatureSensor.getTempCByIndex(0); 

    createTemperatureEntry(temperatureValue);
    createBrightnessEntry(brightnessValue);

    //checkConfigurations(temperatureValue, brightnessValue);

    stayAwake();
    
    hibernate();
  }
}

void loop() {}
