#include <Wire.h>
#include <MPU6050_tockn.h>
#include <WiFi.h>

MPU6050 mpu(Wire);
const int buzzerPin = 15;
const int threshold = 10;  


const char* ssid = "TP-Link_2612";
const char* password = "63830903";

void setup() {
  Serial.begin(115200);
  Wire.begin();

  
  Serial.println("Menghubungkan ke WiFi...");
  WiFi.begin(ssid, password);
  
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nTerhubung ke jaringan: ");
  Serial.println(ssid);

  // Inisialisasi MPU6050
  mpu.begin();
  mpu.calcGyroOffsets(true);
  Serial.println("MPU6050 Terhubung");
}

void loop() {
  
  mpu.update();

 
  float pitch = mpu.getAngleX(); 
  float roll = mpu.getAngleY();  

  
  if (abs(roll) > threshold) { 
    if (roll > 0) {
      tone(buzzerPin, 1000); 
      Serial.println("Arah: Kanan");
    } else {
      tone(buzzerPin, 1200); 
      Serial.println("Arah: Kiri");
    }
  } else if (abs(pitch) > threshold) { 
    if (pitch > 0) {
      tone(buzzerPin, 1400);
      Serial.println("Arah: Depan");
    } else {
      tone(buzzerPin, 1600); 
      Serial.println("Arah: Belakang");
    }
  } else {
    noTone(buzzerPin); 
  }

  delay(200);
} 
