#include "mls_ws2812_led.h"

#include "mls_app.h"
#include "mls_settings.h"
#include "mls_errors.h"
#include "mls_config.h"
#include "mls_tasks.h"
#include "mls_common.h"

#define RMT_LED_STRIP_RESOLUTION_HZ 10000000 // 10MHz resolution, 1 tick = 0.1us (led strip needs a high resolution)
#define EXAMPLE_CHASE_SPEED_MS 2             // 每个刷新周期中, delay 的时长, 单位是 ms

typedef struct rmt_working_context_t
{

    rmt_channel_handle_t channel;
    rmt_encoder_handle_t encoder;
    rmt_transmit_config_t *config;

} rmt_working_context;

////////////////////////////////////////////////////////////////////////////////
// internal functions

mls_led_module *mls_led_module_get_module(mls_module *module);
mls_led_context *mls_led_module_get_context(mls_module *module);

mls_error mls_led_module_on_init(mls_module *module);
mls_error mls_led_module_on_create(mls_module *module);
mls_error mls_led_module_on_start(mls_module *module);

mls_error mls_led_task_run_fn(mls_task *task);

mls_error mls_led_init(mls_led_context *ctx, mls_app *app);
mls_error mls_led_create(mls_led_context *ctx);
mls_error mls_led_start(mls_led_context *ctx);
mls_error mls_led_run_loop(mls_led_context *ledctx);
mls_buffer_slice *mls_led_context_prepare_data(mls_led_context *ctx, mls_buffer_slice *slice);
mls_bool mls_led_has_data_updated(mls_led_context *ctx);
void mls_led_log_config(mls_led_context *ctx, mls_engine_led_buffer *buffer);
void mls_led_flush(mls_led_context *ctx, rmt_working_context *working);
void mls_led_pull(mls_led_context *ctx);

mls_led_rgb_buffer *mls_led_rgb_buffer_new();
void mls_led_rgb_buffer_init(mls_led_rgb_buffer *buffer);

////////////////////////////////////////////////////////////////////////////////

mls_module *mls_led_module_init(mls_led_module *m1)
{
    mls_module *m2 = &m1->module;

    m2->name = "mls_led_module";
    m2->on_init = mls_led_module_on_init;
    m2->on_create = mls_led_module_on_create;
    m2->on_start = mls_led_module_on_start;
    m2->inner = m1;

    return m2;
}

// void mls_led_init_as_demo(mls_led_context *ledctx)
// {
//     uint8_t r, g, b;
//     uint count, index;
//     count = mls_led_count(ledctx);
//     for (index = 0; index < count; index++)
//     {
//         if (index == 0)
//         {
//             r = g = b = 1;
//         }
//         else
//         {
//             r *= 2;
//             g *= 2;
//             b *= 2;
//         }
//         mls_led_set_color(ledctx, index, r, g, b);
//     }
// }

mls_error mls_led_init(mls_led_context *ctx, mls_app *app)
{
    if (ctx == NULL || app == NULL)
    {
        return mls_errors_make(500, "mls_led_init: param(s) is nil");
    }

    mls_settings *settings = &app->settings.settings;
    mls_engine_led_buffer *source = &app->engine.engine.led_buffer;

    // make dest-buffer
    mls_led_rgb_buffer *dest = mls_led_rgb_buffer_new();
    if (dest == NULL)
    {
        return mls_errors_make(500, "mls_led_create: make output buffer, got nil");
    }

    ctx->settings = settings;
    ctx->source = source;
    ctx->destination = dest;

    return NULL;
}

mls_error mls_led_create(mls_led_context *ctx)
{
    mls_task *task = &ctx->task;
    mls_task_init(task);
    task->data = ctx;
    task->name = "mls_ws2812_led_task";
    task->fn = mls_led_task_run_fn;

    return NULL;
}

mls_error mls_led_start(mls_led_context *ctx)
{

    mls_led_log_config(ctx, ctx->source);

    mls_task *task = &ctx->task;
    return mls_task_start(task);
}

void mls_led_flush(mls_led_context *ctx, rmt_working_context *working)
{
    mls_buffer_slice data_holder;
    mls_buffer_slice *data = mls_led_context_prepare_data(ctx, &data_holder);
    if (data)
    {
        ESP_ERROR_CHECK(rmt_transmit(working->channel, working->encoder, data->data, data->length, working->config));
        ESP_ERROR_CHECK(rmt_tx_wait_all_done(working->channel, portMAX_DELAY));
    }
}

void mls_led_pull(mls_led_context *ctx)
{
    mls_engine_led_buffer *src = ctx->source;
    mls_led_rgb_buffer *dst = ctx->destination;
    if (src == NULL || dst == NULL)
    {
        ESP_LOGE(TAG, "mls_led_pull src|dst is nil");
        return;
    }

    int i, offset, length;
    mls_rgb *p_rgb = NULL;
    mls_argb *p_argb = NULL;

    length = src->length;
    offset = src->offset;

    for (i = 0; i < length; i++)
    {
        p_argb = src->items + i + offset;
        p_rgb = dst->items + i;
        mls_argb_to_rgb(p_argb, p_rgb);
    }

    dst->active_count = length;
    dst->revision = src->revision;

    // log ...
    p_argb = src->items;
    p_rgb = dst->items;
    int rev = dst->revision;
    int ptr1 = (int)((void *)p_argb);
    int ptr2 = (int)((void *)p_rgb);
    ESP_LOGI(TAG, "mls_led_pull: sync to revision: %d", rev);
    ESP_LOGI(TAG, "mls_led_pull: [led_buffer ptr1:%d ptr2:%d offset:%d length:%d]", ptr1, ptr2, offset, length);
}

