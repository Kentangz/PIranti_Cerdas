#include <WiFi.h>

const String ssid = "TP-Link_2612";
const String pass = "63830903";

void setup(){
  Serial.begin(9600);
  WiFi.begin(ssid, pass);

  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Conncecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.SSID());
}

void loop(){
  
}
