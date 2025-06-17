#include "handlers.h"

////////////////////////////////////////////////////////////////////////////////
// internal structures & functions

typedef struct mlscp_get_leds_handling_t
{

    mls_cp_context *context;
    mls_cp_request *request;
    mls_cp_response *response;

    mls_cp_block *led_view_pos;  // (position)
    mls_cp_block *led_view_size; // (count)
    mls_cp_block *led_part_items;
    mls_cp_block *led_part_pos;  // (position)
    mls_cp_block *led_part_size; // (count)

    mls_cp_response_builder builder;

} mlscp_get_leds_handling;

mls_error mlscp_get_leds_scan_request(mlscp_get_leds_handling *handling);
mls_error mlscp_get_leds_handle_block(mlscp_get_leds_handling *handling, mls_cp_block *block);
mls_error mlscp_get_leds_on_group_end(mlscp_get_leds_handling *handling);
mls_error mlscp_get_leds_send_view_pos(mlscp_get_leds_handling *handling);
mls_error mlscp_get_leds_send_view_size(mlscp_get_leds_handling *handling);
mls_error mlscp_get_leds_send_part_items_1(mlscp_get_leds_handling *handling, mls_cp_block *part_pos, mls_cp_block *part_size);
mls_error mlscp_get_leds_send_part_items_2(mlscp_get_leds_handling *handling, mls_uint part_pos, mls_uint part_size);

////////////////////////////////////////////////////////////////////////////////

mls_error mlscp_get_leds(mls_cp_context *ctx, mls_cp_request *req)
{
    mls_error err = NULL;
    mlscp_get_leds_handling handling;
    memset(&handling, 0, sizeof(handling));
    handling.context = ctx;
    handling.request = req;
    handling.response = ctx->response;

    // prepare response builder
    mls_cp_response_builder *builder = &handling.builder;
    mls_cp_response_builder_init_with_context(builder, ctx);

    // scan
    err = mlscp_get_leds_scan_request(&handling);
    if (err)
    {
        return err;
    }

    // ok
    mls_cp_status_code code = MLS_CP_STATUS_OK;
    builder->status.code = code;
    builder->status.message = mls_cp_status_stringify(code);
    builder->to = req->remote;
    // builder->transaction = tid  ;

    return mls_cp_response_builder_build_and_send(builder, ctx);
}

mls_error mlscp_get_leds_scan_request(mlscp_get_leds_handling *handling)
{

    int i, count;
    mls_error err;
    mls_cp_block_array *list = handling->request->blocks;
    count = list->count;

    for (i = 0; i < count; i++)
    {
        mls_cp_block_array_item item = list->items[i];

        err = mlscp_get_leds_handle_block(handling, item.block);
        if (err)
        {
            return err;
        }
    }

    return NULL;
}

mls_error mlscp_get_leds_on_group_end(mlscp_get_leds_handling *handling)
{
    mls_error err = NULL;
    mls_error_holder eh;
    mls_error_holder_init(&eh);

    // mls_cp_block *b_part_items = handling->led_part_items;
    mls_cp_block *b_part_pos = handling->led_part_pos;
    mls_cp_block *b_part_size = handling->led_part_size;
    mls_cp_block *b_view_pos = handling->led_view_pos;
    mls_cp_block *b_view_size = handling->led_view_size;

    handling->led_part_items = NULL;
    handling->led_part_pos = NULL;
    handling->led_part_size = NULL;
    handling->led_view_pos = NULL;
    handling->led_view_size = NULL;

    if (b_view_pos)
    {
        err = mlscp_get_leds_send_view_pos(handling);
        mls_error_holder_push(&eh, err);
        if (err)
        {
            return err;
        }
    }

    if (b_view_size)
    {
        err = mlscp_get_leds_send_view_size(handling);
        mls_error_holder_push(&eh, err);
    }

    if (b_part_pos && b_part_size)
    {
        err = mlscp_get_leds_send_part_items_1(handling, b_part_pos, b_part_size);
        mls_error_holder_push(&eh, err);
    }

    return mls_error_holder_get_error(&eh);
}

mls_error mlscp_get_leds_handle_block(mlscp_get_leds_handling *handling, mls_cp_block *block)
{

    if (mls_cp_block_is_group_field_of(block, MLSCP_GF_COMMON_FLUSH))
    {
        return mlscp_get_leds_on_group_end(handling);
    }
    else if (mls_cp_block_is_group_field_of(block, MLSCP_GF_COMMON_EOG))
    {
        return mlscp_get_leds_on_group_end(handling);
    }
    else if (mls_cp_block_is_group_field_of(block, MLSCP_GF_LED_VIEW_POSITION))
    {
        handling->led_view_pos = block;
    }
    else if (mls_cp_block_is_group_field_of(block, MLSCP_GF_LED_VIEW_SIZE))
    {
        handling->led_view_size = block;
    }
    else if (mls_cp_block_is_group_field_of(block, MLSCP_GF_LED_PART_SIZE))
    {
        handling->led_part_size = block;
    }
    else if (mls_cp_block_is_group_field_of(block, MLSCP_GF_LED_PART_POSITION))
    {
        handling->led_part_pos = block;
    }
    else if (mls_cp_block_is_group_field_of(block, MLSCP_GF_LED_PART_ITEMS))
    {
        handling->led_part_items = block;
    }
    else
    {
        // NOP
    }

    return NULL;
}

