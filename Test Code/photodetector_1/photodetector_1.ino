// Frequency Counter Lib example

/*
  Martin Nawrath KHM LAB3
  Kunsthochschule f¸r Medien Kˆln
  Academy of Media Arts
  http://www.khm.de
  http://interface.khm.de/index.php/labor/experimente/  
  http://interface.khm.de/index.php/lab/interfaces-advanced/arduino-frequency-counter-library/
 */
#include <FreqCounter.h>


unsigned long frq;
int start = 1;
int current = 1;
String action;
char com[10];
char val;
int incomingByte = 0;
int LEDPin = 11;

void setup() {
  Serial.begin(19200);        // connect to the serial port
  Serial.println("Frequency Counter");
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, HIGH);
}

void ODMeasure() {
  // wait if any serial is going on
  FreqCounter::f_comp=10;   // Cal Value / Calibrate with professional Freq Counter
  FreqCounter::start(100);  // 100 ms Gate Time

  while (FreqCounter::f_ready == 0) 

  frq=FreqCounter::f_freq;
  Serial.println(frq);
}

void loop() {

  if (Serial.available() > 0) {
      // read the incoming byte:
      incomingByte = Serial.read();
      action = char(incomingByte);
  }
  
  if (action.equalsIgnoreCase("m")) {
    Serial.print("Measuring OD...");
    
    action = "n";
  }
  ODMeasure();
  delay(100);
}  


