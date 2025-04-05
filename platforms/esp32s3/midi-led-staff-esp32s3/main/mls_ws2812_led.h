// ws2812_led.h

#ifndef __ws2812_led_h__
#define __ws2812_led_h__

#include "mls_common.h"
#include "led_strip_encoder.h"
#include "mls_errors.h"

#define MLS_LED_NUMBERS 128 // 灯带缓冲区的大小 (LED 的个数)

typedef struct
{

    uint8_t a;
    uint8_t r;
    uint8_t g;
    uint8_t b;

} ColorRGB;

typedef struct
{

    uint8_t led_strip_pixels[MLS_LED_NUMBERS * 3];

} mls_led;

mls_error mls_led_init(mls_led *led);
mls_error mls_led_loop(mls_led *led);

uint mls_led_count(mls_led *led);
void mls_led_set_color(mls_led *led, uint index, uint8_t r, uint8_t g, uint8_t b);
void mls_led_set_color_rgb(mls_led *led, uint index, ColorRGB *rgb);
void mls_led_get_color(mls_led *led, uint index, uint8_t *r, uint8_t *g, uint8_t *b);

ColorRGB mls_rgb(uint8_t r, uint8_t g, uint8_t b);

#endif // __ws2812_led_h__
