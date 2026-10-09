#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BUTTON_GPIO GPIO_NUM_4

static const char *TAG = "BUTTON";

volatile bool button_pressed = false;


static void IRAM_ATTR button_isr_handler(void *arg)
{
    button_pressed = true;
}


void app_main(void)
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BUTTON_GPIO),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_NEGEDGE
    };

    gpio_config(&io_conf);

    gpio_install_isr_service(0);

    gpio_isr_handler_add(BUTTON_GPIO, button_isr_handler, NULL);


    while (1)
    {
        if (button_pressed == true)
        {
            ESP_LOGI(TAG, "Button Pressed");

            // button_pressed = false;
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}