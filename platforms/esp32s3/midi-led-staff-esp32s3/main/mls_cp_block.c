#include "mls_cp_block.h"
#include "mls_common.h"

#include <netinet/in.h>

mls_bool mls_cp_block_is_type_size_of(mls_cp_block *block, mls_cp_block_type block_type, size_t size2);

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

mls_cp_block_head *mls_cp_block_head_set_group(mls_cp_block_head *head, mls_cp_group_id group)
{
    if (head)
    {
        head->group = group;
    }
    return head;
}

mls_cp_block_head *mls_cp_block_head_set_size(mls_cp_block_head *head, mls_cp_block_size size)
{
    if (head)
    {
        head->size = size;
    }
    return head;
}

mls_cp_block_head *mls_cp_block_head_set_type(mls_cp_block_head *head, mls_cp_block_type bt)
{
    if (head)
    {
        head->type = bt;
    }
    return head;
}

/*******************************************************************************
 * mls_cp_block
 */

mls_bool mls_cp_block_is_type_size_of(mls_cp_block *block, mls_cp_block_type block_type, size_t size2)
{
    if (block)
    {
        mls_cp_block_head head = block->head;
        size_t size12 = sizeof(head) + size2;
        return ((head.type == block_type) && (head.size == size12));
    }
    return NO;
}

mls_byte mls_cp_block_get_body_byte(mls_cp_block *block)
{
    mls_byte value = 0;
    mls_byte *ptr = NULL;
    size_t size2 = sizeof(value);
    if (mls_cp_block_is_type_size_of(block, MLS_CP_TYPE_UINT8, size2))
    {
        ptr = (void *)block->body;
        value = ptr[0];
    }
    return value;
}

mls_buffer_slice mls_cp_block_get_body_bytes(mls_cp_block *block)
{
    mls_buffer_slice slice;
    memset(&slice, 0, sizeof(slice));

    if (block == NULL)
    {
        return slice;
    }

    mls_cp_block_head head = block->head;
    size_t size12 = head.size;
    size_t size2 = size12 - sizeof(head);

    if ((head.type == MLS_CP_TYPE_BYTES) && (size2 < size12))
    {
        slice.data = block->body;
        slice.length = size2;
    }
    return slice;
}

mls_string mls_cp_block_get_body_string(mls_cp_block *block)
{
    if (block == NULL)
    {
        return NULL;
    }

    mls_cp_block_head head = block->head;
    size_t size12 = head.size;
    size_t size2 = size12 - sizeof(head);
    mls_byte *body = block->body;
    mls_byte *end = body + (size2 - 1);

    if ((head.type == MLS_CP_TYPE_STRING) && (end[0] == 0))
    {
        return (char *)body;
    }
    return NULL;
}

mls_int8 mls_cp_block_get_body_int8(mls_cp_block *block)
{
    mls_int8 value = 0;
    mls_int8 *ptr = NULL;
    size_t size2 = sizeof(value);
    if (mls_cp_block_is_type_size_of(block, MLS_CP_TYPE_INT8, size2))
    {
        ptr = (void *)block->body;
        value = ptr[0];
    }
    return value;
}

mls_int16 mls_cp_block_get_body_int16(mls_cp_block *block)
{
    mls_int16 value = 0;
    mls_int16 *ptr = NULL;
    size_t size2 = sizeof(value);
    if (mls_cp_block_is_type_size_of(block, MLS_CP_TYPE_INT16, size2))
    {
        ptr = (void *)block->body;
        value = ptr[0];
    }
    return ntohs(value);
}

mls_int32 mls_cp_block_get_body_int32(mls_cp_block *block)
{
    mls_int32 value = 0;
    mls_int32 *ptr = NULL;
    size_t size2 = sizeof(value);
    if (mls_cp_block_is_type_size_of(block, MLS_CP_TYPE_INT32, size2))
    {
        ptr = (void *)block->body;
        value = ptr[0];
    }
    return ntohl(value);
}

mls_int64 mls_cp_block_get_body_int64(mls_cp_block *block)
{
    mls_int64 value = 0;
    mls_int64 *ptr = NULL;
    size_t size2 = sizeof(value);
    if (mls_cp_block_is_type_size_of(block, MLS_CP_TYPE_INT64, size2))
    {
        ptr = (void *)block->body;
        value = ptr[0];
    }
    return ntohll(value);
}