mls_bool mls_led_has_data_updated(mls_led_context *ctx)
{
    mls_revision r1 = ctx->source->revision;
    mls_revision r2 = ctx->destination->revision;
    return (r1 != r2);
}

mls_error mls_led_run_loop(mls_led_context *ctx)
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

    // ESP_LOGI(TAG, "Start LED rainbow chase");
    rmt_transmit_config_t tx_config = {
        .loop_count = 0, // no transfer loop
    };

    rmt_working_context working;
    working.config = &tx_config;
    working.channel = led_chan;
    working.encoder = led_encoder;

    while (1)
    {
        mls_sleep(EXAMPLE_CHASE_SPEED_MS);
        if (mls_led_has_data_updated(ctx))
        {
            mls_led_pull(ctx);
            mls_led_flush(ctx, &working);
        }
    }

    return NULL;
}

// uint mls_led_count(mls_led_context *ledctx)
// {
//     return MLS_LED_NUMBERS;
// }

// void mls_led_set_color(mls_led_context *ledctx, uint index, uint8_t r, uint8_t g, uint8_t b)
// {
//     if (index >= MLS_LED_NUMBERS)
//     {
//         return;
//     }
//     led_s->led_strip_pixels[(3 * index) + 0] = r;
//     led_s->led_strip_pixels[(3 * index) + 1] = g;
//     led_s->led_strip_pixels[(3 * index) + 2] = b;
// }

// void mls_led_set_color_rgb(mls_led_context *ledctx, uint index, ColorRGB *rgb)
// {
//     if (rgb == NULL)
//     {
//         return;
//     }
//     mls_led_set_color(led_s, index, rgb->r, rgb->g, rgb->b);
// }

// void mls_led_get_color(mls_led_context *ledctx, uint index, uint8_t *r, uint8_t *g, uint8_t *b)
// {
//     if (index >= MLS_LED_NUMBERS)
//     {
//         return;
//     }
//     if (r == NULL || g == NULL || b == NULL)
//     {
//         return;
//     }
//     r[0] = led_s->led_strip_pixels[(3 * index) + 0];
//     g[0] = led_s->led_strip_pixels[(3 * index) + 1];
//     b[0] = led_s->led_strip_pixels[(3 * index) + 2];
// }

mls_error mls_led_task_run_fn(mls_task *task)
{
    mls_led_context *ctx = task->data;
    return mls_led_run_loop(ctx);
}

void mls_led_log_config(mls_led_context *ctx, mls_engine_led_buffer *buffer)
{
    if (ctx == NULL || buffer == NULL)
    {
        return;
    }
    int total = buffer->total;
    int offset = buffer->offset;
    int length = buffer->length;
    int unit_size = buffer->unit_size;
    int total_size = buffer->total_size;

    ESP_LOGI(TAG, "mls_led_log_config: [led_buffer total:%d offset:%d length:%d unit_size:%d total_size:%d]",
             total, offset, length, unit_size, total_size);
}

mls_buffer_slice *mls_led_context_prepare_data(mls_led_context *ctx, mls_buffer_slice *slice)
{
    if (ctx && slice)
    {
        mls_led_rgb_buffer *dest = ctx->destination;
        if (dest)
        {
            void *p_data = dest->items;
            slice->data = p_data;
            slice->length = dest->unit_size * dest->active_count;
            return slice;
        }
    }
    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// mls_led_rgb_buffer

mls_led_rgb_buffer *mls_led_rgb_buffer_new()
{
    size_t size = sizeof(mls_led_rgb_buffer);
    mls_led_rgb_buffer *p = malloc(size);
    mls_led_rgb_buffer_init(p);
    return p;
}

void mls_led_rgb_buffer_init(mls_led_rgb_buffer *buffer)
{
    if (buffer == NULL)
    {
        return;
    }

    memset(buffer, 0, sizeof(buffer[0]));
    size_t unit_size = sizeof(buffer->items[0]);
    size_t total_size = sizeof(buffer->items);

    buffer->total_size = total_size;
    buffer->unit_size = unit_size;
    buffer->total_count = total_size / unit_size;
    buffer->active_count = 88;
    buffer->revision = 0;
}

////////////////////////////////////////////////////////////////////////////////
// mls_module

mls_error mls_led_module_on_init(mls_module *module)
{
    mls_led_context *ctx = mls_led_module_get_context(module);
    if (ctx == NULL)
    {
        return mls_errors_make(500, "mls_led_module_on_init: context is nil");
    }
    mls_app *app = module->app;
    return mls_led_init(ctx, app);
}

mls_error mls_led_module_on_create(mls_module *module)
{
    mls_led_context *ctx = mls_led_module_get_context(module);
    if (ctx == NULL)
    {
        return mls_errors_make(500, "mls_led_module_on_create: context is nil");
    }
    return mls_led_create(ctx);
}

mls_error mls_led_module_on_start(mls_module *module)
{
    mls_led_context *ctx = mls_led_module_get_context(module);
    if (ctx == NULL)
    {
        return mls_errors_make(500, "mls_led_module_on_start: context is nil");
    }
    return mls_led_start(ctx);
}

mls_led_module *mls_led_module_get_module(mls_module *module)
{
    mls_led_module *m1 = NULL;
    if (module)
    {
        m1 = module->inner;
    }
    return m1;
}

mls_led_context *mls_led_module_get_context(mls_module *module)
{
    mls_led_module *m2 = mls_led_module_get_module(module);
    if (m2)
    {
        return &m2->context;
    }
    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
