#include <WiFi.h>

const String ssid = "Y";

void setup(){
  Serial.begin(9600);
  WiFi.begin(ssid);
  
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.SSID());
}

void loop(){

}