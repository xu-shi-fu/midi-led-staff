#include "mls_engine.h"

#include "mls_common.h"
#include "mls_errors.h"

#include "mls_ws2812_led.h"
// #include "mls_tusb_midi.h"

mls_error mls_engine_module_on_init(mls_module *m);
mls_error mls_engine_module_on_create(mls_module *m);
mls_error mls_engine_module_on_start(mls_module *m);

mls_engine_module *mls_engine_module_get_module(mls_module *m);
mls_engine *mls_engine_module_get_engine(mls_module *m);

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

////////////////////////////////////////////////////////////////////////////////
// engine

mls_error mls_engine_init(mls_engine *engine)
{
    if (engine == NULL)
    {
        return mls_errors_make(500, "mls_engine_init: engine is nil");
    }

    mls_error err;
    mls_error_holder eh;
    mls_engine_led_buffer *led_buffer = &engine->led_buffer;

    mls_error_holder_init(&eh);

    err = mls_engine_led_buffer_init(led_buffer);
    mls_error_holder_push(&eh, err);

    return mls_error_holder_get_error(&eh);
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

////////////////////////////////////////////////////////////////////////////////
// module

mls_engine_module *mls_engine_module_get_module(mls_module *m)
{
    if (m)
    {
        return m->inner;
    }
    return NULL;
}

mls_engine *mls_engine_module_get_engine(mls_module *m1)
{
    mls_engine_module *m2 = mls_engine_module_get_module(m1);
    if (m2)
    {
        return &m2->engine;
    }
    return NULL;
}

mls_error mls_engine_module_on_init(mls_module *m)
{
    mls_engine_module *module = mls_engine_module_get_module(m);
    if (module)
    {
        return mls_engine_init(&module->engine);
    }
    return NULL;
}

mls_error mls_engine_module_on_create(mls_module *m)
{
    // ESP_LOGI(TAG, "mls_engine_module::on_create");

    mls_engine *engine = mls_engine_module_get_engine(m);
    if (engine)
    {
        mls_engine_led_buffer *led_buffer = &engine->led_buffer;
        mls_engine_led_buffer_init_as_demo(led_buffer);
    }

    return NULL;
}

mls_error mls_engine_module_on_start(mls_module *m)
{
    // ESP_LOGI(TAG, "mls_engine_module::on_start");
    return NULL;
}

mls_module *mls_engine_module_init(mls_engine_module *m1)
{
    mls_module *m2 = &m1->module;
    m2->name = "mls_engine_module";
    m2->on_init = mls_engine_module_on_init;
    m2->on_create = mls_engine_module_on_create;
    m2->on_start = mls_engine_module_on_start;
    m2->inner = m1;
    return m2;
}

////////////////////////////////////////////////////////////////////////////////
// mls_engine_led_buffer

mls_error mls_engine_led_buffer_init(mls_engine_led_buffer *inst)
{

    memset(inst, 0, sizeof(inst[0]));

    size_t s_total = sizeof(inst->items);
    size_t s_unit = sizeof(mls_engine_led_item);

    inst->total_size = s_total;
    inst->unit_size = s_unit;
    inst->total = s_total / s_unit;
    inst->length = s_total / s_unit;
    inst->offset = 0;
    inst->revision_of_config = 1;
    inst->revision_of_data = 1;

    return NULL;
}

mls_error mls_engine_led_buffer_init_as_demo(mls_engine_led_buffer *inst)
{

    mls_engine_led_item led;
    mls_engine_led_item *items = inst->items;
    uint i, end;

    end = inst->total;
    led.r = 0xff;
    led.g = 0xff;
    led.b = 0xff;

    for (i = 0; i < end; i++)
    {
        items[i] = led;
        led.r += 17;
        led.g += 28;
        led.b += 39;
    }

    inst->revision_of_data++;
    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
