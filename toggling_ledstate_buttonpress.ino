const int buttonPin = 2;
const int led1Pin = 7;
const int led2Pin = 8;


volatile bool buttonPressed = false;
bool toggleMode = false;


void setup() {
  pinMode(buttonPin, INPUT_PULLUP);


  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);


    Serial.begin(9600);


  attachInterrupt(digitalPinToInterrupt(buttonPin),buttonInterrupt,FALLING);
}


void loop() {


  if (toggleMode == true) {
    digitalWrite(led1Pin, HIGH);
    digitalWrite(led2Pin, LOW);
  }
  else {
    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, HIGH);


  }


  delay(1000);
}
void buttonInterrupt() {
  toggleMode = !toggleMode;
}
