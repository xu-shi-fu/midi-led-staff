#include "mlb_engine.h"
#include "mlb_common.h"

#include "mlb_ws2812_led.h"
#include "mlb_tusb_midi.h"

#define rgb_map_count 12
ColorRGB rgb_map[rgb_map_count];

void mlb_engine_state_to_rgb(MidiKeyState *src, ColorRGB *dst)
{

    if (src == NULL || dst == NULL)
    {
        return;
    }

    uint8_t i = src->note % rgb_map_count;
    ColorRGB rgb = rgb_map[i];
    *dst = rgb;
}

void mlb_engine_init()
{
    ESP_LOGI(TAG, "run mlb_engine_init");

    rgb_map[0] = mlb_rgb(255, 0, 0);
    rgb_map[1] = mlb_rgb(200, 128, 0);
    rgb_map[2] = mlb_rgb(128, 200, 0);
    rgb_map[3] = mlb_rgb(0, 255, 0);
    rgb_map[4] = mlb_rgb(0, 200, 128);
    rgb_map[5] = mlb_rgb(0, 128, 200);
    rgb_map[6] = mlb_rgb(0, 0, 255);
    rgb_map[7] = mlb_rgb(0, 0, 0);
    rgb_map[8] = mlb_rgb(128, 0, 200);
    rgb_map[9] = mlb_rgb(200, 0, 128);
    rgb_map[10] = mlb_rgb(1, 1, 1);
    rgb_map[11] = mlb_rgb(255, 255, 255);
}

void mlb_engine_loop()
{
    ESP_LOGI(TAG, "run mlb_engine_loop");

    uint count = 0;
    MidiKeyState *src = mlb_midi_get_key_state_buffer(&count);
    MidiKeyState *state = NULL;
    // uint8_t r, g, b;
    ColorRGB rgb;

    if (src == NULL)
    {
        return;
    }

    for (;;)
    {
        for (uint i = 0; i < count; i++)
        {
            state = src + i;
            if (state->revision1 != state->revision2)
            {
                // ESP_LOGI(TAG, "debug:engine:on_key_state: note_%d", state->note);

                mlb_engine_state_to_rgb(state, &rgb);
                mlb_led_set_color_rgb(state->led, &rgb);
                state->revision2 = state->revision1;
            }
        }
        vTaskDelay(1);
    }
}
