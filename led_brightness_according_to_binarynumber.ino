int ledPins[] = {7, 8, 12, 13};
int decimalValue = 4;
     
void setup() {


  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}


void loop() {
 
  for (int i = 0; i < 4; i++) {
    int bitState = bitRead(decimalValue, i);
    digitalWrite(ledPins[i], bitState);      
  }




}
