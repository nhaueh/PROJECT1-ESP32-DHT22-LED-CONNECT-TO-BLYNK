#define BLYNK_TEMPLATE_ID "TMPL6B-8UE32k"
#define BLYNK_TEMPLATE_NAME "Project1"
#define BLYNK_AUTH_TOKEN "-OZfxIk8az_rys-NVvI5Zg65Gxmlk27O"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"

#define DHTPIN 16     
#define DHTTYPE DHT22 

#define LED_R 27      
#define LED_G 26     
#define LED_B 25     

DHT dht(DHTPIN, DHTTYPE); 

BlynkTimer timer;

void sendSensorData() {
  float h = dht.readHumidity();      
  float t = dht.readTemperature();  

  Blynk.virtualWrite(V3, t); 
  Blynk.virtualWrite(V4, h); 
}
BLYNK_WRITE(V0) {
  int value = param.asInt();
  digitalWrite(LED_R, value);
}

BLYNK_WRITE(V1) {
  int value = param.asInt();
  digitalWrite(LED_G, value);
}

BLYNK_WRITE(V2) {
  int value = param.asInt();
  digitalWrite(LED_B, value);
}

void setup() {

  Serial.begin(115200);

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
 
  dht.begin();

  Blynk.begin(BLYNK_AUTH_TOKEN, "Wokwi-GUEST", "");

  timer.setInterval(2000L, sendSensorData); 
}


void loop() {
  Blynk.run(); 
  timer.run();  
}