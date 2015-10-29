/*
 11-4-2012
 Spark Fun Electronics
 Nathan Seidle
 
 This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

 Serial7Segment is an open source seven segment display. 

 This is example code that shows how to display basic numbers and control the decimal, colon, and AM/PM dot.
 
 Note: This code works with displays the support the center colon and extra dots (AM/PM, not decimals).
 
 Note: This code expects the display to be listening at 9600bps. If your display is not at 9600bps, you can
 do a software or hardware reset. See the Wiki for more info: 
 http://github.com/sparkfun/Serial7SegmentDisplay/wiki/Special-Commands#wiki-baud
 
 To get this code to work, attached an Serial7Segment to an Arduino Uno using the following pins:
 Pin 7 on Uno (software serial RX) to TX on Serial7Segment
 Pin 8 on Uno to RX on Serial7Segment
 VIN to PWR
 GND to GND
 
*/

#include <SoftwareSerial.h>

SoftwareSerial Serial7Segment(7, 8); //RX pin, TX pin

char tempString[100]; //Used for sprintf

void setup() {

  initDisplayOD();
  unitTestDisplayOD();
}

void loop() 
{
}

void initDisplayOD() {
  Serial.begin(9600);
  Serial7Segment.begin(9600); //Talk to the Serial7Segment at 9600 bps
  Serial7Segment.write('v'); //Reset the display - this forces the cursor to return to the beginning of the display
}

void unitTestDisplayOD() {
  int  unitDelay = 1000;
  displayOD(.033);
  Serial.println(" 0.03 (.033)");
  delay(unitDelay);
  displayOD(.2);
  Serial.println(" 0.20 (.2)");
  delay(unitDelay);
  displayOD(200);
  Serial.println("---- (200)");
  delay(unitDelay);
  displayOD(200.1);
  Serial.println("---- (200.1)");
  delay(unitDelay);
  displayOD(-1.1);
  Serial.println("-1.10 (-1.1)");
  delay(unitDelay);
  displayOD(-20);
  Serial.println("---- (-20)");
  delay(unitDelay);
}

void displayOD(double OD) {
  //If Overloaded
  if(abs(OD)>10) {
    Serial7Segment.print("----");
    Serial7Segment.write(0x77);  // Decimal, colon, apostrophe control command
    Serial7Segment.write((byte) 0); // Turns on second decimal
    return;
  }
  if(OD<0) {
    Serial7Segment.print("-");//Print a negative space
  }
  else {
    Serial7Segment.print(" ");//Move cursor forward
  }
  sprintf(tempString, "%03d", (int) (abs(OD)*100));//Shift the OD two decimal places and then format to the first 3 integers
  Serial7Segment.print(tempString); //Send serial string out the soft serial port to the S7S
  Serial7Segment.write(0x77);  // Decimal, colon, apostrophe control command
  Serial7Segment.write((byte) 2); // Turns on second decimal
}

