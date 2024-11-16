#define LIGHT_SENSOR_PIN 4

void setup(){
  Serial.begin(9600);
}

void loop(){
  int analogValue = analogRead(LIGHT_SENSOR_PIN);
  Serial.print("analog Value = ");
  Serial.print(analogValue);
  Serial.println("");
  delay(500);
}