int LED_PIN = 2;


void blinkLED(void *parameter)
{
  pinMode(LED_PIN, OUTPUT);


  while (1)
  {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(1000));


    digitalWrite(LED_PIN, LOW);
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}


void setup()
{
  xTaskCreate(
    blinkLED,
    "LED Task",
    2048,
    NULL,
    1,
    NULL
  );
}


void loop()
{
}
