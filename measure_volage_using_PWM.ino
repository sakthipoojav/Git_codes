const int pwmPin = 9;


void setup() {
  pinMode(pwmPin, OUTPUT);
}


void loop() {
  analogWrite(pwmPin, 204);
}
