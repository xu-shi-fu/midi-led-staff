// ws2812_led.h

#ifndef __ws2812_led_h__
#define __ws2812_led_h__

#include "mlb_common.h"
#include "led_strip_encoder.h"

typedef struct
{

    uint8_t a;
    uint8_t r;
    uint8_t g;
    uint8_t b;

} ColorRGB;

void mlb_led_init();
void mlb_led_loop();

uint mlb_led_count();
void mlb_led_set_color(uint index, uint8_t r, uint8_t g, uint8_t b);
void mlb_led_set_color_rgb(uint index, ColorRGB *rgb);
void mlb_led_get_color(uint index, uint8_t *r, uint8_t *g, uint8_t *b);

ColorRGB mlb_rgb(uint8_t r, uint8_t g, uint8_t b);

#endif // __ws2812_led_h__
