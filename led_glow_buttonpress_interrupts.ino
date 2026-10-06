const int buttonPin = 2;
const int ledPin = 8;


volatile bool buttonPressed = false;


void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);


  digitalWrite(ledPin, LOW);


  attachInterrupt(digitalPinToInterrupt(buttonPin),buttonInterrupt,FALLING);
}


void loop() {
  if (buttonPressed == true) {
    digitalWrite(ledPin, HIGH);
    buttonPressed = false;
  }


  if (digitalRead(buttonPin) == HIGH) {
    digitalWrite(ledPin, LOW);
  }


 
}


void buttonInterrupt() {
  buttonPressed = true;
}
