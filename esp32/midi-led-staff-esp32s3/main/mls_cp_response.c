#include "mls_cp_response.h"
#include "mls_cp_context.h"
#include "mls_cp_server.h"

mls_cp_block_head mls_cp_response_builder_prepare_head(mls_cp_response_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_cp_block_type b_type);

////////////////////////////////////////////////////////////////////////////////

mls_error mls_cp_response_builder_init(mls_cp_response_builder *inst, mls_buffer *buffer)
{
    if (inst == NULL || buffer == NULL)
    {
        return mls_errors_make(500, "mls_cp_response_builder_init: param(s) is nil");
    }
    mls_cp_block_writer *writer = mls_cp_response_builder_get_writer(inst);
    return mls_cp_block_writer_init(writer, buffer);
}

mls_error mls_cp_response_builder_init_with_context(mls_cp_response_builder *inst, mls_cp_context *ctx)
{
    if ((inst == NULL) || (ctx == NULL))
    {
        return mls_errors_make(500, "mls_cp_response_builder_init_with_context: param(s) is nil");
    }

    mls_error err;

    mls_cp_response *resp = ctx->response;
    mls_cp_request *req = ctx->request;
    mls_cp_dispatcher *disp = ctx->dispatcher;
    mls_cp_handler *handler = ctx->handler;
    mls_cp_server *server = ctx->server;

    if ((resp == NULL) || (req == NULL) || (disp == NULL) || (handler == NULL) || (server == NULL))
    {
        return mls_errors_make(500, "mls_cp_response_builder_init_with_context: context contains nil member");
    }

    mls_buffer *buffer = resp->buffer;
    err = mls_cp_response_builder_init(inst, buffer);
    if (err)
    {
        return err;
    }

    inst->to = req->remote;
    inst->status.code = MLS_CP_STATUS_OK;
    inst->status.message = "OK";
    inst->version = mls_cp_version_impl();
    inst->transaction = ctx->transaction;

    return NULL;
}

mls_cp_block_head mls_cp_response_builder_prepare_head(mls_cp_response_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_cp_block_type b_type)
{
    mls_cp_block_head head;
    head.size = 0;
    head.type = b_type;
    head.group = group;
    head.field = field;
    return head;
}

mls_error mls_cp_response_builder_build_and_send(mls_cp_response_builder *inst, mls_cp_context *ctx)
{
    if ((inst == NULL) || (ctx == NULL))
    {
        return mls_errors_make(500, "mls_cp_response_builder_build_and_send: param(s) is nil");
    }

    mls_cp_dispatcher *dispatcher = ctx->dispatcher;
    mls_cp_response *resp = ctx->response;
    if (dispatcher == NULL)
    {
        return mls_errors_make(500, "mls_cp_response_builder_build_and_send: dispatcher is nil");
    }
    if (resp == NULL)
    {
        return mls_errors_make(500, "mls_cp_response_builder_build_and_send: response is nil");
    }

    mls_cp_dispatcher_func fn = dispatcher->fn;
    if (fn == NULL)
    {
        return mls_errors_make(500, "mls_cp_response_builder_build_and_send: dispatcher(fn) is nil");
    }

    mls_cp_response_builder_build(inst);
    resp->status = inst->status;
    resp->remote = inst->to;

    return fn(ctx, resp);
}

mls_buffer_slice mls_cp_response_builder_build(mls_cp_response_builder *inst)
{
    mls_buffer_slice result;
    memset(&result, 0, sizeof(result));

    mls_uint16 code = inst->status.code;
    mls_string msg = inst->status.message;
    mls_uint16 version = mls_cp_version_to_uint16(&inst->version);
    mls_cp_transaction_id trans_id = inst->transaction;
    mls_timestamp time = inst->timestamp;

    mls_cp_block_writer *writer = mls_cp_response_builder_get_writer(inst);
    mls_cp_group_id group = MLS_CP_GROUP_COMMON;

    mls_cp_response_builder_add_uint16(inst, group, MLS_CP_FIELD_COMMON_STATUS_CODE, code);
    mls_cp_response_builder_add_string(inst, group, MLS_CP_FIELD_COMMON_STATUS_MSG, msg);
    mls_cp_response_builder_add_uint16(inst, group, MLS_CP_FIELD_COMMON_VERSION, version);
    mls_cp_response_builder_add_uint32(inst, group, MLS_CP_FIELD_COMMON_TRANSACTION_ID, trans_id);
    mls_cp_response_builder_add_int64(inst, group, MLS_CP_FIELD_COMMON_TIMESTAMP, time);

    mls_cp_response_builder_add_uint8(inst, group, MLS_CP_FIELD_COMMON_END_OF_PACK, 0);

    mls_cp_block_writer_flush(writer);
    result = inst->writer.writer.writer.slice;

    // make check-sum
    mls_cp_checksum sum;
    mls_cp_checksum_init(&sum, &result);
    mls_cp_checksum_make(&sum);

    return result;
}

mls_cp_block_writer *mls_cp_response_builder_get_writer(mls_cp_response_builder *inst)
{
    if (inst)
    {
        return &inst->writer;
    }
    return NULL;
}

void mls_cp_response_builder_add_byte(mls_cp_response_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_byte value)
{
    mls_cp_block_head head = mls_cp_response_builder_prepare_head(inst, group, field, MLS_CP_TYPE_BYTE);
    mls_cp_block_writer *writer = mls_cp_response_builder_get_writer(inst);
    mls_cp_block_writer_write_byte(writer, &head, value);
}

