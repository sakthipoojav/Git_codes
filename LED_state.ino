int ledPin = 8;


void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  digitalWrite(ledPin, HIGH);
  Serial.println("LED is ON");
  delay(1000);


  digitalWrite(ledPin, LOW);
  Serial.println("LED is OFF");
  delay(1000);
}
