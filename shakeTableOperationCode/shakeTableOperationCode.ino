#include <LiquidCrystal.h>
#include <Wire.h>
//#include "RTClib.h"

/*
All functions needed to run Shake table.
Diagnostics will run automatically, other functions can be used as needed depending on settings needed.
Include RTClib to operate real-time clock
Notes:
clockwise = switch1 HIGH and switc2 LOW
countercloskwise = switch1 LOW and switch2 HIGH
clockwise is up
*/
//LiquidCrystal lcd (44, 45, 46, 47, 48, 49);
//pin numbers
byte xMotorEN = 2; //pwm
byte yMotorEN = 4; //pwm
byte z1MotorEN = 8; //pwm
byte z2MotorEN = 9; //pwm
byte z3MotorEN = 10; //pwm
byte z4MotorEN = 11; //pwm
byte lcdGreenBacklight = 12; //pwm
byte lcdRedBacklight = 13; //pwm
byte bluetoothTX = 14; //AKA TX3
byte bluetoothRX = 15; //AKA RX3
byte lcdTX = 16;
byte xMotorSwitch1  = 22;
byte xMotorSwitch2 = 23;
byte onOffSwitch = 24;
byte yMotorSwitch1 = 26;
byte yMotorSwitch2 = 27;
byte z1MotorSwitch1 = 34;
byte z1MotorSwitch2 = 35;
byte z2MotorSwitch1 = 36;
byte z2MotorSwitch2 = 37;
byte z3MotorSwitch1 = 38;
byte z3MotorSwitch2 = 39;
byte z4MotorSwitch1 = 40;
byte z4MotorSwitch2 = 41;
byte bluetoothStatusLED = 42;
byte bluetoothOnOffSwitch = 50; //digital input
byte vibeMotorShiftRegisterData = 51; //this is daisy-chained to another shift register, so there are 2 bytes of data to be sent
byte vibeMotorShiftRegisterLatch = 52;
byte vibeMotorShiftRegisterClock = 53;
byte batteryTesterShiftRegisterData = 43;
byte batteryTesterShiftRegisterLatch = 44;
byte batteryTesterShiftRegisterClock = 45;
//byte z3BatteryTester = A3;
//byte RTCData = 46;
//byte RTCClock = 47; 
//byte z4BatteryTester = A6;
byte rotaryPot = A14; //analog input
byte linearPot = A15; //analog input
//RTC_DS1307 RTC;

/*
Z  motor definitions:
motors deifind looking from behind lcd readout screen
z1Motor: bottom right corner
z2Motor: bottom left corner
z3Motor: top center
code definitions:
code 1: entire right side (z1) up, entire left side (z2) down
code 2: entire left side (z2) up, entire right side (z1) down
code 3: entire bottom side (z1, z3) up, entire top side (z2, z4) down
code 4: entire top side (z2, z4) up, entire bottom side (z1, z3) down
code 5: bottom right corner (z1) up, top left corner (z3) down
code 6: top left corner (z3) up, bottom right corner (z1) down
code 7: top right corner (z2) up, bottom left corner (z4) down
code 8: bottom left corner (z4) up, top right corner (z2) down
any other code: turns off all motors
*/

void setup(){
  //setup of pins
  for(byte pinNum = 0; pinNum < 54; pinNum++){
    pinMode(pinNum, OUTPUT);
  }
  pinMode(bluetoothOnOffSwitch, INPUT);
  pinMode(batteryTesterShiftRegisterData, OUTPUT);
  pinMode(batteryTesterShiftRegisterLatch, OUTPUT);
  pinMode(batteryTesterShiftRegisterClock, OUTPUT);
  pinMode(bluetoothRX, INPUT);
  pinMode(rotaryPot, INPUT);
  pinMode(linearPot, INPUT);
  //start LCD Display
  digitalWrite(lcdTX, HIGH);
  Serial2.begin(9600);
  delay(100);
  Serial2.write(24); //turn on w/ cursor + no blink
  Serial2.write(12); //clear
  delay(5);
  Serial2.print("Hello There!");
  Serial2.write(13); //carriage return
  /*for(int i = 0; i < 5; i++){
    DateTime dateTime = RTC.now();
    String year = String(dateTime.year(), DEC);
    String month = String(dateTime.month(), DEC);
    String day = String(dateTime.day(), DEC);
    String hour = String(dateTime.hour(), DEC);
    String minute = String(dateTime.minute(), DEC);
    String second = String(dateTime.second(), DEC);
    String date = month + "/" + day + "/" + year;
    String time = hour + ":" + minute + ":" + second;
    Serial2.print(time);
    lineErase(1);
    delay(1000);
  }*/
  Serial2.print("Diagnostics ...");
  diagnostics();
}