mls_error mlscp_get_leds_send_view_pos(mlscp_get_leds_handling *handling)
{

    if (handling == NULL)
    {
        return mls_errors_make(500, "mlscp_get_leds_send_view_pos: handling is nil");
    }
    mls_cp_context *ctx = handling->context;
    if (ctx == NULL)
    {
        return mls_errors_make(500, "mlscp_get_leds_send_view_pos: ctx is nil");
    }
    mls_app *app = ctx->app;
    if (app == NULL)
    {
        return mls_errors_make(500, "mlscp_get_leds_send_view_pos: app is nil");
    }
    mls_engine_module *engine_mod = &app->engine;
    if (engine_mod == NULL)
    {
        return mls_errors_make(500, "mlscp_get_leds_send_view_pos: engine_mod is nil");
    }

    //////

    mls_engine *engine = &handling->context->app->engine.engine;
    mls_byte value = (mls_byte)(0xff & engine->led_buffer.view_position);

    mls_cp_response_builder *builder = &handling->builder;
    mls_cp_response_builder_add_byte(builder, MLS_CP_GROUP_LED, MLS_CP_FIELD_LED_VIEW_POSITION, value);
    return NULL;
}

mls_error mlscp_get_leds_send_view_size(mlscp_get_leds_handling *handling)
{
    mls_engine *engine = &handling->context->app->engine.engine;
    mls_byte value = (mls_byte)(0xff & engine->led_buffer.view_size);

    mls_cp_response_builder *builder = &handling->builder;
    mls_cp_response_builder_add_byte(builder, MLS_CP_GROUP_LED, MLS_CP_FIELD_LED_VIEW_SIZE, value);
    return NULL;
}

mls_error mlscp_get_leds_send_part_items_1(mlscp_get_leds_handling *handling, mls_cp_block *b_part_pos, mls_cp_block *b_part_size)
{

    mls_uint n_part_pos = mls_cp_block_get_body_uint(b_part_pos);
    mls_uint n_part_size = mls_cp_block_get_body_uint(b_part_size);

    // 每一组最多 32-leds (256/4= 64), 如果超过需要拆分

    mls_uint pos, end, count, limit;
    mls_int ttl; // 用于防止死循环
    mls_error err;

    limit = 32;
    ttl = 5;
    pos = n_part_pos;
    end = n_part_pos + n_part_size;

    for (; (pos < end) && (ttl > 0); ttl--)
    {
        count = end - pos;
        if (count > limit)
        {
            count = limit;
        }
        err = mlscp_get_leds_send_part_items_2(handling, pos, count);
        if (err)
        {
            return err;
        }
        pos += count;
    }

    return NULL;
    // return mlscp_get_leds_send_part_items_2(handling, n_part_pos, n_part_size);
}

mls_error mlscp_get_leds_send_part_items_2(mlscp_get_leds_handling *handling, mls_uint part_pos, mls_uint part_size)
{

    mls_engine_led_buffer *led_buffer = &handling->context->app->engine.engine.led_buffer;
    mls_cp_response_builder *builder = &handling->builder;

    mls_uint unit_size = sizeof(mls_argb);
    mls_uint count = part_size;
    mls_uint pos1 = part_pos;
    mls_uint pos2 = part_pos + part_size;
    mls_uint total = led_buffer->total;

    mls_argb *items0 = led_buffer->items;
    mls_argb *items1 = items0 + pos1;

    if ((pos1 < pos2) && (pos2 <= total))
    {
        mls_cp_response_builder_add_argb_array(builder, MLS_CP_GROUP_LED, MLS_CP_FIELD_LED_PART_ITEMS, items1, count * unit_size);
        mls_cp_response_builder_add_uint8(builder, MLS_CP_GROUP_LED, MLS_CP_FIELD_LED_PART_POSITION, pos1);
        mls_cp_response_builder_add_uint8(builder, MLS_CP_GROUP_LED, MLS_CP_FIELD_LED_PART_SIZE, count);

        mls_cp_response_builder_add_uint8(builder, MLS_CP_GROUP_COMMON, MLS_CP_FIELD_COMMON_END_OF_GROUP, 0);
        mls_cp_response_builder_add_no_value(builder, MLS_CP_GROUP_COMMON, MLS_CP_FIELD_COMMON_FLUSH);
    }

    ESP_LOGI(TAG, "mlscp_get_leds_send_part_items_2(): pos1=%d, pos2=%d", pos1, pos2);
    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
