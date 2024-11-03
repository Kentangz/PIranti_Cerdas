#include <Wire.h>
#include <MPU6050.h>
#include <WiFi.h>

MPU6050 mpu;
const int buzzerPin = 15;
int threshold = 15000;  // Ambang batas perubahan sudut, sesuaikan jika perlu

// Ganti dengan SSID dan Password Anda
const char* ssid = "TP-Link_2612";
const char* password = "63830903";

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Menghubungkan ke WiFi
  Serial.println("Menghubungkan ke WiFi...");
  WiFi.begin(ssid, password);

  // Menunggu hingga terhubung
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // Informasi koneksi
  Serial.print("Terhubung ke jaringan: ");
  Serial.println(ssid);

  // Inisialisasi MPU6050
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("Tidak dapat menemukan sensor MPU6050");
    while (1);
  }
  Serial.println("MPU6050 Terhubung");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    int16_t ax, ay, az;
    int16_t gx, gy, gz;

    // Membaca data dari sensor
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // Memeriksa perubahan sudut dan menyalakan buzzer sesuai arah
    if (abs(gy) > threshold) {
      if (gy > 0) {
        tone(buzzerPin, 1000); // bunyi untuk kanan
        Serial.println("Arah: Kanan");
      } else {
        tone(buzzerPin, 1200); // bunyi untuk kiri
        Serial.println("Arah: Kiri");
      }
    } else if (abs(gx) > threshold) {
      if (gx > 0) {
        tone(buzzerPin, 1400); // bunyi untuk depan
        Serial.println("Arah: Depan");
      } else {
        tone(buzzerPin, 1600); // bunyi untuk belakang
        Serial.println("Arah: Belakang");
      }
    } else {
      noTone(buzzerPin); // Tidak ada peringatan
    }

    delay(200);
  }
}