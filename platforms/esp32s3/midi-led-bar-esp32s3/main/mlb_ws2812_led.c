#include "mlb_ws2812_led.h"

#define RMT_LED_STRIP_RESOLUTION_HZ 10000000 // 10MHz resolution, 1 tick = 0.1us (led strip needs a high resolution)
#define RMT_LED_STRIP_GPIO_NUM GPIO_NUM_21   // 0

#define EXAMPLE_LED_NUMBERS 88
#define EXAMPLE_CHASE_SPEED_MS 5

// static const char *TAG = "WS2812";

static uint8_t led_strip_pixels[EXAMPLE_LED_NUMBERS * 3];

void mlb_led_init()
{
    ESP_LOGI(TAG, "run mlb_led_init");
    memset(led_strip_pixels, 0x01, sizeof(led_strip_pixels));
}

void mlb_led_loop()
{
    ESP_LOGI(TAG, "run mlb_led_loop");

    uint32_t red = 0;
    uint32_t green = 0;
    uint32_t blue = 0;
    uint16_t hue = 0;
    uint16_t start_rgb = 0;

    ESP_LOGI(TAG, "Create RMT TX channel");
    rmt_channel_handle_t led_chan = NULL;
    rmt_tx_channel_config_t tx_chan_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT, // select source clock
        .gpio_num = RMT_LED_STRIP_GPIO_NUM,
        .mem_block_symbols = 64, // increase the block size can make the LED less flickering
        .resolution_hz = RMT_LED_STRIP_RESOLUTION_HZ,
        .trans_queue_depth = 4, // set the number of transactions that can be pending in the background
    };
    ESP_ERROR_CHECK(rmt_new_tx_channel(&tx_chan_config, &led_chan));

    ESP_LOGI(TAG, "Install led strip encoder");
    rmt_encoder_handle_t led_encoder = NULL;
    led_strip_encoder_config_t encoder_config = {
        .resolution = RMT_LED_STRIP_RESOLUTION_HZ,
    };
    ESP_ERROR_CHECK(rmt_new_led_strip_encoder(&encoder_config, &led_encoder));

    ESP_LOGI(TAG, "Enable RMT TX channel");
    ESP_ERROR_CHECK(rmt_enable(led_chan));

    ESP_LOGI(TAG, "Start LED rainbow chase");
    rmt_transmit_config_t tx_config = {
        .loop_count = 0, // no transfer loop
    };

    memset(led_strip_pixels, 0x33, sizeof(led_strip_pixels));

    while (1)
    {
        for (int i = 0; i < 3; i++)
        {

            // for (int j = i; j < EXAMPLE_LED_NUMBERS; j += 3)
            // {
            //     // Build RGB pixels
            //     hue = j * 360 / EXAMPLE_LED_NUMBERS + start_rgb;
            //     // led_strip_hsv2rgb(hue, 100, 100, &red, &green, &blue);

            //     red = (sin(hue + 1) + 1) * 127;
            //     green = (sin(hue + 2) + 1) * 127;
            //     blue = (sin(hue + 3) + 1) * 127;

            //     // red = green = blue = 250;

            //     led_strip_pixels[j * 3 + 0] = green / 10;
            //     led_strip_pixels[j * 3 + 1] = blue / 10;
            //     led_strip_pixels[j * 3 + 2] = red / 10;
            // }

            // Flush RGB values to LEDs
            ESP_ERROR_CHECK(rmt_transmit(led_chan, led_encoder, led_strip_pixels, sizeof(led_strip_pixels), &tx_config));
            ESP_ERROR_CHECK(rmt_tx_wait_all_done(led_chan, portMAX_DELAY));
            vTaskDelay(pdMS_TO_TICKS(EXAMPLE_CHASE_SPEED_MS));

            // memset(led_strip_pixels, 0, sizeof(led_strip_pixels));
            // ESP_ERROR_CHECK(rmt_transmit(led_chan, led_encoder, led_strip_pixels, sizeof(led_strip_pixels), &tx_config));
            // ESP_ERROR_CHECK(rmt_tx_wait_all_done(led_chan, portMAX_DELAY));
            // vTaskDelay(pdMS_TO_TICKS(EXAMPLE_CHASE_SPEED_MS / 10));
        }
        start_rgb += 60;
    }
}
