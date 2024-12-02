#define BLYNK_TEMPLATE_ID "hai"
#define BLYNK_TEMPLATE_NAME "hai"
#define BLYNK_AUTH_TOKEN "hai"
#define BLYNK_PRINT Serial 
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "hai";  
char pass[] = "hai";

const int ldrPin = 34;
const int relayPin = 5;

bool manualMode = false;
bool relayState = false;

BlynkTimer timer;

BLYNK_WRITE(V3) {
  //toggle V3 (0 = OFF, 1 = ON)
  manualMode = param.asInt();
  if (manualMode) {
    Serial.println("Manual mode is ON");
  } else {
    Serial.println("Manual mode is OFF");
  }
  if (manualMode) {
    if (relayState) {
      digitalWrite(relayPin, HIGH);
      Serial.println("Relay is ON");
      Blynk.virtualWrite(V2, "ON");
    } else {
      digitalWrite(relayPin, LOW);
      Serial.println("Relay is OFF");
      Blynk.virtualWrite(V2, "OFF");
    }
  }
}

BLYNK_WRITE(V4) {
  //toggle V4 (0 = OFF, 1 = ON)
  relayState = param.asInt();
  
  if (manualMode) {
    if (relayState) {
      digitalWrite(relayPin, HIGH);  
      Serial.println("Relay turned ON via manual control");
      Blynk.virtualWrite(V2, "ON");
    } else {
      digitalWrite(relayPin, LOW); 
      Serial.println("Relay turned OFF via manual control");
      Blynk.virtualWrite(V2, "OFF");
    }
  }
}

void sendData() {
  if (!manualMode) {
    int ldrValue = analogRead(ldrPin); 
    Serial.print("LDR VALUE: ");
    Serial.println(ldrValue);

    int ldrPercent = map(ldrValue, 0, 4095, 100, 0);
    Serial.print("LDR PERCENT: ");
    Serial.println(ldrPercent);
    Blynk.virtualWrite(V0, ldrPercent);

    if (ldrValue > 2048) {
      digitalWrite(relayPin, HIGH);
      Blynk.virtualWrite(V1, "Dark");
      Blynk.virtualWrite(V2, "ON");
    } else {
      digitalWrite(relayPin, LOW);
      Blynk.virtualWrite(V1, "Bright");
      Blynk.virtualWrite(V2, "OFF");
    }
  }
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); 
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  timer.setInterval(1000L, sendData);
}

void loop() {
  Blynk.run();    
  timer.run(); 
}
