const int buttonPin = 2;


volatile bool buttonPressed = false;
bool toggleMode = false;


void setup() {
  pinMode(buttonPin, INPUT_PULLUP);


  Serial.begin(9600);


  attachInterrupt(digitalPinToInterrupt(buttonPin),buttonInterrupt,FALLING);
}


void loop() {
 
  if (toggleMode == true) {
    Serial.println("Mode 1");
  }
  else {
    Serial.println("Mode 2");
  }


  delay(1000);
}


void buttonInterrupt() {
  toggleMode =! toggleMode;