void loop(){
  
}

void diagnostics(){
  //lcd screen diags
  Serial2.write(12); 
  delay(5);
  Serial2.print("Diagnostics ...");
  Serial2.write(13); //cariage return
  //battery diags
  Serial2.print("Battery Diags");
  shiftOut(batteryTesterShiftRegisterData, batteryTesterShiftRegisterClock, LSBFIRST, B10000000);
  delay(500);
  shiftOut(batteryTesterShiftRegisterData, batteryTesterShiftRegisterClock, LSBFIRST, B01000000);
  delay(500);
  shiftOut(batteryTesterShiftRegisterData, batteryTesterShiftRegisterClock, LSBFIRST, B00100000);
  delay(500);
  shiftOut(batteryTesterShiftRegisterData, batteryTesterShiftRegisterClock, LSBFIRST, B00010000);
  delay(500);
  shiftOut(batteryTesterShiftRegisterData, batteryTesterShiftRegisterClock, LSBFIRST, B00001000);
  delay(500);
  shiftOut(batteryTesterShiftRegisterData, batteryTesterShiftRegisterClock, LSBFIRST, B00000100);
  delay(500);
  shiftOut(batteryTesterShiftRegisterData, batteryTesterShiftRegisterClock, LSBFIRST, B11111100);
  delay(500);
  shiftOut(batteryTesterShiftRegisterData, batteryTesterShiftRegisterClock, LSBFIRST, B00000000);
  //motor diags
  lineErase(1);
  Serial2.print("Motor Diags");
  moveXYMotors(100, true, true, 1000); //more x clockwise for 1 sec at speed 100
  moveXYMotors(100, true, false, 1000); //more x counter-clockwise for 1 sec at speed 100
  moveXYMotors(100, false, true, 1000); //more y clockwise for 1 sec at speed 100
  moveXYMotors(100, false, false, 1000); //more y counter-clockwise for 1 sec at speed 100
  /*for(byte n = 1; n <= 8; n++){ //loop through each case for Z
    moveZMotors(100, n, 1000); 
    delay(100);
  }*/
}

void moveXYMotors(double motorSpeed, boolean isX, boolean isClockwise, int time){ //speed is max 255, time is in milliseconds
  if(isX){
    if(isClockwise){
      //set to clockwise motion
      digitalWrite(xMotorSwitch1, HIGH);
      digitalWrite(xMotorSwitch2, LOW);  
    }
    else{
      //set to clockwise motion
      digitalWrite(xMotorSwitch1, LOW);
      digitalWrite(xMotorSwitch2, HIGH);  
    }
    //turn motors on
    for(int i = 0; i < 50; i++){
      analogWrite(xMotorEN, (motorSpeed*(i/50)));
      delay(time/50);
    }
    for(int i = 0; i < 50; i++){
      analogWrite(xMotorEN, (motorSpeed - (motorSpeed*(i/50))));
      delay(time/50);
    }
    //turn motors off
    analogWrite(xMotorEN, 0);
  }
    else{
    if(isClockwise){
      //set to clockwise motion
      digitalWrite(yMotorSwitch1, HIGH);
      digitalWrite(yMotorSwitch2, LOW);   
    }
    else{
      //set to clockwise motion
      digitalWrite(yMotorSwitch1, LOW);
      digitalWrite(yMotorSwitch2, HIGH);  
    }
    //turn motors on
    for(int i = 0; i < 50; i++){
      analogWrite(yMotorEN, (motorSpeed*(i/50)));
      delay(time/50);
    }
    for(int i = 0; i < 50; i++){
      analogWrite(yMotorEN, (motorSpeed - (motorSpeed*(i/50))));
      delay(time/50);
    }
    //turn motors off
    analogWrite(yMotorEN, 0);
  }
}

