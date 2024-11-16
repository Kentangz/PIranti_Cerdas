#include "WiFi.h"

const char* primarySSID = "TP-Link_2612";
const char* primaryPassword = "63830903";

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println("Memindai jaringan Wi-Fi...");

  int n = WiFi.scanNetworks();
  if (n == 0) {
    Serial.println("Tidak ada jaringan yang ditemukan.");
  } else {
    Serial.println("Daftar jaringan yang ditemukan:");
    for (int i = 0; i < n; ++i) {
      String ssid = WiFi.SSID(i);
      int rssi = WiFi.RSSI(i);
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(ssid);
      Serial.print(" (Kekuatan sinyal: ");
      Serial.print(rssi);
      Serial.print(" dBm, Enkripsi: ");
      Serial.println(WiFi.encryptionType(i) == WIFI_AUTH_OPEN ? "Terbuka" : "Terenkripsi");
    }
  }

  bool primaryNet = false;
  int openNet = -1;
  

  for (int i = 0; i < n; ++i) {
    String ssid = WiFi.SSID(i);

    if (ssid == primarySSID) {
      primaryNet = true;
      break;
    }
    if (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) {
      if (openNet == -1 || WiFi.RSSI(i) > WiFi.RSSI(openNet)) {
        openNet = i;
      }
    }
  }

  if (primaryNet) {
    Serial.print("Menghubungkan ke jaringan utama: ");
    Serial.println(primarySSID);
    WiFi.begin(primarySSID, primaryPassword);

    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }
    Serial.println("\nTerhubung ke jaringan utama!");
  } 
  else if (openNet != -1) {
    String openSSID = WiFi.SSID(openNet);
    Serial.print("Menghubungkan ke jaringan lain!: ");
    Serial.println(openSSID);
    WiFi.begin(openSSID.c_str());

    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }
    Serial.println("\nTerhubung ke jaringan terbuka!");
  } else {
    Serial.println("Tidak ada jaringan yang tersedia untuk terhubung.");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Alamat IP: ");
    Serial.println(WiFi.localIP());
  }
}

void loop() {
}
