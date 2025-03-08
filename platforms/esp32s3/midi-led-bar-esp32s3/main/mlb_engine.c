#include "mlb_engine.h"
#include "mlb_common.h"

#include "mlb_ws2812_led.h"
#include "mlb_tusb_midi.h"

void mlb_engine_init()
{
    ESP_LOGI(TAG, "run mlb_engine_init");
}

void mlb_engine_loop()
{
    ESP_LOGI(TAG, "run mlb_engine_loop");

    uint count = 0;
    MidiKeyState *src = mlb_midi_get_key_state_buffer(&count);
    MidiKeyState *state = NULL;
    uint8_t r, g, b;

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
                ESP_LOGI(TAG, "debug:engine:on_key_state: note_%d", state->note);

                r = g = b = state->velocity;
                mlb_led_set_color(state->note, r, g, b);
                state->revision2 = state->revision1;
            }
        }
        vTaskDelay(1);
    }
}
