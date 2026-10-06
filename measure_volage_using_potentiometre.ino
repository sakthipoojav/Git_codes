const int potPin = A3;


void setup() {
  Serial.begin(9600);
}


void loop() {
  int adcValue = analogRead(potPin);


  float voltage = adcValue * (3.3 / 1023.0);


  Serial.println(voltage);


  delay(1000);
}
