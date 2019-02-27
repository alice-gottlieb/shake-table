#include <Wire.h>
#include "RTClib.h"

/*
 Test of real time clock printed to LCD screen
 */


byte lcdTX = 16;

RTC_DS1307 RTC;
void setup() {
  pinMode(lcdTX, OUTPUT);
  digitalWrite(lcdTX, HIGH);
  Serial2.begin(9600);
  Serial2.write(22);
  Serial2.write(12);                 // Clear             
  Serial2.write(17);       
  Wire.begin();
  RTC.begin();
  //if(!(RTC.isrunning())){
   //RTC.adjust(DateTime(__DATE__, __TIME__));
  //}
}

void loop() {
  DateTime dateTime = RTC.now();
  String year = String(dateTime.year(), DEC);
  String month = String(dateTime.month(), DEC);
  String day = String(dateTime.day(), DEC);
  String hour = String(dateTime.hour(), DEC);
  String minute = String(dateTime.minute(), DEC);
  String second = String(dateTime.second(), DEC);
  String date = month + "/" + day + "/" + year;
  String time = hour + ":" + minute + ":" + second;
  Serial2.print(date);
  Serial2.write(13);
  Serial2.print(time);
  delay(1000);
  Serial2.write(12);
}
