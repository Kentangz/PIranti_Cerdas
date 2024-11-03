#define LED 5
#define BUZZER 4

// Definisikan durasi nada (dalam milidetik)
int noteDurations[] = {
  400, 400, 400, 600, 400, 400, 600, 
  400, 400, 600, 400, 400, 600,
  400, 400, 600, 400, 400, 600, 400
};

// Definisikan jeda antar nada (dalam milidetik)
int pauseBetweenNotes = 100; // Jeda kecil antar nada

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  // Loop untuk memainkan "lagu" dengan durasi nada yang berbeda-beda
  for (int i = 0; i < sizeof(noteDurations) / sizeof(noteDurations[0]); i++) {
    // Menyalakan LED dan Buzzer
    digitalWrite(LED, HIGH);
    digitalWrite(BUZZER, HIGH);

    // Menahan nada sesuai durasi yang telah didefinisikan
    delay(noteDurations[i]);

    // Mematikan LED dan Buzzer
    digitalWrite(LED, LOW);
    digitalWrite(BUZZER, LOW);

    // Menunggu sebentar sebelum nada berikutnya
    delay(pauseBetweenNotes);
  }

  // Jeda sebelum melodi diulang lagi
  delay(2000); // Jeda selama 2 detik sebelum mengulang melodi
}
