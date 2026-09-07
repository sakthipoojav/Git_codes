#include "ADS1X15.h"

ADS1115 ADS(0x4A);

void setup()
{
  Serial.begin(115200);


  Wire.begin(23, 22);


  ADS.setGain(16);
  delay(200);
  ADS.setDataRate(7);


}


void loop()
{
  int16_t adcValue;


  adcValue = ADS.readADC_Differential_0_1();


  Serial.println(adcValue);


  delay(500);
}
