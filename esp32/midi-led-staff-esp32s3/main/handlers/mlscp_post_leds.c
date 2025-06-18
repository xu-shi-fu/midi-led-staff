#include "handlers.h"

typedef struct mlscp_post_leds_handling_t
{

    mls_cp_context *context;
    mls_cp_request *request;
    mls_cp_response *response;

    mls_cp_response_builder builder;

    mls_cp_block *block_part_pos;
    mls_cp_block *block_part_size;
    mls_cp_block *block_part_items;
    mls_cp_block *block_view_pos;
    mls_cp_block *block_view_size;

} mlscp_post_leds_handling;

////////////////////////////////////////////////////////////////////////////////
// internal functions

mls_error mlscp_post_leds_scan_request(mlscp_post_leds_handling *handling);
mls_error mlscp_post_leds_scan_request_on_block(mlscp_post_leds_handling *handling, mls_cp_block *block);
mls_error mlscp_post_leds_scan_request_on_flush(mlscp_post_leds_handling *handling);
mls_error mlscp_post_leds_scan_request_on_set_part(mlscp_post_leds_handling *handling, mls_uint pos, mls_argb *items, mls_uint count);
mls_error mlscp_post_leds_scan_request_on_set_view(mlscp_post_leds_handling *handling, mls_uint pos, mls_uint count);

////////////////////////////////////////////////////////////////////////////////
// impl

mls_error mlscp_post_leds(mls_cp_context *ctx, mls_cp_request *req)
{
    mls_error err = NULL;
    mlscp_post_leds_handling handling;
    memset(&handling, 0, sizeof(handling));
    handling.context = ctx;
    handling.request = req;
    handling.response = ctx->response;

    // prepare response builder
    mls_cp_response_builder *resp_builder = &handling.builder;
    mls_cp_response_builder_init_with_context(resp_builder, ctx);

    // scan
    err = mlscp_post_leds_scan_request(&handling);

    // send response
    mls_cp_status_code code = MLS_CP_STATUS_OK;
    if (err)
    {
        code = MLS_CP_STATUS_INTERNAL_SERVER_ERROR;
        mls_errors_log_warn(err);
    }
    resp_builder->status.code = code;
    resp_builder->status.message = mls_cp_status_stringify(code);
    resp_builder->to = req->remote;
    resp_builder->transaction = ctx->transaction;
    return mls_cp_response_builder_build_and_send(resp_builder, ctx);
}

mls_error mlscp_post_leds_scan_request(mlscp_post_leds_handling *handling)
{
    mls_cp_block_array *blocks = handling->request->blocks;
    mls_uint count = blocks->count;
    mls_cp_block_array_item *items = blocks->items;
    mls_cp_block_array_item *item;
    mls_cp_block *block;
    mls_error err;

    for (mls_uint i = 0; i < count; i++)
    {
        item = items + i;
        block = item->block;
        err = mlscp_post_leds_scan_request_on_block(handling, block);
        // mls_errors_log_warn(err);
        if (err)
        {
            return err;
        }
    }

    err = mlscp_post_leds_scan_request_on_flush(handling);
    return err;
}

mls_error mlscp_post_leds_scan_request_on_block(mlscp_post_leds_handling *handling, mls_cp_block *block)
{
    mls_error err = NULL;

    if (block == NULL)
    {
        // NOP
    }
    else if (mls_cp_block_is_group_field_of(block, MLSCP_GF_COMMON_FLUSH))
    {

        err = mlscp_post_leds_scan_request_on_flush(handling);

        handling->block_part_pos = NULL;
        handling->block_part_size = NULL;
        handling->block_part_items = NULL;
        handling->block_view_pos = NULL;
        handling->block_view_size = NULL;
    }
    else if (mls_cp_block_is_group_field_of(block, MLSCP_GF_LED_PART_POSITION))
    {
        handling->block_part_pos = block;
    }
    else if (mls_cp_block_is_group_field_of(block, MLSCP_GF_LED_PART_SIZE))
    {
        handling->block_part_size = block;
    }
    else if (mls_cp_block_is_group_field_of(block, MLSCP_GF_LED_PART_ITEMS))
    {
        handling->block_part_items = block;
    }
    else if (mls_cp_block_is_group_field_of(block, MLSCP_GF_LED_VIEW_POSITION))
    {
        handling->block_view_pos = block;
    }
    else if (mls_cp_block_is_group_field_of(block, MLSCP_GF_LED_VIEW_SIZE))
    {
        handling->block_view_size = block;
    }

    return err;
}

mls_error mlscp_post_leds_scan_request_on_flush(mlscp_post_leds_handling *handling)
{
    mls_error err;
    mls_cp_block *b_view_pos = handling->block_view_pos;
    mls_cp_block *b_view_size = handling->block_view_size;
    mls_cp_block *b_part_pos = handling->block_part_pos;
    mls_cp_block *b_part_size = handling->block_part_size;
    mls_cp_block *b_part_items = handling->block_part_items;

    if (b_view_pos && b_view_size)
    {
        // as view
        mls_uint n_pos = mls_cp_block_get_body_uint(b_view_pos);
        mls_uint n_size = mls_cp_block_get_body_uint(b_view_size);

        err = mlscp_post_leds_scan_request_on_set_view(handling, n_pos, n_size);
        if (err)
        {
            return err;
        }
    }

    if (b_part_pos && b_part_size && b_part_items)
    {
        // as part
        mls_uint n_pos = mls_cp_block_get_body_uint(b_part_pos);
        mls_uint n_size = mls_cp_block_get_body_uint(b_part_size);
        mls_argb_array_slice slice = mls_cp_block_get_body_argb_array(b_part_items);

        if (n_size != slice.count)
        {
            return mls_errors_make(500, "mlscp_post_leds_scan_request_on_flush: bad size");
        }

        err = mlscp_post_leds_scan_request_on_set_part(handling, n_pos, slice.array, slice.count);
        if (err)
        {
            return err;
        }
    }

    return NULL;
}

mls_error mlscp_post_leds_scan_request_on_set_part(mlscp_post_leds_handling *handling, mls_uint pos, mls_argb *items, mls_uint count)
{
    mls_engine_led_buffer *led_buffer = &handling->context->app->engine.engine.led_buffer;
    mls_uint end = pos + count;

    if (end > led_buffer->total)
    {
        return mls_errors_make(500, "mls_engine_led_buffer: overflow");
    }

    mls_argb *item_src;
    mls_argb *item_dst;

    for (mls_uint i = 0; i < count; i++)
    {
        item_src = items + i;
        item_dst = led_buffer->items + (pos + i);
        *item_dst = *item_src;
    }

    led_buffer->revision++;
    return NULL;
}

mls_error mlscp_post_leds_scan_request_on_set_view(mlscp_post_leds_handling *handling, mls_uint pos, mls_uint count)
{
    mls_engine_led_buffer *led_buffer = &handling->context->app->engine.engine.led_buffer;
    led_buffer->view_size = 0;
    led_buffer->view_position = pos;
    led_buffer->view_size = count;
    led_buffer->revision++;
    return NULL;
}
