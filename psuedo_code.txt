integrationTime is 0.5 seconds //Over how long of a period to average the output
operationTime is 10 minutes //How long the device stays on
operationFrequency is 50 //The number of measurements to take in 1 second
measurementNumber is operationFrequency*integrationTime //Number of measurements to average
measurements is an empty int array of size measurementNumber //This stores raw laser measurements
currentIndex is 0 //Current index used in measument array
blankValue is 0//in OD600 units
buttonActive is false
opertionCount is 0 //iterations untill shutdown
blankingCount is 0 //iterations until blanking is done

loop
  If button is not active and it is pressed
    Set button as active
    Set operationCount to operationTime
    Set blankingCount to blankingTime
    set blankValue to 0
    Display Blanking symbols
  If button is not pressed
    Set button to not active
  If blanking period just ended
    Calculate blank OD
    set blankValue to blank OD
  If active and not blanking
    calculate time averaged OD600
    display time averaged OD600
  if active
    record OD
  if operation just ended
    turn off display
    turn off laser
  if active
    decrement operationCount
  if blanking
    decrement BlankingCount
  If active
    record OD600
    
//Takes a OD600 value and displays it on the 7 segment display
displayOD(double)
//Returns a value from the sensor in arbitrary units taking into account laser intensity calibration
getMeasurement()
//Turns the laser on
turnOnLaser()
//Turns off the laser
turnOffLaser()
//Returns the boolean state of the button
isButtonPressed()