#define LED_PIN 2
#define BUTTON_PIN 23


TaskHandle_t ledTaskHandle;
TaskHandle_t buttonTaskHandle;




void ledTask(void *parameter)
{
  while (1)
  {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}




void buttonTask(void *parameter)
{
  bool suspended = false;


  while (1)
  {
    if (digitalRead(BUTTON_PIN) == LOW)
    {
      vTaskDelay(pdMS_TO_TICKS(150));
      if (digitalRead(BUTTON_PIN) == LOW)
      {
        if (suspended == false)
        {
          vTaskSuspend(ledTaskHandle);
          digitalWrite(LED_PIN, LOW);


          Serial.println("LED OFF");
          suspended = true;
        }
        else
        {
          vTaskResume(ledTaskHandle);


          Serial.println("LED ON");
          suspended = false;
        }


        // while (digitalRead(BUTTON_PIN) == LOW)
        // {
        //   vTaskDelay(pdMS_TO_TICKS(100));
        // }
      }
    }


    vTaskDelay(pdMS_TO_TICKS(50));
  }
}




void setup()
{
  Serial.begin(115200);


  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);


  xTaskCreate(
    ledTask,
    "LED Task",
    1000,
    NULL,
    1,
    &ledTaskHandle
  );


  xTaskCreate(
    buttonTask,
    "Button Task",
    1000,
    NULL,
    1,
    &buttonTaskHandle
  );
}




void loop()
{
}
