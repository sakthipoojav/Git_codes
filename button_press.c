#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BUTTON_GPIO GPIO_NUM_23

static const char *TAG = "BUTTON";

void app_main(void)
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BUTTON_GPIO),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config(&io_conf);

    while (1)
    {
        int button_state = gpio_get_level(BUTTON_GPIO);

        if (button_state == 0)
        {
            ESP_LOGI(TAG, "Button Pressed");

            vTaskDelay(pdMS_TO_TICKS(200));
        }

    }
}