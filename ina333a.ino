#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

void setup() {
  Serial.begin(115200);

  Wire.begin(23, 22);

  if (!ads.begin(0x4A)) {
    Serial.println("ADS1115 not found!");
    while (1);
  }

  ads.setGain(GAIN_ONE);

  Serial.println("ADS1115 connected!");
}

void loop() {

  int16_t adc0 = ads.readADC_SingleEnded(0);
  int16_t adc1 = ads.readADC_SingleEnded(1);
  int16_t adc2 = ads.readADC_SingleEnded(2);

  float v0 = ads.computeVolts(adc0);
  float v1 = ads.computeVolts(adc1);
  float v2 = ads.computeVolts(adc2);
  
  float vsum = v0 + v1;
  float hw_sum = v2 / 2;


  Serial.print("INA1 (A0): ");
  Serial.print(v0, 3);
  Serial.print(" V  |  INA2 (A1): ");
  Serial.print(v1, 3);
  Serial.print(" V  |  HW Sum (A2): ");
  Serial.print(hw_sum, 3);
  Serial.print(" V  |  SW Sum: ");
  Serial.print(vsum, 3);

  Serial.println(" V");

  delay(500);
 }
