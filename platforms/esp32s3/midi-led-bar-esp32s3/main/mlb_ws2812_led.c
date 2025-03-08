#include "mlb_ws2812_led.h"

#define RMT_LED_STRIP_RESOLUTION_HZ 10000000 // 10MHz resolution, 1 tick = 0.1us (led strip needs a high resolution)
#define RMT_LED_STRIP_GPIO_NUM GPIO_NUM_6    // 设置用于输出的 GPIO 口
#define EXAMPLE_LED_NUMBERS 128              // 灯带缓冲区的大小 (LED 的个数)
#define EXAMPLE_CHASE_SPEED_MS 3             // 每个刷新周期中, delay 的时长, 单位是 ms

static uint8_t led_strip_pixels[EXAMPLE_LED_NUMBERS * 3];

void mlb_led_init()
{
    ESP_LOGI(TAG, "run mlb_led_init");
    memset(led_strip_pixels, 0x01, sizeof(led_strip_pixels));
}

void mlb_led_loop()
{
    ESP_LOGI(TAG, "run mlb_led_loop");

    // uint32_t red = 0;
    // uint32_t green = 0;
    // uint32_t blue = 0;
    // uint16_t hue = 0;
    // uint16_t start_rgb = 0;

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

    while (1)
    {
        // Flush RGB values to LEDs
        ESP_ERROR_CHECK(rmt_transmit(led_chan, led_encoder, led_strip_pixels, sizeof(led_strip_pixels), &tx_config));
        ESP_ERROR_CHECK(rmt_tx_wait_all_done(led_chan, portMAX_DELAY));
        vTaskDelay(pdMS_TO_TICKS(EXAMPLE_CHASE_SPEED_MS));
    }
}

uint mlb_led_count()
{
    return EXAMPLE_LED_NUMBERS;
}

void mlb_led_set_color(uint index, uint8_t r, uint8_t g, uint8_t b)
{
    if (index >= EXAMPLE_LED_NUMBERS)
    {
        return;
    }
    led_strip_pixels[(3 * index) + 0] = r;
    led_strip_pixels[(3 * index) + 1] = g;
    led_strip_pixels[(3 * index) + 2] = b;
}

void mlb_led_get_color(uint index, uint8_t *r, uint8_t *g, uint8_t *b)
{
    if (index >= EXAMPLE_LED_NUMBERS)
    {
        return;
    }
    if (r == NULL || g == NULL || b == NULL)
    {
        return;
    }
    r[0] = led_strip_pixels[(3 * index) + 0];
    g[0] = led_strip_pixels[(3 * index) + 1];
    b[0] = led_strip_pixels[(3 * index) + 2];
}
