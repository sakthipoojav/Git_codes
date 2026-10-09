#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

portMUX_TYPE DATA_MUTEX = portMUX_INITIALIZER_UNLOCKED;
// global variable
// modify this var from two diff tasks
// Task1 adds 1 to varible; Task2 adds 2

TaskHandle_t task1_handle = 0;
TaskHandle_t task2_handle = 0;

int global_var = 0;

void task1(void *pvParams) {

    while (1)
    {
        portENTER_CRITICAL(&DATA_MUTEX);
        global_var+=1;
        portEXIT_CRITICAL(&DATA_MUTEX);

        ESP_LOGI("TASK1", "Modified the gloabal variable");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
}

void task2(void *pvParams){

    while (1)
    {
        portENTER_CRITICAL(&DATA_MUTEX);
        global_var+=1;
        portEXIT_CRITICAL(&DATA_MUTEX);
        
        ESP_LOGI("TASK2", "Modified the gloabal variable");

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
}

void app_main(void) {

    xTaskCreate(task1, "TASK1", 1024, NULL, 5, &task1_handle);
    xTaskCreate(task2, "TASK2", 1024, NULL, 5, &task2_handle);
    
}