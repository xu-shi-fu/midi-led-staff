#include "mls_engine.h"

#include "mls_common.h"
#include "mls_errors.h"

#include "mls_ws2812_led.h"
// #include "mls_tusb_midi.h"

////////////////////////////////////////////////////////////////////////////////
// internal functions

mls_error mls_engine_module_on_init(mls_module *m);
mls_error mls_engine_module_on_create(mls_module *m);
mls_error mls_engine_module_on_start(mls_module *m);

mls_engine_module *mls_engine_module_get_module(mls_module *m);
mls_engine *mls_engine_module_get_engine(mls_module *m);

mls_error mls_engine_init(mls_engine *engine);
mls_error mls_engine_create(mls_engine *engine);
mls_error mls_engine_start(mls_engine *engine);
mls_error mls_engine_loop(mls_engine *engine);

mls_error mls_engine_task_func(mls_task *t);

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

    err = mls_task_init(&engine->task);
    mls_error_holder_push(&eh, err);

    return mls_error_holder_get_error(&eh);
}

mls_error mls_engine_create(mls_engine *engine)
{

    mls_task *task = &engine->task;
    task->name = "mls_engine_task";
    task->data = engine;
    task->fn = mls_engine_task_func;

    return NULL;
}

mls_error mls_engine_start(mls_engine *engine)
{
    return mls_task_start(&engine->task);
}

mls_error mls_engine_task_func(mls_task *t)
{
    mls_engine *engine = t->data;
    if (engine)
    {
        return mls_engine_loop(engine);
    }
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

    mls_engine_led_buffer *led_buf = &engine->led_buffer;

    for (;;)
    {
        ESP_LOGI(TAG, "mls_engine_loop: keep-alive");
        mls_sleep(3000);

        led_buf->revision++;
    }

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
    // mls_engine_module *module = mls_engine_module_get_module(m);
    mls_engine *engine = mls_engine_module_get_engine(m);
    if (engine)
    {
        return mls_engine_init(engine);
    }
    return NULL;
}

mls_error mls_engine_module_on_create(mls_module *m)
{
    mls_engine *engine = mls_engine_module_get_engine(m);
    if (engine)
    {
        mls_engine_led_buffer *led_buffer = &engine->led_buffer;
        mls_engine_led_buffer_init_as_demo(led_buffer);
        return mls_engine_create(engine);
    }
    return NULL;
}

mls_error mls_engine_module_on_start(mls_module *m)
{
    mls_engine *engine = mls_engine_module_get_engine(m);
    if (engine)
    {
        return mls_engine_start(engine);
    }
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
    size_t s_unit = sizeof(inst->items[0]);

    inst->total_size = s_total;
    inst->unit_size = s_unit;
    inst->total = s_total / s_unit;
    inst->view_size = s_total / s_unit;
    inst->view_position = 0;
    inst->revision = 1;

    return NULL;
}

#define DEMO_PATTERN_SIZE 7

mls_error mls_engine_led_buffer_init_as_demo(mls_engine_led_buffer *inst)
{
    mls_argb led;
    mls_argb *items;
    mls_argb pattern[DEMO_PATTERN_SIZE];
    uint i, end;

    pattern[0] = mls_argb_red();
    pattern[1] = mls_argb_orange();
    pattern[2] = mls_argb_yellow();
    pattern[3] = mls_argb_green();
    pattern[4] = mls_argb_blue();
    pattern[5] = mls_argb_azure();
    pattern[6] = mls_argb_purple();

    items = inst->items;
    end = inst->total;
    for (i = 0; i < end; i++)
    {
        led = pattern[i % DEMO_PATTERN_SIZE];
        items[i] = led;
    }

    inst->view_size = DEMO_PATTERN_SIZE;
    inst->revision++;
    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