mls_uint8 mls_cp_block_get_body_uint8(mls_cp_block *block)
{
    mls_uint8 value = 0;
    mls_uint8 *ptr = NULL;
    size_t size2 = sizeof(value);
    if (mls_cp_block_is_type_size_of(block, MLS_CP_TYPE_UINT8, size2))
    {
        ptr = (void *)block->body;
        value = ptr[0];
    }
    return value;
}

mls_uint16 mls_cp_block_get_body_uint16(mls_cp_block *block)
{
    mls_uint16 value = 0;
    mls_uint16 *ptr = NULL;
    size_t size2 = sizeof(value);
    if (mls_cp_block_is_type_size_of(block, MLS_CP_TYPE_UINT16, size2))
    {
        ptr = (void *)block->body;
        value = ptr[0];
    }
    return ntohs(value);
}

mls_uint32 mls_cp_block_get_body_uint32(mls_cp_block *block)
{
    mls_uint32 value = 0;
    mls_uint32 *ptr = NULL;
    size_t size2 = sizeof(value);
    if (mls_cp_block_is_type_size_of(block, MLS_CP_TYPE_UINT32, size2))
    {
        ptr = (void *)block->body;
        value = ptr[0];
    }
    return ntohl(value);
}

mls_uint64 mls_cp_block_get_body_uint64(mls_cp_block *block)
{
    mls_uint64 value = 0;
    mls_uint64 *ptr = NULL;
    size_t size2 = sizeof(value);
    if (mls_cp_block_is_type_size_of(block, MLS_CP_TYPE_UINT64, size2))
    {
        ptr = (void *)block->body;
        value = ptr[0];
    }
    return ntohll(value);
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
    mls_cp_block_head_set_type(head, MLS_CP_TYPE_BYTE);
    mls_cp_block_writer_write_block(writer, head, &b, sizeof(b));
}

void mls_cp_block_writer_write_bytes(mls_cp_block_writer *writer, mls_cp_block_head *head, const mls_byte *data_ptr, size_t data_len)
{
    mls_cp_block_head_set_type(head, MLS_CP_TYPE_BYTES);
    mls_cp_block_writer_write_block(writer, head, data_ptr, data_len);
}

void mls_cp_block_writer_write_string(mls_cp_block_writer *writer, mls_cp_block_head *head, const char *str)
{
    size_t str_len = 0;
    if (str)
    {
        str_len = strlen(str);
    }
    mls_cp_block_head_set_type(head, MLS_CP_TYPE_STRING);
    mls_cp_block_writer_write_block(writer, head, str, str_len + 1);
}

void mls_cp_block_writer_write_argb(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_argb argb)
{
    mls_cp_block_head_set_type(head, MLS_CP_TYPE_ARGB);
    mls_cp_block_writer_write_block(writer, head, &argb, sizeof(argb));
}

void mls_cp_block_writer_write_uint8(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_uint8 n)
{
    size_t body_len = sizeof(n);
    mls_cp_block_head_set_type(head, MLS_CP_TYPE_UINT8);
    mls_cp_block_writer_write_block_head_with_body_len(writer, head, body_len);
    mls_net_writer *inner = mls_cp_block_writer_get_inner(writer);
    mls_net_writer_write_uint8(inner, n);
}

void mls_cp_block_writer_write_uint16(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_uint16 n)
{
    size_t body_len = sizeof(n);
    mls_cp_block_head_set_type(head, MLS_CP_TYPE_UINT16);
    mls_cp_block_writer_write_block_head_with_body_len(writer, head, body_len);
    mls_net_writer *inner = mls_cp_block_writer_get_inner(writer);
    mls_net_writer_write_uint16(inner, n);
}

void mls_cp_block_writer_write_uint32(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_uint32 n)
{
    size_t body_len = sizeof(n);
    mls_cp_block_head_set_type(head, MLS_CP_TYPE_UINT32);
    mls_cp_block_writer_write_block_head_with_body_len(writer, head, body_len);
    mls_net_writer *inner = mls_cp_block_writer_get_inner(writer);
    mls_net_writer_write_uint32(inner, n);
}

void mls_cp_block_writer_write_uint64(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_uint64 n)
{
    size_t body_len = sizeof(n);
    mls_cp_block_head_set_type(head, MLS_CP_TYPE_UINT64);
    mls_cp_block_writer_write_block_head_with_body_len(writer, head, body_len);
    mls_net_writer *inner = mls_cp_block_writer_get_inner(writer);
    mls_net_writer_write_uint64(inner, n);
}

