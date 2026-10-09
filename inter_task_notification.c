#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "TASK";

static TaskHandle_t xReceiverTaskHandle = NULL;

void Task1(void *pvParameters){
    ESP_LOGI(TAG,"receiver ready");

    while(1) {

        uint32_t count = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        if (count > 0){
            ESP_LOGI(TAG, "Notification Received");
        }
    }
}

void Task2(void *pvParameters){

     while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));

        ESP_LOGI(TAG,"sending notification");

        if (xReceiverTaskHandle != NULL) {
            xTaskNotifyGive(xReceiverTaskHandle);
        }
     }    
}

void app_main(void){
    xTaskCreate(Task1, "ReceiverTask", 2048, NULL, 2, &xReceiverTaskHandle);

    xTaskCreate(Task2, "SenderTask", 2048, NULL, 1, NULL);
}