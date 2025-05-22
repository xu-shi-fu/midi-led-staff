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
 * mls_cp_block_head
 */

mls_cp_block_head *mls_cp_block_head_set_field(mls_cp_block_head *head, mls_cp_field_id field)
{
    if (head)
    {
        head->field = field;
    }
    return head;
}

/*******************************************************************************
 * mls_cp_block_writer
 */

mls_net_writer *mls_cp_block_writer_get_inner(mls_cp_block_writer *writer);
void mls_cp_block_writer_write_block_head_with_body_len(mls_cp_block_writer *writer, mls_cp_block_head *head, size_t body_len);

mls_error mls_cp_block_writer_init(mls_cp_block_writer *writer, mls_buffer *buffer)
{
    mls_net_writer *inner = mls_cp_block_writer_get_inner(writer);
    return mls_net_writer_init(inner, buffer);
}

mls_error mls_cp_block_writer_error(mls_cp_block_writer *writer)
{
    mls_net_writer *inner = mls_cp_block_writer_get_inner(writer);
    return mls_net_writer_error(inner);
}

void mls_cp_block_writer_reset(mls_cp_block_writer *writer)
{
    mls_net_writer *inner = mls_cp_block_writer_get_inner(writer);
    mls_net_writer_reset(inner);
}

void mls_cp_block_writer_flush(mls_cp_block_writer *writer)
{
    mls_net_writer *inner = mls_cp_block_writer_get_inner(writer);
    mls_net_writer_flush(inner);
}

mls_net_writer *mls_cp_block_writer_get_inner(mls_cp_block_writer *writer)
{
    if (writer)
    {
        return &writer->writer;
    }
    return NULL;
}

void mls_cp_block_writer_write_block_head_with_body_len(mls_cp_block_writer *writer, mls_cp_block_head *head, size_t body_len)
{
    if (writer && head)
    {
        size_t head_len = sizeof(head[0]);
        head->size = head_len + body_len;
        mls_net_writer *inner = mls_cp_block_writer_get_inner(writer);
        mls_net_writer_write_bytes(inner, (mls_byte *)head, head_len);
    }
}

void mls_cp_block_writer_write_block_head(mls_cp_block_writer *writer, mls_cp_block_head *head)
{
    if (writer && head)
    {
        mls_net_writer *inner = mls_cp_block_writer_get_inner(writer);
        mls_net_writer_write_bytes(inner, (mls_byte *)head, sizeof(head[0]));
    }
}

void mls_cp_block_writer_write_block(mls_cp_block_writer *writer, mls_cp_block_head *head, const void *body_data, size_t body_len)
{
    const size_t body_len_limit = 250;
    if (writer && head && body_data)
    {
        if (body_len > body_len_limit)
        {
            mls_error err = mls_errors_make(500, "body length is too long");
            mls_error_holder *eh = &writer->writer.writer.err_holder;
            mls_error_holder_push(eh, err);
            return;
        }
        size_t head_len = sizeof(head[0]);
        head->size = head_len + body_len;
        mls_net_writer *inner = mls_cp_block_writer_get_inner(writer);
        mls_net_writer_write_bytes(inner, (mls_byte *)head, head_len);
        mls_net_writer_write_bytes(inner, body_data, body_len);
    }
}

void mls_cp_block_writer_write_byte(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_byte b)
{
    mls_cp_block_writer_write_block(writer, head, &b, sizeof(b));
}

void mls_cp_block_writer_write_bytes(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_byte *data_ptr, size_t data_len)
{
    mls_cp_block_writer_write_block(writer, head, data_ptr, data_len);
}

void mls_cp_block_writer_write_string(mls_cp_block_writer *writer, mls_cp_block_head *head, const char *str)
{
    if (writer && head && str)
    {
        size_t str_len = strlen(str);
        mls_cp_block_writer_write_block(writer, head, str, str_len + 1);
    }
}

void mls_cp_block_writer_write_uint8(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_uint8 n)
{
    size_t body_len = sizeof(n);
    mls_cp_block_writer_write_block_head_with_body_len(writer, head, body_len);
    mls_net_writer *inner = mls_cp_block_writer_get_inner(writer);
    mls_net_writer_write_uint8(inner, n);
}

void mls_cp_block_writer_write_uint16(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_uint16 n)
{
    size_t body_len = sizeof(n);
    mls_cp_block_writer_write_block_head_with_body_len(writer, head, body_len);
    mls_net_writer *inner = mls_cp_block_writer_get_inner(writer);
    mls_net_writer_write_uint16(inner, n);
}

void mls_cp_block_writer_write_uint32(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_uint32 n)
{
    size_t body_len = sizeof(n);
    mls_cp_block_writer_write_block_head_with_body_len(writer, head, body_len);
    mls_net_writer *inner = mls_cp_block_writer_get_inner(writer);
    mls_net_writer_write_uint32(inner, n);
}

void mls_cp_block_writer_write_uint64(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_uint64 n)
{
    size_t body_len = sizeof(n);
    mls_cp_block_writer_write_block_head_with_body_len(writer, head, body_len);
    mls_net_writer *inner = mls_cp_block_writer_get_inner(writer);
    mls_net_writer_write_uint64(inner, n);
}

void mls_cp_block_writer_write_int8(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_int8 n)
{
    size_t body_len = sizeof(n);
    mls_cp_block_writer_write_block_head_with_body_len(writer, head, body_len);
    mls_net_writer *inner = mls_cp_block_writer_get_inner(writer);
    mls_net_writer_write_int8(inner, n);
}

void mls_cp_block_writer_write_int16(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_int16 n)
{
    size_t body_len = sizeof(n);
    mls_cp_block_writer_write_block_head_with_body_len(writer, head, body_len);
    mls_net_writer *inner = mls_cp_block_writer_get_inner(writer);
    mls_net_writer_write_int16(inner, n);
}

void mls_cp_block_writer_write_int32(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_int32 n)
{
    size_t body_len = sizeof(n);
    mls_cp_block_writer_write_block_head_with_body_len(writer, head, body_len);
    mls_net_writer *inner = mls_cp_block_writer_get_inner(writer);
    mls_net_writer_write_int32(inner, n);
}

void mls_cp_block_writer_write_int64(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_int64 n)
{
    size_t body_len = sizeof(n);
    mls_cp_block_writer_write_block_head_with_body_len(writer, head, body_len);
    mls_net_writer *inner = mls_cp_block_writer_get_inner(writer);
    mls_net_writer_write_int64(inner, n);
}

/*******************************************************************************
 * EOF
 */
