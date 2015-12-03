#include <math.h>
#include <SoftwareSerial.h>
#include <FreqCounter.h> //http://interface.khm.de/index.php/lab/interfaces-advanced/arduino-frequency-counter-library/

SoftwareSerial Serial7Segment(7, 9); //RX pin, TX pin for LED display

int LEDPin = 11;
int buttonPin = 2;
const long operationPeriod = 600000; //How long the device stays on [ms]
const long blankingPeriod = 1000;
const long integrationPeriod = 100;
const long displayPeriod = 1000;
int blankValue = 1; //in OD600 units
boolean buttonActive = false;
long operationTime = 2147483647;
double intensity;
float measuredOD;                                                                                       
float calibratedOD;
const long measurementPeriod = displayPeriod; //Over how long of a period to average the output [ms]
const int measurementNumber = (int) (measurementPeriod/integrationPeriod); //Number of measurements to average
int measurements[measurementNumber]; //This stores raw laser measurements
int currentIndex = 0; //Current index used in measument array
unsigned long frq; //square wave pulse count through integration time


void setup() {
  Serial.begin(19200);// connect to the serial port
  pinMode(LEDPin, OUTPUT);
  initDisplayOD();
}

void loop() {
  //If button is not active and it is pressed
  if(!buttonActive && buttonState()){
    Serial.println("Begin blanking mode");
    buttonActive = true;//Set button as active
    operationTime = 0;
    turnOnLED();
    Serial7Segment.print("0000");
  }
  //If button is not pressed
  if(!buttonState()){
    //Serial.println("Button not pressed");
    buttonActive = false;
  }
  //If blanking period just ended
  if(operationTime >= blankingPeriod && operationTime < blankingPeriod + integrationPeriod){
    Serial.println("Ended blanking period");
    //HACK: throws away first 20 blank value while maintaing same display update
    //      and detector reading patter to avoide incorrect blank value due to
    //      information transfer interference
    for (int i=0; i <= 2; i++) {
      Serial7Segment.print("0000");
      for (int k=0; k <= 10; k++) {
        measureOD();
      }
    }
    blankValue = getMeasurement();
    Serial.println(blankValue);
    Serial7Segment.print("    ");
  }

  //If active and not blanking
  if(operationTime < operationPeriod && operationTime >= blankingPeriod && operationTime % displayPeriod < integrationPeriod){
    //Serial.println("Displaying OD");
    displayOD(getOD());
  }
  if(operationTime<operationPeriod){
    measureOD();
  }
  //if operation just ended
  if(operationTime >= operationPeriod && operationTime < operationPeriod + integrationPeriod){
    Serial.println("Shutting down");
    //turn off display
    Serial7Segment.write('v');
    //turn off laser
    turnOffLED();
  }
  if(operationTime < operationPeriod + 2*integrationPeriod) {
    operationTime += integrationPeriod;
  }
}

double getMeasurement() {
  long total = 0;
  for(int i=0; i<measurementNumber; i++){
    total += measurements[i];
  }
  return total*1.0/measurementNumber;
}

double getOD() {
  Serial.println("Getting OD");
  intensity = getMeasurement();
  Serial.println(intensity);
  Serial.println(blankValue);
  measuredOD = -log10(intensity/blankValue);
  //calibration curve
//  calibratedOD = 1.191*measuredOD + 0.02099;
  calibratedOD = 0.9449*measuredOD + 0.005323;
  
  return calibratedOD;
}

void measureOD() {
  if(currentIndex>=measurementNumber){
    currentIndex=0;
  }
  measurements[currentIndex] = readSensor();
  currentIndex++;
}

int readSensor(){
  // Detector must be in pin 5 for arduino uno 
  // wait if any serial is going on
  FreqCounter::f_comp=10;   // Cal Value / Calibrate with professional Freq Counter
  FreqCounter::start(integrationPeriod);  // 100 ms Gate Time

  while (FreqCounter::f_ready == 0)
 
  frq = FreqCounter::f_freq; 
  return frq;
}


void turnOnLED(){
  digitalWrite(LEDPin, HIGH);
}

void turnOffLED(){
  digitalWrite(LEDPin, LOW);
}

void initButton(){
  pinMode(buttonPin, INPUT);
}

boolean buttonState() {
  return digitalRead(buttonPin);
}

void initDisplayOD() {
  Serial7Segment.begin(9600); //Talk to the Serial7Segment at 9600 bps
  Serial7Segment.write('v'); //Reset the display - this forces the cursor to return to the beginning of the display
  Serial7Segment.write(0x7A); // Brightness control
  Serial7Segment.write((byte) 25); // set to 25/255
}

char tempString[100]; //Used for sprintf

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
  //abs was rounding for some reason
  if(OD<0) {
    OD=-OD;
  }
  sprintf(tempString, "%03d", (int) (OD*100));//Shift the OD two decimal places and then format to the first 3 integers
  Serial.println(tempString);
  Serial7Segment.print(tempString); //Send serial string out the soft serial port to the S7S
  Serial7Segment.write(0x77);  // Decimal, colon, apostrophe control command
  Serial7Segment.write((byte) 2); // Turns on second decimal
}
