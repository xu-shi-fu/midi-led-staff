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

mls_error mls_cp_block_array_create(mls_cp_block_array *buffer, mls_uint capacity)
{
    if (buffer == NULL)
    {
        return mls_errors_make(0, "param is null");
    }

    if (buffer->entity)
    {
        return NULL;
    }

    mls_cp_block_array_entity *ent = mls_cp_block_array_entity_create(capacity);

    if (ent == NULL)
    {
        return mls_errors_make(0, "create block array entity failed");
    }

    buffer->entity = ent;
    buffer->items = ent->items;
    buffer->capacity = capacity;
    buffer->count = 0;
    buffer->overflow = NO;
    return NULL;
}

void mls_cp_block_array_add_block(mls_cp_block_array *array, mls_cp_block *block)
{
    if (array == NULL || block == NULL)
    {
        return;
    }
    const mls_uint count = array->count;
    const mls_uint capacity = array->capacity;
    mls_cp_block_array_item *items = array->items;
    if (items && (count < capacity))
    {
        items[count].block = block;
        array->count = count + 1;
    }
    else
    {
        array->overflow = MLS_YES;
    }
}

void mls_cp_block_array_add_item(mls_cp_block_array *buffer, mls_cp_block_array_item *item)
{
    if (item)
    {
        mls_cp_block_array_add_block(buffer, item->block);
    }
}

/*******************************************************************************
 * mls_cp_block_array_entity
 */

mls_cp_block_array_entity *mls_cp_block_array_entity_create(mls_uint capacity)
{
    size_t size1 = sizeof(mls_cp_block_array_entity);
    size_t size2 = sizeof(mls_cp_block_array_item) * capacity;
    size_t size = size1 + size2;

    void *p = malloc(size);
    if (p == NULL)
    {
        return NULL;
    }
    memset(p, 0, size);

    mls_cp_block_array_entity *entity = p;
    entity->capacity = capacity;
    return entity;
}

void mls_cp_block_array_entity_release(mls_cp_block_array_entity *entity)
{
    if (entity)
    {
        free(entity);
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
        mls_buffer_writer_reset(builder->writer);
    }
}

mls_bool mls_cp_pack_builder_is_overflow(mls_cp_pack_builder *builder)
{
    if (builder)
    {
        if (mls_cp_block_array_is_overflow(builder->blocks))
        {
            return YES;
        }
        if (mls_buffer_writer_is_overflow(builder->writer))
        {
            return YES;
        }
    }
    return NO;
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
    mls_cp_block *block;
    mls_error err;

    if (callback == NULL)
    {
        return mls_errors_make(0, "callback function is null");
    }

    for (; p < ending;)
    {
        block = (mls_cp_block *)p;
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
