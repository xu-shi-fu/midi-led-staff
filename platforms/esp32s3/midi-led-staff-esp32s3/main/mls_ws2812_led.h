// ws2812_led.h

#ifndef __ws2812_led_h__
#define __ws2812_led_h__

#include "mls_common_mls.h"
#include "mls_api.h"
#include "led_strip_encoder.h"
#include "mls_errors.h"
#include "mls_module.h"
#include "mls_engine.h"
#include "mls_tasks.h"

// #define MLS_LED_NUMBERS 128 // 灯带缓冲区的大小 (LED 的个数)
// struct ColorRGB;   // use: mls_argb

typedef struct mls_led_context_t
{

    struct mls_settings_t *settings;

    mls_engine_led_buffer *buffer;

    mls_task task;

} mls_led_context;

typedef struct mls_led_module_t
{
    mls_module module;

    mls_led_context context;

} mls_led_module;

////////////////////////////////////////////////////////////////////////////////

mls_module *mls_led_module_init(mls_led_module *m);

#endif // __ws2812_led_h__
