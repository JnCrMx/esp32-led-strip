#include <math.h>
#include "ledc.h"
#include "driver/ledc.h"
#include "esp_err.h"

esp_err_t ledc_init()
{
	ledc_timer_config_t ledc_timer = {
        .duty_resolution	= CONFIG_POOLLANTERN_LEDC_RESOLUTION,	// resolution of PWM duty
        .freq_hz			= CONFIG_POOLLANTERN_LEDC_FREQUENCY,	// frequency of PWM signal
        .speed_mode			= LEDC_SPEED_MODE,					// timer mode
        .timer_num			= LEDC_TIMER_0,						// timer index
        .clk_cfg			= LEDC_AUTO_CLK,					// Auto select the source clock
    };
	ledc_timer_config(&ledc_timer);
	
	ledc_channel_config_t channel_red = {
		.channel    = LEDC_CHANNEL_RED,
		.duty       = 0,
		.gpio_num   = CONFIG_POOLLANTERN_GPIO_RED,
		.speed_mode = LEDC_SPEED_MODE,
		.hpoint     = 0,
		.timer_sel  = LEDC_TIMER_0
	};
	ledc_channel_config_t channel_green = {
		.channel    = LEDC_CHANNEL_GREEN,
		.duty       = 0,
		.gpio_num   = CONFIG_POOLLANTERN_GPIO_GREEN,
		.speed_mode = LEDC_SPEED_MODE,
		.hpoint     = 0,
		.timer_sel  = LEDC_TIMER_0
	};
	ledc_channel_config_t channel_blue = {
		.channel    = LEDC_CHANNEL_BLUE,
		.duty       = 0,
		.gpio_num   = CONFIG_POOLLANTERN_GPIO_BLUE,
		.speed_mode = LEDC_SPEED_MODE,
		.hpoint     = 0,
		.timer_sel  = LEDC_TIMER_0
	};
	ledc_channel_config(&channel_red);
	ledc_channel_config(&channel_green);
	ledc_channel_config(&channel_blue);
	
    return ESP_OK;
}

esp_err_t ledc_set_color(uint8_t red, uint8_t green, uint8_t blue)
{
	int factor = (pow(2, CONFIG_POOLLANTERN_LEDC_RESOLUTION))/256;
	
	int red_scaled = red * factor;
	int green_scaled = green * factor;
	int blue_scaled = blue * factor;
	
	ledc_set_duty(LEDC_SPEED_MODE, LEDC_CHANNEL_RED, red_scaled);
	ledc_update_duty(LEDC_SPEED_MODE, LEDC_CHANNEL_RED);
	
	ledc_set_duty(LEDC_SPEED_MODE, LEDC_CHANNEL_GREEN, green_scaled);
	ledc_update_duty(LEDC_SPEED_MODE, LEDC_CHANNEL_GREEN);
	
	ledc_set_duty(LEDC_SPEED_MODE, LEDC_CHANNEL_BLUE, blue_scaled);
	ledc_update_duty(LEDC_SPEED_MODE, LEDC_CHANNEL_BLUE);
	
    return ESP_OK;
}

esp_err_t ledc_get_color(uint8_t* red, uint8_t* green, uint8_t* blue)
{
	int factor = (pow(2, CONFIG_POOLLANTERN_LEDC_RESOLUTION))/256;

	int red_scaled = ledc_get_duty(LEDC_SPEED_MODE, LEDC_CHANNEL_RED);
	int green_scaled = ledc_get_duty(LEDC_SPEED_MODE, LEDC_CHANNEL_GREEN);
	int blue_scaled = ledc_get_duty(LEDC_SPEED_MODE, LEDC_CHANNEL_BLUE);

	*red = red_scaled / factor;
	*green = green_scaled / factor;
	*blue = blue_scaled / factor;

    return ESP_OK;
}