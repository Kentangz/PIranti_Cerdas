#define LED 5
#define BUZZER 4

// Frekuensi nada dalam Hertz
#define note_c4 261.63
#define note_c4has 277.18
#define note_d4 293.66
#define note_d4has 311.13
#define note_g4 392.00
#define note_g4has 415.30
#define note_a4has 466.16
#define note_c5 523.25

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  playMusic();

  // Jeda sebelum melodi diulang lagi
  delay(2000); // Jeda selama 2 detik sebelum mengulang melodi
}


void playMusic(){
  tone(BUZZER, note_c4, 860); delay(300);
  tone(BUZZER, note_c4has, 350); delay(300);
  tone(BUZZER, note_d4has, 200); delay(650);
  tone(BUZZER, note_d4has, 200); delay(650);
  tone(BUZZER, note_d4has, 200); delay(690);
  tone(BUZZER, note_g4has, 210); delay(550);
  tone(BUZZER, note_g4has, 210); delay(650);
  tone(BUZZER, note_c5, 230); delay(500);
  tone(BUZZER, note_c5, 600); delay(350);
  tone(BUZZER, note_a4has, 220); delay(390);
  tone(BUZZER, note_g4has, 170); delay(600);
  tone(BUZZER, note_g4, 150); delay(300);
  tone(BUZZER, note_g4has, 150); delay(300);
  tone(BUZZER, note_a4has, 150); delay(600);
  tone(BUZZER, note_c5, 600); delay(500);
  tone(BUZZER, note_a4has, 170); delay(390);
  tone(BUZZER, note_g4has, 150); delay(1000);
}