void mls_cp_block_writer_write_int8(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_int8 n)
{
    size_t body_len = sizeof(n);
    mls_cp_block_head_set_type(head, MLS_CP_TYPE_INT8);
    mls_cp_block_writer_write_block_head_with_body_len(writer, head, body_len);
    mls_net_writer *inner = mls_cp_block_writer_get_inner(writer);
    mls_net_writer_write_int8(inner, n);
}

void mls_cp_block_writer_write_int16(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_int16 n)
{
    size_t body_len = sizeof(n);
    mls_cp_block_head_set_type(head, MLS_CP_TYPE_INT16);
    mls_cp_block_writer_write_block_head_with_body_len(writer, head, body_len);
    mls_net_writer *inner = mls_cp_block_writer_get_inner(writer);
    mls_net_writer_write_int16(inner, n);
}

void mls_cp_block_writer_write_int32(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_int32 n)
{
    size_t body_len = sizeof(n);
    mls_cp_block_head_set_type(head, MLS_CP_TYPE_INT32);
    mls_cp_block_writer_write_block_head_with_body_len(writer, head, body_len);
    mls_net_writer *inner = mls_cp_block_writer_get_inner(writer);
    mls_net_writer_write_int32(inner, n);
}

void mls_cp_block_writer_write_int64(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_int64 n)
{
    size_t body_len = sizeof(n);
    mls_cp_block_head_set_type(head, MLS_CP_TYPE_INT64);
    mls_cp_block_writer_write_block_head_with_body_len(writer, head, body_len);
    mls_net_writer *inner = mls_cp_block_writer_get_inner(writer);
    mls_net_writer_write_int64(inner, n);
}

/*******************************************************************************
 * mls_cp_block_array
 */

void mls_cp_block_array_log_block(mls_cp_block_array *array, int index, mls_cp_block *block);

void mls_cp_block_array_init(mls_cp_block_array *buffer)
{
    if (buffer)
    {
        memset(buffer, 0, sizeof(buffer[0]));
    }
}

