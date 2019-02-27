#include <LiquidCrystal.h>

/*
 Standard LCD test with no colored backlight.
 */

byte RS = 2;
byte EN = 3;
byte D4 = 4;
byte D5 = 5;
byte D6 = 6;
byte D7 = 7;
byte V0 = 8;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup() {
  pinMode(RS, OUTPUT);
  pinMode(EN, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(V0, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("Hello");
}

void loop() {
 // lcd.setCursor(0, 1);
  digitalWrite(V0, HIGH);
  delay(1000);
  digitalWrite(V0, LOW);

}
