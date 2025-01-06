#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define MOISTURE_SENSOR_PIN A0
#define RELAY_PIN D3
#define MOISTURE_THRESHOLD 40

void setup() {
  Serial.begin(9600);
  Wire.begin(D1, D2);
  lcd.begin();
  lcd.backlight();
  
  pinMode(MOISTURE_SENSOR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  
  delay(2000);
  
  lcd.setCursor(4, 0);
  lcd.print("Mulai");
  for (int a = 0; a <= 15; a++) {
    lcd.setCursor(a, 1);
    lcd.print(".");
    delay(500);
  }
  
  lcd.clear(); lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Sistem Aktif");
  delay(3000);
  lcd.clear();
}

void loop() {
  int moistureValue = analogRead(MOISTURE_SENSOR_PIN);
  int moisturePercentage = map(moistureValue, 0, 1023, 0, 100);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Kelembapan: ");
  lcd.print(moisturePercentage);
  lcd.print("%");
  
  if (moisturePercentage < MOISTURE_THRESHOLD) {
    digitalWrite(RELAY_PIN, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Pompa: Mati");
  } else {
    digitalWrite(RELAY_PIN, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Pompa: Hidup");
  }
  
  delay(2000);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Kondisi Tanah:");
  
  lcd.setCursor(0, 1);
  if (moisturePercentage < MOISTURE_THRESHOLD) {
    lcd.print("Basah");
  } else {
    lcd.print("Kering");
  }
  
  delay(2000);
  
  Serial.print("Nilai Mentah Sensor: ");
  Serial.println(moistureValue);
  Serial.print("Nilai Persen: ");
  Serial.println(moisturePercentage);
}