#include "esp_err.h"

#define LEDC_SPEED_MODE LEDC_LOW_SPEED_MODE

#define LEDC_CHANNEL_RED LEDC_CHANNEL_0
#define LEDC_CHANNEL_GREEN LEDC_CHANNEL_1
#define LEDC_CHANNEL_BLUE LEDC_CHANNEL_2

esp_err_t ledc_init();
esp_err_t ledc_set_color(uint8_t red, uint8_t green, uint8_t blue);
esp_err_t ledc_get_color(uint8_t* red, uint8_t* green, uint8_t* blue);
