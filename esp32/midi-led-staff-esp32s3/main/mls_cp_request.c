#include "mls_cp_request.h"

mls_cp_block_head mls_cp_request_builder_prepare_head(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_cp_block_type bt);

////////////////////////////////////////////////////////////////////////////////

mls_cp_block_head mls_cp_request_builder_prepare_head(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_cp_block_type bt)
{
    mls_cp_block_head head;
    head.field = field;
    head.group = group;
    head.size = 0;
    head.type = bt;
    return head;
}

mls_error mls_cp_request_builder_init(mls_cp_request_builder *inst, mls_buffer *buffer)
{
    if (inst && buffer)
    {
        memset(inst, 0, sizeof(inst[0]));
        mls_cp_block_writer *writer = mls_cp_request_builder_get_writer(inst);
        return mls_cp_block_writer_init(writer, buffer);
    }
    return mls_errors_make(500, "param(s) is nil");
}

mls_buffer_slice mls_cp_request_builder_build(mls_cp_request_builder *inst)
{
    mls_buffer_slice result;
    memset(&result, 0, sizeof(result));

    mls_cp_block_writer *writer = mls_cp_request_builder_get_writer(inst);
    mls_cp_group_id group = MLS_CP_GROUP_COMMON;
    mls_uint16 version = mls_cp_version_to_uint16(&inst->version);

    mls_cp_request_builder_add_uint8(inst, group, MLS_CP_FIELD_COMMON_METHOD, inst->method);
    mls_cp_request_builder_add_uint16(inst, group, MLS_CP_FIELD_COMMON_VERSION, version);
    mls_cp_request_builder_add_uint32(inst, group, MLS_CP_FIELD_COMMON_TRANSACTION_ID, inst->transaction);
    mls_cp_request_builder_add_string(inst, group, MLS_CP_FIELD_COMMON_LOCATION, inst->location);

    mls_cp_request_builder_add_uint8(inst, group, MLS_CP_FIELD_COMMON_END_OF_PACK, 0);

    mls_cp_block_writer_flush(writer);
    result = writer->writer.writer.slice;

    // make check-sum
    mls_cp_checksum sum;
    mls_cp_checksum_init(&sum, &result);
    mls_cp_checksum_make(&sum);

    return result;
}

mls_cp_block_writer *mls_cp_request_builder_get_writer(mls_cp_request_builder *inst)
{
    if (inst)
    {
        return &inst->writer;
    }
    return NULL;
}

mls_error mls_cp_request_builder_get_error(mls_cp_request_builder *inst)
{
    mls_cp_block_writer *writer = mls_cp_request_builder_get_writer(inst);
    return mls_cp_block_writer_error(writer);
}

mls_bool mls_cp_request_builder_has_error(mls_cp_request_builder *inst)
{
    mls_cp_block_writer *writer = mls_cp_request_builder_get_writer(inst);
    mls_error err = mls_cp_block_writer_error(writer);
    return (err != NULL);
}

void mls_cp_request_builder_add_byte(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_byte value)
{
    mls_cp_block_head head = mls_cp_request_builder_prepare_head(inst, group, field, MLS_CP_TYPE_BYTE);
    mls_cp_block_writer *writer = mls_cp_request_builder_get_writer(inst);
    mls_cp_block_writer_write_byte(writer, &head, value);
}

void mls_cp_request_builder_add_bytes(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_byte *data, size_t len)
{
    mls_cp_block_head head = mls_cp_request_builder_prepare_head(inst, group, field, MLS_CP_TYPE_BYTES);
    mls_cp_block_writer *writer = mls_cp_request_builder_get_writer(inst);
    mls_cp_block_writer_write_bytes(writer, &head, data, len);
}

void mls_cp_request_builder_add_string(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_string value)
{
    mls_cp_block_head head = mls_cp_request_builder_prepare_head(inst, group, field, MLS_CP_TYPE_STRING);
    mls_cp_block_writer *writer = mls_cp_request_builder_get_writer(inst);
    mls_cp_block_writer_write_string(writer, &head, value);
}

void mls_cp_request_builder_add_argb(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_argb value)
{
    mls_cp_block_head head = mls_cp_request_builder_prepare_head(inst, group, field, MLS_CP_TYPE_ARGB);
    mls_cp_block_writer *writer = mls_cp_request_builder_get_writer(inst);
    mls_cp_block_writer_write_argb(writer, &head, value);
}

void mls_cp_request_builder_add_int8(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_int8 value)
{
    mls_cp_block_head head = mls_cp_request_builder_prepare_head(inst, group, field, MLS_CP_TYPE_INT8);
    mls_cp_block_writer *writer = mls_cp_request_builder_get_writer(inst);
    mls_cp_block_writer_write_int8(writer, &head, value);
}

void mls_cp_request_builder_add_int16(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_int16 value)
{
    mls_cp_block_head head = mls_cp_request_builder_prepare_head(inst, group, field, MLS_CP_TYPE_INT16);
    mls_cp_block_writer *writer = mls_cp_request_builder_get_writer(inst);
    mls_cp_block_writer_write_int16(writer, &head, value);
}

void mls_cp_request_builder_add_int32(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_int32 value)
{
    mls_cp_block_head head = mls_cp_request_builder_prepare_head(inst, group, field, MLS_CP_TYPE_INT32);
    mls_cp_block_writer *writer = mls_cp_request_builder_get_writer(inst);
    mls_cp_block_writer_write_int32(writer, &head, value);
}

void mls_cp_request_builder_add_int64(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_int64 value)
{
    mls_cp_block_head head = mls_cp_request_builder_prepare_head(inst, group, field, MLS_CP_TYPE_INT64);
    mls_cp_block_writer *writer = mls_cp_request_builder_get_writer(inst);
    mls_cp_block_writer_write_int64(writer, &head, value);
}

void mls_cp_request_builder_add_uint8(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_uint8 value)
{
    mls_cp_block_head head = mls_cp_request_builder_prepare_head(inst, group, field, MLS_CP_TYPE_UINT8);
    mls_cp_block_writer *writer = mls_cp_request_builder_get_writer(inst);
    mls_cp_block_writer_write_uint8(writer, &head, value);
}

void mls_cp_request_builder_add_uint16(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_uint16 value)
{
    mls_cp_block_head head = mls_cp_request_builder_prepare_head(inst, group, field, MLS_CP_TYPE_UINT16);
    mls_cp_block_writer *writer = mls_cp_request_builder_get_writer(inst);
    mls_cp_block_writer_write_uint16(writer, &head, value);
}

void mls_cp_request_builder_add_uint32(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_uint32 value)
{
    mls_cp_block_head head = mls_cp_request_builder_prepare_head(inst, group, field, MLS_CP_TYPE_UINT32);
    mls_cp_block_writer *writer = mls_cp_request_builder_get_writer(inst);
    mls_cp_block_writer_write_uint32(writer, &head, value);
}

void mls_cp_request_builder_add_uint64(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_uint64 value)
{
    mls_cp_block_head head = mls_cp_request_builder_prepare_head(inst, group, field, MLS_CP_TYPE_UINT64);
    mls_cp_block_writer *writer = mls_cp_request_builder_get_writer(inst);
    mls_cp_block_writer_write_uint64(writer, &head, value);
}
