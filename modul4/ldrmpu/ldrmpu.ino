#include <Wire.h>
#include <MPU6050_tockn.h>

// Deklarasi objek dan pin
MPU6050 mpu(Wire); // Objek untuk MPU6050
int ldrPin = 32;   // Pin analog untuk LDR

void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(115200);

  // Inisialisasi I2C dan MPU6050
  Wire.begin();
  mpu.begin();

  // Kalibrasi giroskop MPU6050
  Serial.println("Kalibrasi sedang berjalan...");
  mpu.calcGyroOffsets();  // Pastikan sensor tidak bergerak saat kalibrasi
  Serial.println("Kalibrasi selesai. Sensor siap!");
}

void loop() {
  // Membaca data LDR
  int ldrValue = analogRead(ldrPin);
  Serial.print("Nilai LDR: ");
  Serial.println(ldrValue);

  // Menentukan kondisi berdasarkan nilai LDR
  if (ldrValue <= 50) {
    Serial.println("Keadaan: Sangat Terang");
  } else if (ldrValue <= 500) {
    Serial.println("Keadaan: Cahaya Terang");
  } else if (ldrValue <= 2000) {
    Serial.println("Keadaan: Redup");
  } else {
    Serial.println("Keadaan: Gelap");
  }

  // Update data dari MPU6050
  mpu.update();

  // Membaca sudut kemiringan dari MPU6050
  float ax = mpu.getAngleX(); // Sudut kemiringan sumbu X
  float ay = mpu.getAngleY(); // Sudut kemiringan sumbu Y

  Serial.print("Angle X: ");
  Serial.println(ax);
  Serial.print("Angle Y: ");
  Serial.println(ay);

  // Menentukan kondisi kemiringan berdasarkan sumbu X dan Y
  if (ax > 10) {
    Serial.println("Sensor miring: Kiri");
  } else if (ax < -10) {
    Serial.println("Sensor miring: Kanan");
  } else if (ay > 10) {
    Serial.println("Sensor miring: Depan");
  } else if (ay < -10) {
    Serial.println("Sensor miring: Belakang");
  } else {
    Serial.println("Sensor dalam posisi stabil");
  }

  // Delay untuk stabilitas pembacaan
  delay(1000);
}
