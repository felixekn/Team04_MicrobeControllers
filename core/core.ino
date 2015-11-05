
#include <SoftwareSerial.h>

SoftwareSerial Serial7Segment(7, 8); //RX pin, TX pin

const long operationPeriod = 20000; //How long the device stays on [mds]
const long blankingPeriod = 1000;
const long integrationPeriod = 10;
const long displayPeriod = 1000;
int blankValue = 0; //in OD600 units
boolean buttonActive = false;
long operationTime = 2147483647;

void setup() {
  initDisplayOD();
}

void loop() {
  //If button is not active and it is pressed
  if(!buttonActive && buttonState()){
    Serial.println("Begin blanking mode");
    buttonActive = true;//Set button as active
    operationTime = 0;
    blankValue = 0;//set blankValue to 0
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
    blankValue = getOD();
    Serial7Segment.print("    ");
  }

  //If active and not blanking
  if(operationTime < operationPeriod && operationTime >= blankingPeriod && operationTime % displayPeriod < integrationPeriod){
    //Serial.println("Displaying OD");
    displayOD(getOD());
  }
  if(operationTime<operationPeriod){
    Serial.println("Measuring OD");
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
  delay(integrationPeriod);
}

const long measurementPeriod = displayPeriod; //Over how long of a period to average the output [ms]
const int measurementNumber = (int) (measurementPeriod/integrationPeriod); //Number of measurements to average
int measurements[measurementNumber]; //This stores raw laser measurements
int currentIndex = 0; //Current index used in measument array

double getOD() {
  double total = 0;
  for(int i=0; i<measurementNumber; i++){
    total += measurements[i]/1000.0;
  }
  return total/measurementNumber;
}

void measureOD() {
  if(currentIndex>=measurementNumber){
    currentIndex=0;
  }
  measurements[currentIndex] = readSensor();
  currentIndex++;
}

int readSensor(){
  return random(-1000,1000)+500;
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
  Serial.begin(9600);
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

