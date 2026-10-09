#include <stdio.h>
#include <string.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/i2c_master.h"
#include "driver/uart.h"


static const char *TAG = "BNO055_EXAMPLE";


#define I2C_MASTER_SDA_IO           6    
#define I2C_MASTER_SCL_IO           7    
#define I2C_MASTER_NUM              I2C_NUM_0                                  
#define I2C_MASTER_FREQ_HZ          100000
#define I2C_MASTER_TIMEOUT_MS       1000


#define BNO055_SENSOR_ADDR          0x28
#define BNO055_WHO_AM_I_REG_ADDR    0x00
#define BNO055_OPR_MODE_REG_ADDR    0x3D
#define BNO055_ACC_DATA_X_LSB_ADDR  0x08    


#define BNO055_MODE_CONFIG          0x00
#define BNO055_MODE_NDOF            0x0C


#define UART_PORT_NUM  UART_NUM_0
#define UART_BUF_SIZE  1024


static esp_err_t bno055_register_read(i2c_master_dev_handle_t dev_handle, uint8_t reg_addr, uint8_t *data, size_t len)
{
    return i2c_master_transmit_receive(dev_handle, &reg_addr, 1, data, len, I2C_MASTER_TIMEOUT_MS);
}


static esp_err_t bno055_register_write_byte(i2c_master_dev_handle_t dev_handle, uint8_t reg_addr, uint8_t data)
{
    uint8_t write_buf[2] = {reg_addr, data};
    return i2c_master_transmit(dev_handle, write_buf, sizeof(write_buf), I2C_MASTER_TIMEOUT_MS);
}


static void i2c_master_init(i2c_master_bus_handle_t *bus_handle, i2c_master_dev_handle_t *dev_handle)
{
    i2c_master_bus_config_t bus_config = {
        .i2c_port = I2C_MASTER_NUM,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, bus_handle));


    i2c_device_config_t dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = BNO055_SENSOR_ADDR,
        .scl_speed_hz = I2C_MASTER_FREQ_HZ,
    };
    ESP_ERROR_CHECK(i2c_master_bus_add_device(*bus_handle, &dev_config, dev_handle));
}


void app_main(void)
{
    ESP_ERROR_CHECK(
    uart_driver_install(
        UART_PORT_NUM,
        UART_BUF_SIZE,
        UART_BUF_SIZE,
        0,
        NULL,
        0
    )
);


const uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    .rx_flow_ctrl_thresh = 122,
};


ESP_ERROR_CHECK(
    uart_param_config(
        UART_PORT_NUM,
        &uart_config
    )
);


ESP_ERROR_CHECK(
    uart_set_pin(
        UART_PORT_NUM,
        UART_PIN_NO_CHANGE,
        UART_PIN_NO_CHANGE,
        UART_PIN_NO_CHANGE,
        UART_PIN_NO_CHANGE
    )
);


    uint8_t data[6] = {0};
    i2c_master_bus_handle_t bus_handle;
    i2c_master_dev_handle_t dev_handle;
    i2c_master_init(&bus_handle, &dev_handle);
    ESP_LOGI(TAG, "I2C initialized successfully");


    vTaskDelay(pdMS_TO_TICKS(400));
    ESP_ERROR_CHECK(bno055_register_read(dev_handle, BNO055_WHO_AM_I_REG_ADDR, data, 1));
    ESP_LOGI(TAG, "WHO_AM_I = %X", data[0]);


    ESP_ERROR_CHECK(bno055_register_write_byte(dev_handle, BNO055_OPR_MODE_REG_ADDR, BNO055_MODE_CONFIG));
    vTaskDelay(pdMS_TO_TICKS(25));
    ESP_ERROR_CHECK(bno055_register_write_byte(dev_handle, BNO055_OPR_MODE_REG_ADDR, BNO055_MODE_NDOF));
    vTaskDelay(pdMS_TO_TICKS(20));


    float sum_x = 0.0f;
    float sum_y = 0.0f;
    float sum_z = 0.0f;
    const int sample_count = 10;


    ESP_LOGI(TAG, "Collecting data ", sample_count);
    for (int i = 0; i < sample_count; i++) {
        ESP_ERROR_CHECK(bno055_register_read(dev_handle, BNO055_ACC_DATA_X_LSB_ADDR, data, 6));


        uint8_t lsb[3] = {data[0], data[2], data[4]};
        uint8_t msb[3] = {data[1], data[3], data[5]};
       
        int16_t acc_x_raw = (int16_t)(((uint16_t)msb[0] << 8) | lsb[0]);
        int16_t acc_y_raw = (int16_t)(((uint16_t)msb[1] << 8) | lsb[1]);
        int16_t acc_z_raw = (int16_t)(((uint16_t)msb[2] << 8) | lsb[2]);


        sum_x += (float)acc_x_raw / 100.0f;
        sum_y += (float)acc_y_raw / 100.0f;
        sum_z += (float)acc_z_raw / 100.0f;


        vTaskDelay(pdMS_TO_TICKS(100));
    }


    float mean_x = sum_x / (float)sample_count;
    float mean_y = sum_y / (float)sample_count;
    float mean_z = sum_z / (float)sample_count;


    ESP_LOGI(TAG, "Mean calculated -> X: %.3f | Y: %.3f | Z: %.3f", mean_x, mean_y, mean_z);


    while(1) {


       
        ESP_ERROR_CHECK(bno055_register_read(dev_handle, BNO055_ACC_DATA_X_LSB_ADDR, data, 6));


        uint8_t lsb[3] = {data[0], data[2], data[4]};
        uint8_t msb[3] = {data[1], data[3], data[5]};
       
        int16_t acc_x_raw = (int16_t)(((uint16_t)msb[0] << 8) | lsb[0]);
        int16_t acc_y_raw = (int16_t)(((uint16_t)msb[1] << 8) | lsb[1]);
        int16_t acc_z_raw = (int16_t)(((uint16_t)msb[2] << 8) | lsb[2]);


        float acc_x_mps2 = ((float)acc_x_raw / 100.0f);
        float acc_y_mps2 = ((float)acc_y_raw / 100.0f);
        float acc_z_mps2 = ((float)acc_z_raw / 100.0f);


        float final_x = acc_x_mps2 - mean_x;
        float final_y = acc_y_mps2 - mean_y;
        float final_z = (acc_z_mps2) / mean_z;

        uint8_t arr[14] = {0};

        arr[0] = 0xAA;
        arr[1] = 0x55;

        memcpy(&arr[0],&final_x,4);
        memcpy(&arr[4],&final_y,4);
        memcpy(&arr[8],&final_z,4);


        // arr[0] = acceleration_data;
        // arr[0] - arr[3] = accle_x
        // arr[8] - arr[11] = accel_z
        
        uart_write_bytes(UART_PORT_NUM,(const char *)arr,sizeof(arr));


        vTaskDelay(pdMS_TO_TICKS(500));
    }


    ESP_ERROR_CHECK(i2c_master_bus_rm_device(dev_handle));
    ESP_ERROR_CHECK(i2c_del_master_bus(bus_handle));
    ESP_LOGI(TAG, "I2C de-initialized successfully");
}