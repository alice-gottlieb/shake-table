/*
 Test of shift register to send same bits to one LCD screen as is displayed on another.
 */

byte lcdTX = 16;
byte outputEnable = 49;
byte data = 51;
byte latch = 52;
byte clock = 53;

void setup() {
  pinMode(lcdTX, OUTPUT);
  digitalWrite(lcdTX, HIGH);
  delay(100);
  Serial2.begin(9600);
  pinMode(outputEnable, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(clock, OUTPUT);
  digitalWrite(outputEnable, LOW);
}

void loop() {
  digitalWrite(outputEnable, LOW);
  Serial2.write(17); //turn backlight on
  Serial2.write(12); //clear
  delay(5);
  Serial2.print("1");
  digitalWrite(latch, LOW);
  shiftOut(data, clock, LSBFIRST, B00000001);
  shiftOut(data, clock, LSBFIRST, B00000000);
  digitalWrite(latch, HIGH);
  delay(1000);
  Serial2.write(12); //clear
  delay(5);
  Serial2.print("2");
  digitalWrite(latch, LOW);
  shiftOut(data, clock, LSBFIRST, B00000011);
  shiftOut(data, clock, LSBFIRST, B00000000);
  digitalWrite(latch, HIGH);
  delay(1000);
  Serial2.write(12); //clear
  delay(5);
  Serial2.print("3");
  digitalWrite(latch, LOW);
  shiftOut(data, clock, LSBFIRST, B00000111);
  shiftOut(data, clock, LSBFIRST, B00000000);
  digitalWrite(latch, HIGH);
  delay(1000);
  Serial2.write(12); //clear
  delay(5);
  Serial2.print("4");
  digitalWrite(latch, LOW);
  shiftOut(data, clock, LSBFIRST, B00001111);
  shiftOut(data, clock, LSBFIRST, B00000000);
  digitalWrite(latch, HIGH);
  delay(1000);
  Serial2.write(12); //clear
  delay(5);
  Serial2.print("5");
  digitalWrite(latch, LOW);
  shiftOut(data, clock, LSBFIRST, B00011111);
  shiftOut(data, clock, LSBFIRST, B00000000);
  digitalWrite(latch, HIGH);
  delay(1000);
  Serial2.write(12); //clear
  delay(5);
  Serial2.print("6");
  digitalWrite(latch, LOW);
  shiftOut(data, clock, LSBFIRST, B00111111);
  shiftOut(data, clock, LSBFIRST, B00000000);
  digitalWrite(latch, HIGH);
  delay(1000);
  Serial2.write(12); //clear
  delay(5);
  Serial2.print("7");
  digitalWrite(latch, LOW);
  shiftOut(data, clock, LSBFIRST, B01111111);
  shiftOut(data, clock, LSBFIRST, B00000000);
  digitalWrite(latch, HIGH);
  delay(1000);
  Serial2.write(12); //clear
  delay(5);
  Serial2.print("8");
  digitalWrite(latch, LOW);
  shiftOut(data, clock, LSBFIRST, B11111111);
  shiftOut(data, clock, LSBFIRST, B00000000);
  digitalWrite(latch, HIGH);
  delay(1000);
  Serial2.write(12); //clear
  delay(5);
  Serial2.print("9");
  digitalWrite(latch, LOW);
  shiftOut(data, clock, LSBFIRST, B11111111);
  shiftOut(data, clock, LSBFIRST, B00000001);
  digitalWrite(latch, HIGH);
  delay(1000);
  Serial2.write(12); //clear
  delay(5);
  Serial2.print("10");
  digitalWrite(latch, LOW);
  shiftOut(data, clock, LSBFIRST, B11111111);
  shiftOut(data, clock, LSBFIRST, B00000011);
  digitalWrite(latch, HIGH);
  delay(1000);
  Serial2.write(12); //clear
  delay(5);
  Serial2.print("11");
  digitalWrite(latch, LOW);
  shiftOut(data, clock, LSBFIRST, B11111111);
  shiftOut(data, clock, LSBFIRST, B00000111);
  digitalWrite(latch, HIGH);
  delay(1000);
  Serial2.write(12); //clear
  delay(5);
  Serial2.print("12");
  digitalWrite(latch, LOW);
  shiftOut(data, clock, LSBFIRST, B11111111);
  shiftOut(data, clock, LSBFIRST, B00001111);
  digitalWrite(latch, HIGH);
  delay(1000);
  Serial2.write(12); //clear
  delay(5);
  Serial2.print("13");
  digitalWrite(latch, LOW);
  shiftOut(data, clock, LSBFIRST, B11111111);
  shiftOut(data, clock, LSBFIRST, B00011111);
  digitalWrite(latch, HIGH);
  delay(1000);
  Serial2.write(12); //clear
  delay(5);
  Serial2.print("14");
  digitalWrite(latch, LOW);
  shiftOut(data, clock, LSBFIRST, B11111111);
  shiftOut(data, clock, LSBFIRST, B00111111);
  digitalWrite(latch, HIGH);
  delay(1000);
  Serial2.write(12); //clear
  delay(5);
  Serial2.print("15");
  digitalWrite(latch, LOW);
  shiftOut(data, clock, LSBFIRST, B11111111);
  shiftOut(data, clock, LSBFIRST, B01111111);
  digitalWrite(latch, HIGH);
  delay(1000);
  Serial2.write(12); //clear
  delay(5);
  Serial2.print("16");
  digitalWrite(latch, LOW);
  shiftOut(data, clock, LSBFIRST, B11111111);
  shiftOut(data, clock, LSBFIRST, B11111111);
  digitalWrite(latch, HIGH);
  delay(1000);
  Serial2.write(12); //clear
  delay(5);
  Serial2.print("Everything!");
  //digitalWrite(outputEnable, HIGH);
  digitalWrite(latch, LOW);
  shiftOut(data, clock, LSBFIRST, B11111111);
  shiftOut(data, clock, LSBFIRST, B11111111);
  digitalWrite(latch, HIGH);
  delay(1000);
  digitalWrite(latch, LOW);
  shiftOut(data, clock, LSBFIRST, B00000000);
  shiftOut(data, clock, LSBFIRST, B00000000);
  digitalWrite(latch, HIGH);
  delay(1000);
}