void mls_cp_response_builder_add_bytes(mls_cp_response_builder *inst, mls_cp_group_id group, mls_cp_field_id field, const void *data, size_t len)
{
    mls_cp_block_head head = mls_cp_response_builder_prepare_head(inst, group, field, MLS_CP_TYPE_BYTES);
    mls_cp_block_writer *writer = mls_cp_response_builder_get_writer(inst);
    mls_cp_block_writer_write_bytes(writer, &head, data, len);
}

void mls_cp_response_builder_add_string(mls_cp_response_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_string value)
{
    mls_cp_block_head head = mls_cp_response_builder_prepare_head(inst, group, field, MLS_CP_TYPE_STRING);
    mls_cp_block_writer *writer = mls_cp_response_builder_get_writer(inst);
    mls_cp_block_writer_write_string(writer, &head, value);
}

void mls_cp_response_builder_add_no_value(mls_cp_response_builder *inst, mls_cp_group_id group, mls_cp_field_id field)
{
    mls_cp_block_head head = mls_cp_response_builder_prepare_head(inst, group, field, MLS_CP_TYPE_NO_VALUE);
    mls_cp_block_writer *writer = mls_cp_response_builder_get_writer(inst);
    mls_cp_block_writer_write_no_value(writer, &head);
}

void mls_cp_response_builder_add_argb(mls_cp_response_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_argb value)
{
    mls_cp_block_head head = mls_cp_response_builder_prepare_head(inst, group, field, MLS_CP_TYPE_ARGB);
    mls_cp_block_writer *writer = mls_cp_response_builder_get_writer(inst);
    mls_cp_block_writer_write_argb(writer, &head, value);
}

void mls_cp_response_builder_add_argb_array(mls_cp_response_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_argb *items, size_t items_size_in_byte)
{
    mls_cp_block_head head = mls_cp_response_builder_prepare_head(inst, group, field, MLS_CP_TYPE_ARGB_ARRAY);
    mls_cp_block_writer *writer = mls_cp_response_builder_get_writer(inst);
    mls_cp_block_writer_write_argb_array(writer, &head, items, items_size_in_byte);
}

void mls_cp_response_builder_add_int8(mls_cp_response_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_int8 value)
{
    mls_cp_block_head head = mls_cp_response_builder_prepare_head(inst, group, field, MLS_CP_TYPE_INT8);
    mls_cp_block_writer *writer = mls_cp_response_builder_get_writer(inst);
    mls_cp_block_writer_write_int8(writer, &head, value);
}

void mls_cp_response_builder_add_int16(mls_cp_response_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_int16 value)
{
    mls_cp_block_head head = mls_cp_response_builder_prepare_head(inst, group, field, MLS_CP_TYPE_INT16);
    mls_cp_block_writer *writer = mls_cp_response_builder_get_writer(inst);
    mls_cp_block_writer_write_int16(writer, &head, value);
}

void mls_cp_response_builder_add_int32(mls_cp_response_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_int32 value)
{
    mls_cp_block_head head = mls_cp_response_builder_prepare_head(inst, group, field, MLS_CP_TYPE_INT32);
    mls_cp_block_writer *writer = mls_cp_response_builder_get_writer(inst);
    mls_cp_block_writer_write_int32(writer, &head, value);
}

void mls_cp_response_builder_add_int64(mls_cp_response_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_int64 value)
{
    mls_cp_block_head head = mls_cp_response_builder_prepare_head(inst, group, field, MLS_CP_TYPE_INT64);
    mls_cp_block_writer *writer = mls_cp_response_builder_get_writer(inst);
    mls_cp_block_writer_write_int64(writer, &head, value);
}

void mls_cp_response_builder_add_uint8(mls_cp_response_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_uint8 value)
{
    mls_cp_block_head head = mls_cp_response_builder_prepare_head(inst, group, field, MLS_CP_TYPE_UINT8);
    mls_cp_block_writer *writer = mls_cp_response_builder_get_writer(inst);
    mls_cp_block_writer_write_uint8(writer, &head, value);
}

void mls_cp_response_builder_add_uint16(mls_cp_response_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_uint16 value)
{
    mls_cp_block_head head = mls_cp_response_builder_prepare_head(inst, group, field, MLS_CP_TYPE_UINT16);
    mls_cp_block_writer *writer = mls_cp_response_builder_get_writer(inst);
    mls_cp_block_writer_write_uint16(writer, &head, value);
}

void mls_cp_response_builder_add_uint32(mls_cp_response_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_uint32 value)
{
    mls_cp_block_head head = mls_cp_response_builder_prepare_head(inst, group, field, MLS_CP_TYPE_UINT32);
    mls_cp_block_writer *writer = mls_cp_response_builder_get_writer(inst);
    mls_cp_block_writer_write_uint32(writer, &head, value);
}

void mls_cp_response_builder_add_uint64(mls_cp_response_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_uint64 value)
{
    mls_cp_block_head head = mls_cp_response_builder_prepare_head(inst, group, field, MLS_CP_TYPE_UINT64);
    mls_cp_block_writer *writer = mls_cp_response_builder_get_writer(inst);
    mls_cp_block_writer_write_uint64(writer, &head, value);
}

////////////////////////////////////////////////////////////////////////////////
// EOF
