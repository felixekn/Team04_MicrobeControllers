int pin = 5;
int LEDPin = 11;

unsigned long duration;


void setup()

{
  Serial.begin(19200);
  pinMode(pin, INPUT);
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, HIGH);
}



void loop()

{

  duration = pulseIn(pin, LOW);
  Serial.println(duration);
  delay(1000);
}
