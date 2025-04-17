// mls_control_protocol.c

#include "mls_control_protocol.h"
#include "mls_tasks.h"

/*******************************************************************************
 * mls_cp_block_array
 */

void mls_cp_block_array_init(mls_cp_block_array *buffer)
{
    if (buffer)
    {
        memset(buffer, 0, sizeof(buffer[0]));
    }
}

void mls_cp_block_array_add_entity(mls_cp_block_array *array, mls_cp_block_entity *entity)
{
    if (array == NULL || entity == NULL)
    {
        return;
    }
    const uint count = array->count;
    const uint capacity = array->capacity;
    mls_cp_block_ref *blocks = array->blocks;
    if (blocks && (count < capacity))
    {
        blocks[count].block = entity;
        array->count = count + 1;
    }
    else
    {
        array->overflow = true;
    }
}

void mls_cp_block_array_add_ref(mls_cp_block_array *buffer, mls_cp_block_ref *ref)
{
    if (ref)
    {
        mls_cp_block_array_add_entity(buffer, ref->block);
    }
}

/*******************************************************************************
 * mls_cp_pack_builder
 */

void mls_cp_pack_builder_init(mls_cp_pack_builder *builder)
{
    if (builder)
    {
        memset(builder, 0, sizeof(builder[0]));
    }
}

void mls_cp_pack_builder_reset(mls_cp_pack_builder *builder)
{
    if (builder)
    {
        mls_cp_block_array_reset(builder->blocks);
        mls_buffer_reset(builder->buffer);
    }
}

bool mls_cp_pack_builder_is_overflow(mls_cp_pack_builder *builder)
{
    if (builder)
    {
        if (mls_cp_block_array_is_overflow(builder->blocks))
        {
            return true;
        }
        if (mls_buffer_is_overflow(builder->buffer))
        {
            return true;
        }
    }
    return false;
}

void mls_cp_pack_builder_add_uint8(mls_cp_pack_builder *builder, mls_cp_block_head *head, uint8_t value) {}
void mls_cp_pack_builder_add_uint16(mls_cp_pack_builder *builder, mls_cp_block_head *head, uint16_t value) {}
void mls_cp_pack_builder_add_uint32(mls_cp_pack_builder *builder, mls_cp_block_head *head, uint32_t value) {}
void mls_cp_pack_builder_add_uint64(mls_cp_pack_builder *builder, mls_cp_block_head *head, uint64_t value) {}
void mls_cp_pack_builder_add_bytes(mls_cp_pack_builder *builder, mls_cp_block_head *head, uint8_t *data, size_t len) {}
void mls_cp_pack_builder_add_string(mls_cp_pack_builder *builder, mls_cp_block_head *head, char *str) {}

/*******************************************************************************
 * mls_cp_pack_parser
 */

void mls_cp_pack_parser_init(mls_cp_pack_parser *parser)
{
    memset(parser, 0, sizeof(parser[0]));
}

mls_error mls_cp_pack_parser_parse(mls_cp_pack_parser *parser, uint8_t *data, size_t len)
{
    if (parser == NULL || data == NULL)
    {
        return mls_errors_make(0, "param(s) is null");
    }

    uint8_t *p = data;
    uint8_t *ending = data + len;
    uint8_t *next_pos;
    mls_cp_parser_callback_func callback = parser->callback;
    mls_cp_block_entity *block;
    mls_error err;

    if (callback == NULL)
    {
        return mls_errors_make(0, "callback function is null");
    }

    for (; p < ending;)
    {
        block = (mls_cp_block_entity *)p;
        next_pos = p + block->head.size;
        if (next_pos > ending)
        {
            return mls_errors_make(0, "ending at bad position");
        }
        err = callback(parser, block);
        if (err)
        {
            return err;
        }
        p = next_pos;
    }

    return NULL;
}

/*******************************************************************************
 * EOF
 */