void moveXYMotors(double motorSpeed, boolean isX, boolean isClockwise, boolean isOn){ //speed is max 255, no time delay
  if(isOn){
    if(isX){
      if(isClockwise){
        //set to clockwise motion
        digitalWrite(xMotorSwitch1, HIGH);
        digitalWrite(xMotorSwitch2, LOW);  
      }
      else{
        //set to clockwise motion
        digitalWrite(xMotorSwitch1, LOW);
        digitalWrite(xMotorSwitch2, HIGH);   
      }
        //turn motors on
        analogWrite(xMotorEN, motorSpeed);
    }
    else{
      if(isClockwise){
        //set to clockwise motion
        digitalWrite(yMotorSwitch1, HIGH);
        digitalWrite(yMotorSwitch2, LOW);  
      }
      else{
        //set to clockwise motion
        digitalWrite(yMotorSwitch1, LOW);
        digitalWrite(yMotorSwitch2, HIGH);   
      }
      //turn motors on
      analogWrite(yMotorEN, motorSpeed);
    }
  }
  else{
    if(isX){
      analogWrite(xMotorEN, 0);
    }
    else{
      analogWrite(yMotorEN, 0);
    }
  }
}

void moveZMotors(double motorSpeed, byte code, int time){
  /*
  motor definitions:
  motors deifind looking from behind lcd readout screen
  z1Motor: bottom right corner
  z2Motor: top right corner
  z3Motor: top left corner
  z4Motor: bottom left corner
  code definitions:
  code 1: entire right side (z1, z2) up, entire left side (z3, z4) down
  code 2: entire left side (z3, z4) up, entire right side (z1, z2) down
  code 3: entire bottom side (z1, z3) up, entire top side (z2, z4) down
  code 4: entire top side (z2, z4) up, entire bottom side (z1, z3) down
  code 5: bottom right corner (z1) up, top left corner (z3) down
  code 6: top left corner (z3) up, bottom right corner (z1) down
  code 7: top right corner (z2) up, bottom left corner (z4) down
  code 8: bottom left corner (z4) up, top right corner (z2) down
  any other code: turns off all motors
  Note: clockwise turn will be up, couterclockwise will be down
  */
  
  long startingMilliseconds = millis(); //get number of milliseconds since startup
   switch(code){
     case 1: //entire right side (z1, z2) up, entire left side (z3, z4) down
       //set clockwise
       digitalWrite(z1MotorSwitch1, HIGH);
       digitalWrite(z1MotorSwitch2, LOW);  
       digitalWrite(z2MotorSwitch1, HIGH);
       digitalWrite(z2MotorSwitch2, LOW); 
       //set counterclockwise
       digitalWrite(z3MotorSwitch1, LOW); 
       digitalWrite(z3MotorSwitch2, HIGH);
       digitalWrite(z4MotorSwitch1, LOW);
       digitalWrite(z4MotorSwitch2, HIGH);
       while((millis() - startingMilliseconds) < time){ //while amount of time has not elapsed
          analogWrite(z1MotorEN, motorSpeed);
          analogWrite(z2MotorEN, motorSpeed);
          analogWrite(z3MotorEN, motorSpeed);
          analogWrite(z4MotorEN, motorSpeed);
          delay(1);
       }
       analogWrite(z1MotorEN, 0);
       analogWrite(z2MotorEN, 0);
       analogWrite(z3MotorEN, 0);
       analogWrite(z4MotorEN, 0);
       break;
     case 2: //entire left side (z3, z4) up, entire right side (z1, z2) down
        //set counterclockwise
       digitalWrite(z1MotorSwitch1, LOW);
       digitalWrite(z1MotorSwitch2, HIGH);  
       digitalWrite(z2MotorSwitch1, LOW);
       digitalWrite(z2MotorSwitch2, HIGH); 
       //set clockwise
       digitalWrite(z3MotorSwitch1, HIGH); 
       digitalWrite(z3MotorSwitch2, LOW);
       digitalWrite(z4MotorSwitch1, HIGH);
       digitalWrite(z4MotorSwitch2, LOW);
       while((millis() - startingMilliseconds) < time){ //while amount of time has not elapsed
          analogWrite(z1MotorEN, motorSpeed);
          analogWrite(z2MotorEN, motorSpeed);
          analogWrite(z3MotorEN, motorSpeed);
          analogWrite(z4MotorEN, motorSpeed);
          delay(1);
       }
       analogWrite(z1MotorEN, 0);
       analogWrite(z2MotorEN, 0);
       analogWrite(z3MotorEN, 0);
       analogWrite(z4MotorEN, 0);
       break;
     case 3: //entire bottom side (z1, z3) up, entire top side (z2, z4) down
       //set clockwise
       digitalWrite(z1MotorSwitch1, HIGH);
       digitalWrite(z1MotorSwitch2, LOW);  
       digitalWrite(z3MotorSwitch1, HIGH);
       digitalWrite(z3MotorSwitch2, LOW); 
       //set counterclockwise
       digitalWrite(z2MotorSwitch1, LOW); 
       digitalWrite(z2MotorSwitch2, HIGH);
       digitalWrite(z4MotorSwitch1, LOW);
       digitalWrite(z4MotorSwitch2, HIGH);
       while((millis() - startingMilliseconds) < time){ //while amount of time has not elapsed
          analogWrite(z1MotorEN, motorSpeed);
          analogWrite(z2MotorEN, motorSpeed);
          analogWrite(z3MotorEN, motorSpeed);
          analogWrite(z4MotorEN, motorSpeed);
          delay(1);
       }
       analogWrite(z1MotorEN, 0);
       analogWrite(z2MotorEN, 0);
       analogWrite(z3MotorEN, 0);
       analogWrite(z4MotorEN, 0);
       break;
       case 4: //entire top side (z2, z4) up, entire bottom side (z1, z3) down
                //set clockwise
         digitalWrite(z1MotorSwitch1, HIGH);
         digitalWrite(z1MotorSwitch2, LOW);  
         digitalWrite(z3MotorSwitch1, HIGH);
         digitalWrite(z3MotorSwitch2, LOW); 
         //set counterclockwise
         digitalWrite(z2MotorSwitch1, LOW); 
         digitalWrite(z2MotorSwitch2, HIGH);
         digitalWrite(z4MotorSwitch1, LOW);
         digitalWrite(z4MotorSwitch2, HIGH);
         while((millis() - startingMilliseconds) < time){ //while amount of time has not elapsed
            analogWrite(z1MotorEN, motorSpeed);
            analogWrite(z2MotorEN, motorSpeed);
            analogWrite(z3MotorEN, motorSpeed);
            analogWrite(z4MotorEN, motorSpeed);
            delay(1);
         }
         analogWrite(z1MotorEN, 0);
         analogWrite(z2MotorEN, 0);
         analogWrite(z3MotorEN, 0);
         analogWrite(z4MotorEN, 0);
         break;
       case 5: //bottom right corner (z1) up, top left corner (z3) down
         digitalWrite(z1MotorSwitch1, HIGH);
         digitalWrite(z1MotorSwitch2, LOW);
         //set counterclockwise
         digitalWrite(z3MotorSwitch1, LOW);
         digitalWrite(z3MotorSwitch2, HIGH);
                  while((millis() - startingMilliseconds) < time){ //while amount of time has not elapsed
            analogWrite(z1MotorEN, motorSpeed);
            analogWrite(z3MotorEN, motorSpeed);
            delay(1);
         }
         analogWrite(z1MotorEN, 0);
         analogWrite(z3MotorEN, 0);
         break;
       case 6: //top left corner (z3) up, bottom right corner (z1) down
         //set counterclockwise
         digitalWrite(z1MotorSwitch1, LOW);
         digitalWrite(z1MotorSwitch2, HIGH);
         //set clockwise
         digitalWrite(z3MotorSwitch1, HIGH);
         digitalWrite(z3MotorSwitch2, LOW);
         while((millis() - startingMilliseconds) < time){ //while amount of time has not elapsed
            analogWrite(z1MotorEN, motorSpeed);
            analogWrite(z3MotorEN, motorSpeed);
            delay(1);
         }
         analogWrite(z1MotorEN, 0);
         analogWrite(z3MotorEN, 0);
         break;
       case 7: //top right corner (z2) up, bottom left corner (z4) down
         //set clockwise
         digitalWrite(z2MotorSwitch1, HIGH);
         digitalWrite(z2MotorSwitch2, LOW);
         //set counterclockwise
         digitalWrite(z4MotorSwitch1, LOW);
         digitalWrite(z4MotorSwitch2, HIGH);
         while((millis() - startingMilliseconds) < time){ //while amount of time has not elapsed
            analogWrite(z2MotorEN, motorSpeed);
            analogWrite(z4MotorEN, motorSpeed);
            delay(1);
         }
         analogWrite(z2MotorEN, 0);
         analogWrite(z4MotorEN, 0);
         break;
       case 8: //bottom left corner (z4) up, top right corner (z2) down
         //set counterclockwise
         digitalWrite(z2MotorSwitch1, LOW);
         digitalWrite(z2MotorSwitch2, HIGH);
         //set clockwise
         digitalWrite(z4MotorSwitch1, HIGH);
         digitalWrite(z4MotorSwitch2, LOW);
         while((millis() - startingMilliseconds) < time){ //while amount of time has not elapsed
            analogWrite(z2MotorEN, motorSpeed);
            analogWrite(z4MotorEN, motorSpeed);
            delay(1);
         }
         analogWrite(z2MotorEN, 0);
         analogWrite(z4MotorEN, 0);
         break;
       default: //if the code is entered incorrectly, turn motors off
         analogWrite(z1MotorEN, 0);
         analogWrite(z2MotorEN, 0);
         analogWrite(z3MotorEN, 0);
         analogWrite(z4MotorEN, 0);
         break;
   }
}