void mls_cp_block_array_reset(mls_cp_block_array *buffer)
{
    if (buffer)
    {
        mls_cp_block_array_entity *ent = buffer->entity;
        if (ent)
        {
            buffer->capacity = ent->capacity;
            buffer->items = ent->items;
        }
        buffer->count = 0;
        buffer->overflow = NO;
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

void mls_cp_block_array_log_all(mls_cp_block_array *array)
{
    if (array == NULL)
    {
        return;
    }

    mls_cp_block_array_item *items = array->items;
    mls_uint count = array->count;

    if (items == NULL)
    {
        return;
    }

    for (mls_uint i = 0; i < count; ++i)
    {
        mls_cp_block_array_item item = items[i];
        mls_cp_block_array_log_block(array, i, item.block);
    }
}

void mls_cp_block_array_log_block(mls_cp_block_array *array, int index, mls_cp_block *block)
{
    if (block == NULL)
    {
        return;
    }

    mls_cp_block_head head = block->head;
    const char *str_type = mls_cp_block_type_stringify(head.type);
    const char *str_field = mls_cp_group_field_stringify(head.group, head.field);

#define MLS_CBALB_FMT "[block index:%d size:%d type:%d(%s) group:%d field:%d(%s)]"

    ESP_LOGI(TAG, MLS_CBALB_FMT, index, head.size, head.type, str_type, head.group, head.field, str_field);
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
 * other
 */

mls_uint16 mls_cp_version_to_uint16(mls_cp_version *version)
{
    if (version)
    {
        mls_uint16 v1 = version->major;
        mls_uint16 v2 = version->minor;
        return ((v1 << 8) | (v2));
    }
    return 0;
}

mls_string mls_cp_block_type_stringify(mls_cp_block_type b_type)
{
    switch (b_type)
    {
    case MLS_CP_TYPE_UINT8:
        return "uint8";
    case MLS_CP_TYPE_UINT16:
        return "uint16";
    case MLS_CP_TYPE_UINT32:
        return "uint32";
    case MLS_CP_TYPE_UINT64:
        return "uint64";

    case MLS_CP_TYPE_INT8:
        return "int8";
    case MLS_CP_TYPE_INT16:
        return "int16";
    case MLS_CP_TYPE_INT32:
        return "int32";
    case MLS_CP_TYPE_INT64:
        return "int64";

    case MLS_CP_TYPE_STRING:
        return "string";
    case MLS_CP_TYPE_BYTES:
        return "byte_array";

        // case MLS_CP_TYPE_BYTE:         return "byte";

    case MLS_CP_TYPE_ARGB:
        return "argb";

    default:
        break;
    }
    return "unknown_type";
}

mls_string mls_cp_group_field_stringify(mls_cp_group_id group, mls_cp_field_id field)
{
    if (group == MLS_CP_GROUP_COMMON)
    {
        switch (field)
        {
        case MLS_CP_FIELD_COMMON_END_OF_PACK:
            return "MLS_CP_FIELD_COMMON_END_OF_PACK";
        case MLS_CP_FIELD_COMMON_VERSION:
            return "MLS_CP_FIELD_COMMON_VERSION";
        case MLS_CP_FIELD_COMMON_METHOD:
            return "MLS_CP_FIELD_COMMON_METHOD";
        case MLS_CP_FIELD_COMMON_LOCATION:
            return "MLS_CP_FIELD_COMMON_LOCATION";
        case MLS_CP_FIELD_COMMON_TRANSACTION_ID:
            return "MLS_CP_FIELD_COMMON_TRANSACTION_ID";
        case MLS_CP_FIELD_COMMON_STATUS_CODE:
            return "MLS_CP_FIELD_COMMON_STATUS_CODE";
        case MLS_CP_FIELD_COMMON_STATUS_MSG:
            return "MLS_CP_FIELD_COMMON_STATUS_MSG";
        case MLS_CP_FIELD_COMMON_TIMESTAMP:
            return "MLS_CP_FIELD_COMMON_TIMESTAMP";
        default:
            break;
        }
    }
    else if (group == MLS_CP_GROUP_EXAMPLE)
    {
        switch (field)
        {
        case MLS_CP_FIELD_EXAMPLE_FOO:
            return "MLS_CP_FIELD_EXAMPLE_FOO";
        case MLS_CP_FIELD_EXAMPLE_BAR:
            return "MLS_CP_FIELD_EXAMPLE_BAR";
        default:
            break;
        }
    }
    else if (group == MLS_CP_GROUP_TEST)
    {
    }

    return "unknown_field";
}

mls_string mls_cp_status_stringify(mls_cp_status_code code)
{
    switch (code)
    {
    case MLS_CP_STATUS_CONTINUE:
        return "CONTINUE";

    case MLS_CP_STATUS_OK:
        return "OK";
    case MLS_CP_STATUS_CREATED:
        return "CREATED";
    case MLS_CP_STATUS_ACCEPTED:
        return "ACCEPTED";

    case MLS_CP_STATUS_MULTIPLE_CHOICE:
        return "MULTIPLE_CHOICE";
    case MLS_CP_STATUS_MOVED_PERMANENTLY:
        return "MOVED_PERMANENTLY";
    case MLS_CP_STATUS_FOUND:
        return "FOUND";
    case MLS_CP_STATUS_SEE_OTHER:
        return "SEE_OTHER";
    case MLS_CP_STATUS_TEMPORARY_REDIRECT:
        return "TEMPORARY_REDIRECT";
    case MLS_CP_STATUS_PERMANENT_REDIRECT:
        return "PERMANENT_REDIRECT";

    case MLS_CP_STATUS_BAD_REQUEST:
        return "BAD_REQUEST";
    case MLS_CP_STATUS_UNAUTHORIZED:
        return "UNAUTHORIZED";
    case MLS_CP_STATUS_PAYMENT_REQUIRED:
        return "PAYMENT_REQUIRED";
    case MLS_CP_STATUS_FORBIDDEN:
        return "FORBIDDEN";
    case MLS_CP_STATUS_NOT_FOUND:
        return "NOT_FOUND";

    case MLS_CP_STATUS_INTERNAL_SERVER_ERROR:
        return "INTERNAL_SERVER_ERROR";
    case MLS_CP_STATUS_NOT_IMPLEMENTED:
        return "NOT_IMPLEMENTED";
    case MLS_CP_STATUS_BAD_GATEWAY:
        return "BAD_GATEWAY";
    case MLS_CP_STATUS_SERVICE_UNAVAILABLE:
        return "SERVICE_UNAVAILABLE";
    case MLS_CP_STATUS_GATEWAY_TIMEOUT:
        return "GATEWAY_TIMEOUT";
    case MLS_CP_STATUS_VERSION_NOT_SUPPORTED:
        return "VERSION_NOT_SUPPORTED";

    default:
        break;
    }
    return "UNKNOWN_STATUS_CODE";
}

/*******************************************************************************
 * EOF
 */
