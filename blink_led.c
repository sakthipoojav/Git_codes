#include <stdio.h>
#include "esp_log.h"

static const char *TAG = "MY_APP";

void app_main(void)
{
    esp_log_level_set("*", ESP_LOG_WARN);
    ESP_LOGI(TAG, "Application started");

    ESP_LOGW(TAG, "This is a warning");

    ESP_LOGD(TAG, "This is a debug message");


    // ESP_LOGE(TAG, "This is an error");

    ESP_LOGV(TAG, "This is a verbose message");
}