const int potPin = A4;
const int ledPin = 9;


void setup() {
  pinMode(ledPin, OUTPUT);
}


void loop() {
  int potValue  7= analogRead(potPin);


  int pwmValue = map(potValue, 0, 1023, 0, 255);


  analogWrite(ledPin, pwmValue);
}
