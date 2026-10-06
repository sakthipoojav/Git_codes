int ledPins[] = {7, 8, 12, 13};
int decimalValue;




void setup() {
  Serial.begin(9600);


  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }


  Serial.println("Enter a decimal number from 0 to 15:");
}


void loop() {


  if (Serial.available() > 0) {


    decimalValue = Serial.parseInt();


    while (Serial.available()) {
      Serial.read();
    }


    if (decimalValue >= 0 && decimalValue <= 15) {


      Serial.print("Decimal: ");
      Serial.println(decimalValue);


      Serial.print("Binary: ");


      for (int i = 0; i < 4; i++) {


        int bitState = bitRead(decimalValue, i);


        digitalWrite(ledPins[i], bitState);


        Serial.print(bitState);
      }


      Serial.println();


      delay(1000);


      for (int i = 0; i < 4; i++) {
        digitalWrite(ledPins[i], LOW);
      }


      Serial.println("Enter another number from 0 to 15:");
    }
  }
}
