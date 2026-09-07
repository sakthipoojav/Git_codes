const int buttonPin = 2;
const int ledPin = LED_BUILTIN;


volatile bool buttonPressed = false;


void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);


  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, FALLING);


  SeriTtal.begin(9600);
}


void loop() {
  if (buttonPressed == true) {


    Serial.println("Button Pressed");


    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);


    buttonPressed = false;
  }
}


void buttonInterrupt() {
  buttonPressed = true;
}
