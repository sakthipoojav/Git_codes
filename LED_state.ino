int ledPin = 8;


void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  // Turn LED ON
  digitalWrite(ledPin, HIGH);
  Serial.println("LED is ON");
  delay(1000);


  // Turn LED OFF
  digitalWrite(ledPin, LOW);
  Serial.println("LED is OFF");
  delay(1000);
}
