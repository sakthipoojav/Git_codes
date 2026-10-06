const int buttonPin = 2;
const int led1Pin = 8;
const int led2Pin = 9;


volatile bool buttonPressed = false;
bool ledState = false;


void setup() {


  pinMode(buttonPin, INPUT_PULLUP);


  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);


  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);


  attachInterrupt(digitalPinToInterrupt(buttonPin),buttonInterrupt,FALLING);
}


void loop() {


  if (buttonPressed == true) {


    ledState = !ledState;


    if (ledState == true) {


      digitalWrite(led1Pin, HIGH);
      digitalWrite(led2Pin, LOW);


    } else {


      digitalWrite(led1Pin, LOW);
      digitalWrite(led2Pin, HIGH);
    }


    buttonPressed = false;


    delay(200);
  }
}
                                     
void buttonInterrupt() {


  buttonPressed = true;
