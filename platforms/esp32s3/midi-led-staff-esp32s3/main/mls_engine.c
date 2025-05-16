#include "mls_engine.h"

#include "mls_common.h"
#include "mls_errors.h"

#include "mls_ws2812_led.h"
// #include "mls_tusb_midi.h"

// #define rgb_map_count 12
// ColorRGB rgb_map[rgb_map_count];

// void mls_engine_state_to_rgb(MidiKeyState *src, ColorRGB *dst)
// {

//     if (src == NULL || dst == NULL)
//     {
//         return;
//     }

//     uint8_t i = src->note % rgb_map_count;
//     ColorRGB rgb = rgb_map[i];
//     *dst = rgb;
// }

mls_module *mls_engine_module_init(mls_engine_module *m1)
{
    mls_module *m2 = &m1->module;
    m2->name = "mls_engine_module";
    return m2;
}

mls_error mls_engine_init(mls_engine *engine)
{
    ESP_LOGI(TAG, "run mls_engine_init");

    // rgb_map[0] = mls_rgb(255, 0, 0);
    // rgb_map[1] = mls_rgb(200, 128, 0);
    // rgb_map[2] = mls_rgb(128, 200, 0);
    // rgb_map[3] = mls_rgb(0, 255, 0);
    // rgb_map[4] = mls_rgb(0, 200, 128);
    // rgb_map[5] = mls_rgb(0, 128, 200);
    // rgb_map[6] = mls_rgb(0, 0, 255);
    // rgb_map[7] = mls_rgb(0, 0, 0);
    // rgb_map[8] = mls_rgb(128, 0, 200);
    // rgb_map[9] = mls_rgb(200, 0, 128);
    // rgb_map[10] = mls_rgb(1, 1, 1);
    // rgb_map[11] = mls_rgb(255, 255, 255);

    return NULL;
}

mls_error mls_engine_loop(mls_engine *engine)
{
    ESP_LOGI(TAG, "run mls_engine_loop");

    // uint count = 0;
    // MidiKeyState *src = mls_midi_get_key_state_buffer(&count);
    // MidiKeyState *state = NULL;
    // // uint8_t r, g, b;
    // ColorRGB rgb;

    // if (src == NULL)
    // {
    //     return;
    // }

    // for (;;)
    // {
    //     for (uint i = 0; i < count; i++)
    //     {
    //         state = src + i;
    //         if (state->revision1 != state->revision2)
    //         {
    //             // ESP_LOGI(TAG, "debug:engine:on_key_state: note_%d", state->note);

    //             mls_engine_state_to_rgb(state, &rgb);
    //             mls_led_set_color_rgb(state->led, &rgb);
    //             state->revision2 = state->revision1;
    //         }
    //     }
    //     vTaskDelay(1);
    // }

    return NULL;
}
