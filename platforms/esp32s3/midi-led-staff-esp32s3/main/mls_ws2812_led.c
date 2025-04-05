#include "mls_ws2812_led.h"

#include "mls_settings.h"
#include "mls_errors.h"
#include "mls_config.h"
#include "mls_tasks.h"

#define RMT_LED_STRIP_RESOLUTION_HZ 10000000 // 10MHz resolution, 1 tick = 0.1us (led strip needs a high resolution)
#define EXAMPLE_CHASE_SPEED_MS 2             // 每个刷新周期中, delay 的时长, 单位是 ms

void mls_led_init_as_demo(mls_led *led)
{
    uint8_t r, g, b;
    uint count, index;
    count = mls_led_count(led);
    for (index = 0; index < count; index++)
    {
        if (index == 0)
        {
            r = g = b = 1;
        }
        else
        {
            r *= 2;
            g *= 2;
            b *= 2;
        }
        mls_led_set_color(led, index, r, g, b);
    }
}

mls_error mls_led_init(mls_led *led)
{
    ESP_LOGI(TAG, "run mls_led_init");
    memset(led, 0, sizeof(led[0]));
    mls_led_init_as_demo(led);
    return NULL;
}

mls_error mls_led_loop(mls_led *led_s)
{
    ESP_LOGI(TAG, "run mls_led_loop");
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

    SettingsAll *settings = mls_settings_get_all();
    uint8_t *led_strip_pixels_0 = led_s->led_strip_pixels;
    uint8_t *payload_begin = led_strip_pixels_0;
    uint8_t *payload_end = led_strip_pixels_0;
    uint8_t *payload_max = led_strip_pixels_0 + sizeof(led_s->led_strip_pixels);
    size_t payload_size = 0;
    uint16_t offset = 0;
    uint16_t limit = 0;

    while (1)
    {
        // vTaskDelay(pdMS_TO_TICKS(EXAMPLE_CHASE_SPEED_MS));
        mls_tasks_sleep(EXAMPLE_CHASE_SPEED_MS);

        offset = settings->led.output_offset;
        limit = settings->led.output_limit;

        payload_size = limit * 3;
        payload_begin = led_strip_pixels_0 + (offset * 3);
        payload_end = payload_begin + payload_size;

        if ((led_strip_pixels_0 <= payload_begin) && (payload_begin < payload_end) && (payload_end <= payload_max))
        {
            // Flush RGB values to LEDs
            ESP_ERROR_CHECK(rmt_transmit(led_chan, led_encoder, payload_begin, payload_size, &tx_config));
            ESP_ERROR_CHECK(rmt_tx_wait_all_done(led_chan, portMAX_DELAY));
        }
    }

    return NULL;
}

uint mls_led_count(mls_led *led_s)
{
    return MLS_LED_NUMBERS;
}

void mls_led_set_color(mls_led *led_s, uint index, uint8_t r, uint8_t g, uint8_t b)
{
    if (index >= MLS_LED_NUMBERS)
    {
        return;
    }
    led_s->led_strip_pixels[(3 * index) + 0] = r;
    led_s->led_strip_pixels[(3 * index) + 1] = g;
    led_s->led_strip_pixels[(3 * index) + 2] = b;
}

void mls_led_set_color_rgb(mls_led *led_s, uint index, ColorRGB *rgb)
{
    if (rgb == NULL)
    {
        return;
    }
    mls_led_set_color(led_s, index, rgb->r, rgb->g, rgb->b);
}

void mls_led_get_color(mls_led *led_s, uint index, uint8_t *r, uint8_t *g, uint8_t *b)
{
    if (index >= MLS_LED_NUMBERS)
    {
        return;
    }
    if (r == NULL || g == NULL || b == NULL)
    {
        return;
    }
    r[0] = led_s->led_strip_pixels[(3 * index) + 0];
    g[0] = led_s->led_strip_pixels[(3 * index) + 1];
    b[0] = led_s->led_strip_pixels[(3 * index) + 2];
}

ColorRGB mls_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    ColorRGB rgb;
    rgb.a = 255;
    rgb.r = r;
    rgb.g = g;
    rgb.b = b;
    return rgb;
}
