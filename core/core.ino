#include <math.h>
#include <SoftwareSerial.h>
#include <FreqCounter.h>

SoftwareSerial Serial7Segment(7, 8); //RX pin, TX pin

const long operationPeriod = 600000; //How long the device stays on [ms]
const long blankingPeriod = 1000;
const long integrationPeriod = 100;
const long displayPeriod = 1000;
int blankValue = 1; //in OD600 units
boolean buttonActive = false;
long operationTime = 2147483647;                                                                                       

void setup() {
  Serial.begin(19200);        // connect to the serial port
  initDisplayOD();
}

void loop() {
  //If button is not active and it is pressed
  if(!buttonActive && buttonState()){
    Serial.println("Begin blanking mode");
    buttonActive = true;//Set button as active
    operationTime = 0;
    blankValue = 1;//set blankValue to 0
    turnOnLaser();
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
    turnOffLaser();
  }
  if(operationTime < operationPeriod + 2*integrationPeriod) {
    operationTime += integrationPeriod;
  }
}

const long measurementPeriod = displayPeriod; //Over how long of a period to average the output [ms]
const int measurementNumber = (int) (measurementPeriod/integrationPeriod); //Number of measurements to average
int measurements[measurementNumber]; //This stores raw laser measurements
int currentIndex = 0; //Current index used in measument array

double getMeasurement() {
  long total = 0;
  for(int i=0; i<measurementNumber; i++){
    total += measurements[i];
  }
  return total*1.0/measurementNumber;
}

double getOD() {
  Serial.println("Getting OD");
  Serial.println(getMeasurement());
  Serial.println(blankValue);
  return -log10(getMeasurement()/blankValue);
}

void measureOD() {
  if(currentIndex>=measurementNumber){
    currentIndex=0;
  }
  measurements[currentIndex] = readSensor();
  currentIndex++;
}

unsigned long frq;

int readSensor(){
    // wait if any serial is going on
  FreqCounter::f_comp=10;   // Cal Value / Calibrate with professional Freq Counter
  FreqCounter::start(integrationPeriod);  // 100 ms Gate Time

  while (FreqCounter::f_ready == 0)
 
  frq = FreqCounter::f_freq; 
  return frq;
}

//Turns the laser on
void turnOnLaser(){
  
}
//Turns off the laser
void turnOffLaser(){
  
}

void initButton(){
  pinMode(2, INPUT);
}


boolean buttonState() {
  return digitalRead(2);
}

void initDisplayOD() {
  Serial7Segment.begin(9600); //Talk to the Serial7Segment at 9600 bps
  Serial7Segment.write('v'); //Reset the display - this forces the cursor to return to the beginning of the display
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
