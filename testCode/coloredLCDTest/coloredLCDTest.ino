/*
 test of new LCD with colored backlight.
 */

/*
Codes for LCD screen:
12: clears the display and sets cursore at (0, 0)
17: turns backligth on
18: turns backlight off
212: sets up sounds for quarter not
220: Plays A
*/
int lcdTX = 16;

void setup() {
  pinMode(lcdTX, OUTPUT);
  digitalWrite(lcdTX, HIGH);
  Serial2.begin(9600);
  delay(100);
  Serial2.write(22);
  Serial2.write(12);                 // Clear             
  Serial2.write(17);                 // Turn backlight on
  delay(5);                           // Required delay
  Serial2.print("Meow");  // First line
  delay(1000);
  Serial2.print(" Meow");
  delay(1000);
  Serial2.write(24);
  Serial2.write(8);
  Serial2.write(8);
  Serial2.write(8);
  Serial2.write(8);
  delay(1000);
  oneByOneWriter("Ruff", 500);
  Serial2.write(13);                 // Form feed
  Serial2.print("A");   // Second line
  Serial2.write(212);                // Quarter note
  Serial2.write(220);                // A tone
  delay(500);
  Serial2.print("A#");
  Serial2.write(221);
  delay(500);
  Serial2.print("B");
  Serial2.write(222);
  delay(500);
  Serial2.print("C");
  Serial2.write(223);
  delay(500);
  Serial2.print("C#");
  Serial2.write(224);
  delay(500);
  Serial2.print("D");
  Serial2.write(225);
  delay(500);
  Serial2.print("D#");
  Serial2.write(226);
  delay(500);
  Serial2.print("E");
  Serial2.write(227);
  delay(500);
  Serial2.print("F");
  Serial2.write(228);
  delay(500);
  Serial2.print("F#");
  Serial2.write(229);
  delay(500);
  Serial2.print("G");
  Serial2.write(230);
  delay(3000);                        // Wait 3 seconds
  Serial2.write(18);                 // Turn backlight off
}

void loop() {
  // put your main code here, to run repeatedly:

}

void oneByOneWriter(String string){
  int i = 0;
  String stringArray[33] = {""};
  for(i; i < string.length(); i++){
    stringArray[i] = string.substring(i, (i + 1));
  }
  for(int a = 0; a <= i; a++){
    Serial2.print(stringArray[a]);
    delay(500);
  }
}

void oneByOneWriter(String string, int delayTime){
  int i = 0;
  String stringArray[33] = {""};
  for(i; i < string.length(); i++){
    stringArray[i] = string.substring(i, (i + 1));
  }
  for(int a = 0; a <= i; a++){
    Serial2.print(stringArray[a]);
    delay(delayTime);
  }
}
