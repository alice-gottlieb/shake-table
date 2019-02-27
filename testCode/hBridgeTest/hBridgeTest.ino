/*
 Test using one hBridge to switch multiple motors. One in the X and one in the Y direction.
 Video of circuit used and test in operation inside picturesAndVideos
 */

byte xswitch1 = 22;
byte xswitch2 = 23;
byte xEN = 2;
byte yswitch1 = 26;
byte yswitch2 = 27;
byte yEN = 4;
byte speed;

void setup() {
  pinMode(xswitch1, OUTPUT);
  pinMode(xswitch2, OUTPUT);
  pinMode(xEN, OUTPUT);
  pinMode(yswitch1, OUTPUT);
  pinMode(yswitch2, OUTPUT);
  pinMode(yEN, OUTPUT);
}

void loop() {
  //clockwise
  analogWrite(xEN, 0);
  analogWrite(yEN, 0);
  digitalWrite(xswitch1, HIGH);
  digitalWrite(xswitch2, LOW);
  digitalWrite(yswitch1, HIGH);
  digitalWrite(yswitch2, LOW);
  //speed up
  while(speed < 255){
    analogWrite(xEN, speed);
    analogWrite(yEN, speed);
    speed += 1;
    delay(50);
  }
 while(speed > 0){
    analogWrite(xEN, speed);
    analogWrite(yEN, speed);
    speed -= 1;
    delay(50);
  }
  //counterclockwise
  analogWrite(xEN, 0);
  analogWrite(yEN, 0);
  digitalWrite(xswitch1, LOW);
  digitalWrite(xswitch2, HIGH);
  digitalWrite(yswitch1, LOW);
  digitalWrite(yswitch2, HIGH);
  //speed up
  while(speed < 255){
    analogWrite(xEN, speed);
    analogWrite(yEN, speed);
    speed += 1;
    delay(50);
  }
 while(speed > 0){
    analogWrite(xEN, speed);
    analogWrite(yEN, speed);
    speed -= 1;
    delay(50);
  }
}