void moveZMotors(double motorSpeed, int code, boolean isOn){
/*
  motor definitions:
  motors deifind looking from behind lcd readout screen
  z1Motor: bottom right corner
  z2Motor: top right corner
  z3Motor: top left corner
  z4Motor: bottom left corner
  code definitions:
  code 1: entire right side (z1, z2) up, entire left side (z3, z4) down
  code 2: entire left side (z3, z4) up, entire right side (z1, z2) down
  code 3: entire bottom side (z1, z3) up, entire top side (z2, z4) down
  code 4: entire top side (z2, z4) up, entire bottom side (z1, z3) down
  code 5: bottom right corner (z1) up, top left corner (z3) down
  code 6: top left corner (z3) up, bottom right corner (z1) down
  code 7: top right corner (z2) up, bottom left corner (z4) down
  code 8: bottom left corner (z4) up, top right corner (z2) down
  any other code: turns off all motors
  Note: clockwise turn will be up, couterclockwise will be down
*/

  long startingMilliseconds = millis(); //get number of milliseconds since startup
    if(isOn){ 
     switch(code){
       case 1: //entire right side (z1, z2) up, entire left side (z3, z4) down
         //set clockwise
         digitalWrite(z1MotorSwitch1, HIGH);
         digitalWrite(z1MotorSwitch2, LOW);  
         digitalWrite(z2MotorSwitch1, HIGH);
         digitalWrite(z2MotorSwitch2, LOW); 
         //set counterclockwise
         digitalWrite(z3MotorSwitch1, LOW); 
         digitalWrite(z3MotorSwitch2, HIGH);
         digitalWrite(z4MotorSwitch1, LOW);
         digitalWrite(z4MotorSwitch2, HIGH);
         analogWrite(z1MotorEN, motorSpeed);
         analogWrite(z2MotorEN, motorSpeed);
         analogWrite(z3MotorEN, motorSpeed);
         analogWrite(z4MotorEN, motorSpeed);
         delay(10);
         analogWrite(z1MotorEN, 0);
         analogWrite(z2MotorEN, 0);
         analogWrite(z3MotorEN, 0);
         analogWrite(z4MotorEN, 0);
         break;
       case 2: //entire left side (z3, z4) up, entire right side (z1, z2) down
          //set counterclockwise
         digitalWrite(z1MotorSwitch1, LOW);
         digitalWrite(z1MotorSwitch2, HIGH);  
         digitalWrite(z2MotorSwitch1, LOW);
         digitalWrite(z2MotorSwitch2, HIGH); 
         //set clockwise
         digitalWrite(z3MotorSwitch1, HIGH); 
         digitalWrite(z3MotorSwitch2, LOW);
         digitalWrite(z4MotorSwitch1, HIGH);
         digitalWrite(z4MotorSwitch2, LOW);
            analogWrite(z1MotorEN, motorSpeed);
            analogWrite(z2MotorEN, motorSpeed);
            analogWrite(z3MotorEN, motorSpeed);
            analogWrite(z4MotorEN, motorSpeed);
            delay(10);
         analogWrite(z1MotorEN, 0);
         analogWrite(z2MotorEN, 0);
         analogWrite(z3MotorEN, 0);
         analogWrite(z4MotorEN, 0);
         break;
       case 3: //entire bottom side (z1, z3) up, entire top side (z2, z4) down
         //set clockwise
         digitalWrite(z1MotorSwitch1, HIGH);
         digitalWrite(z1MotorSwitch2, LOW);  
         digitalWrite(z3MotorSwitch1, HIGH);
         digitalWrite(z3MotorSwitch2, LOW); 
         //set counterclockwise
         digitalWrite(z2MotorSwitch1, LOW); 
         digitalWrite(z2MotorSwitch2, HIGH);
         digitalWrite(z4MotorSwitch1, LOW);
         digitalWrite(z4MotorSwitch2, HIGH);
            analogWrite(z1MotorEN, motorSpeed);
            analogWrite(z2MotorEN, motorSpeed);
            analogWrite(z3MotorEN, motorSpeed);
            analogWrite(z4MotorEN, motorSpeed);
            delay(10);
         analogWrite(z1MotorEN, 0);
         analogWrite(z2MotorEN, 0);
         analogWrite(z3MotorEN, 0);
         analogWrite(z4MotorEN, 0);
         break;
         case 4: //entire top side (z2, z4) up, entire bottom side (z1, z3) down
                  //set clockwise
           digitalWrite(z1MotorSwitch1, HIGH);
           digitalWrite(z1MotorSwitch2, LOW);  
           digitalWrite(z3MotorSwitch1, HIGH);
           digitalWrite(z3MotorSwitch2, LOW); 
           //set counterclockwise
           digitalWrite(z2MotorSwitch1, LOW); 
           digitalWrite(z2MotorSwitch2, HIGH);
           digitalWrite(z4MotorSwitch1, LOW);
           digitalWrite(z4MotorSwitch2, HIGH);
              analogWrite(z1MotorEN, motorSpeed);
              analogWrite(z2MotorEN, motorSpeed);
              analogWrite(z3MotorEN, motorSpeed);
              analogWrite(z4MotorEN, motorSpeed);
              delay(10);
           analogWrite(z1MotorEN, 0);
           analogWrite(z2MotorEN, 0);
           analogWrite(z3MotorEN, 0);
           analogWrite(z4MotorEN, 0);
           break;
         case 5: //bottom right corner (z1) up, top left corner (z3) down
           digitalWrite(z1MotorSwitch1, HIGH);
           digitalWrite(z1MotorSwitch2, LOW);
           //set counterclockwise
           digitalWrite(z3MotorSwitch1, LOW);
           digitalWrite(z3MotorSwitch2, HIGH);
              analogWrite(z1MotorEN, motorSpeed);
              analogWrite(z3MotorEN, motorSpeed);
              delay(10);
           analogWrite(z1MotorEN, 0);
           analogWrite(z3MotorEN, 0);
           break;
         case 6: //top left corner (z3) up, bottom right corner (z1) down
           //set counterclockwise
           digitalWrite(z1MotorSwitch1, LOW);
           digitalWrite(z1MotorSwitch2, HIGH);
           //set clockwise
           digitalWrite(z3MotorSwitch1, HIGH);
           digitalWrite(z3MotorSwitch2, LOW);
              analogWrite(z1MotorEN, motorSpeed);
              analogWrite(z3MotorEN, motorSpeed);
              delay(10);
           analogWrite(z1MotorEN, 0);
           analogWrite(z3MotorEN, 0);
           break;
         case 7: //top right corner (z2) up, bottom left corner (z4) down
           //set clockwise
           digitalWrite(z2MotorSwitch1, HIGH);
           digitalWrite(z2MotorSwitch2, LOW);
           //set counterclockwise
           digitalWrite(z4MotorSwitch1, LOW);
           digitalWrite(z4MotorSwitch2, HIGH);
              analogWrite(z2MotorEN, motorSpeed);
              analogWrite(z4MotorEN, motorSpeed);
              delay(10);
           analogWrite(z2MotorEN, 0);
           analogWrite(z4MotorEN, 0);
           break;
         case 8: //bottom left corner (z4) up, top right corner (z2) down
           //set counterclockwise
           digitalWrite(z2MotorSwitch1, LOW);
           digitalWrite(z2MotorSwitch2, HIGH);
           //set clockwise
           digitalWrite(z4MotorSwitch1, HIGH);
           digitalWrite(z4MotorSwitch2, LOW);
              analogWrite(z2MotorEN, motorSpeed);
              analogWrite(z4MotorEN, motorSpeed);
              delay(10);
           analogWrite(z2MotorEN, 0);
           analogWrite(z4MotorEN, 0);
           break;
         default: //if the code is entered incorrectly, turn motors off
           analogWrite(z1MotorEN, 0);
           analogWrite(z2MotorEN, 0);
           analogWrite(z3MotorEN, 0);
           analogWrite(z4MotorEN, 0);
           break;
     }
   } 
     else{
       switch(code){
        case 1: //entire right side (z1, z2) up, entire left side (z3, z4) down
         analogWrite(z1MotorEN, 0);
         analogWrite(z2MotorEN, 0);
         analogWrite(z3MotorEN, 0);
         analogWrite(z4MotorEN, 0);
         break;
       case 2: //entire left side (z3, z4) up, entire right side (z1, z2) down
         analogWrite(z1MotorEN, 0);
         analogWrite(z2MotorEN, 0);
         analogWrite(z3MotorEN, 0);
         analogWrite(z4MotorEN, 0);
         break;
       case 3: //entire bottom side (z1, z3) up, entire top side (z2, z4) down
         analogWrite(z1MotorEN, 0);
         analogWrite(z2MotorEN, 0);
         analogWrite(z3MotorEN, 0);
         analogWrite(z4MotorEN, 0);
         break;
         case 4: //entire top side (z2, z4) up, entire bottom side (z1, z3) down
           analogWrite(z1MotorEN, 0);
           analogWrite(z2MotorEN, 0);
           analogWrite(z3MotorEN, 0);
           analogWrite(z4MotorEN, 0);
           break;
         case 5: //bottom right corner (z1) up, top left corner (z3) down
           analogWrite(z1MotorEN, 0);
           analogWrite(z3MotorEN, 0);
           break;
         case 6: //top left corner (z3) up, bottom right corner (z1) down
           analogWrite(z1MotorEN, 0);
           analogWrite(z3MotorEN, 0);
           break;
         case 7: //top right corner (z2) up, bottom left corner (z4) down
           analogWrite(z2MotorEN, 0);
           analogWrite(z4MotorEN, 0);
           break;
         case 8: //bottom left corner (z4) up, top right corner (z2) down
           analogWrite(z2MotorEN, 0);
           analogWrite(z4MotorEN, 0);
           break;
         default: //if the code is entered incorrectly, turn motors off
           analogWrite(z1MotorEN, 0);
           analogWrite(z2MotorEN, 0);
           analogWrite(z3MotorEN, 0);
           analogWrite(z4MotorEN, 0);
           break;
       }
   }
}

void lineErase(byte line){
  if(line == 1){
    Serial2.write(148); //set cursor to line 1, position 0
    Serial2.print("                "); //erase second line
    Serial2.write(148);
  }
  else{
    Serial2.write(128); //set cursor to line 0, position 0
    Serial2.print("                "); //erase second line
    Serial2.write(128);
  }
}
