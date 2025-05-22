#include "mls_buffer.h"
#include <memory.h>

////////////////////////////////////////////////////////////////////////////////
// mls_buffer_entity

mls_buffer_entity *mls_buffer_entity_create(size_t capacity)
{
    size_t len = sizeof(mls_buffer_entity) + capacity;
    void *p = malloc(len);
    mls_buffer_entity *head = NULL;
    if (p)
    {
        memset(p, 0, len);
        head = p;
        head->capacity = capacity;
    }
    return head;
}

void mls_buffer_entity_release(mls_buffer_entity *ent)
{
    if (ent)
    {
        free(ent);
    }
}

////////////////////////////////////////////////////////////////////////////////
// mls_buffer

void mls_buffer_init(mls_buffer *buffer)
{
    if (buffer)
    {
        memset(buffer, 0, sizeof(buffer[0]));
    }
}

mls_error mls_buffer_create(mls_buffer *buffer)
{
    if (buffer == NULL)
    {
        return mls_errors_make(500, "byte buffer is nil");
    }
    if (buffer->entity)
    {
        return NULL;
    }

    mls_buffer_entity *ent = mls_buffer_entity_create(buffer->capacity);
    if (ent == NULL)
    {
        return mls_errors_make(500, "create a nil buffer entity");
    }

    buffer->size = 0;
    buffer->entity = ent;
    buffer->data = ent->data;
    buffer->capacity = ent->capacity;
    return NULL;
}

void mls_buffer_release(mls_buffer *buffer)
{
    if (buffer)
    {
        if (buffer->entity)
        {
            mls_buffer_entity_release(buffer->entity);
            buffer->entity = NULL;
            buffer->data = NULL;
            buffer->size = 0;
        }
    }
}

mls_bool mls_buffer_is_ready(mls_buffer *buffer)
{
    if (buffer)
    {
        if (buffer->entity)
        {
            return YES;
        }
    }
    return NO;
}

void mls_buffer_reset(mls_buffer *buffer)
{
    if (buffer == NULL)
    {
        return;
    }
    mls_buffer_entity *ent = buffer->entity;
    if (ent)
    {
        buffer->capacity = ent->capacity;
        buffer->size = 0;
        buffer->data = ent->data;
        buffer->entity = ent;
    }
    else
    {
        // buffer->capacity = ent->capacity;
        buffer->size = 0;
        buffer->data = NULL;
        buffer->entity = NULL;
    }
}

////////////////////////////////////////////////////////////////////////////////
// mls_buffer_holder

void mls_buffer_holder_init(mls_buffer_holder *h, mls_buffer *buf)
{
    if (h)
    {
        memset(h, 0, sizeof(h[0]));
        h->buffer = buf;
    }
}

mls_error mls_buffer_holder_create(mls_buffer_holder *h, size_t capacity)
{
    if (h == NULL)
    {
        return mls_errors_make(500, "mls_buffer_holder is nil");
    }

    if (h->buffer == NULL)
    {
        return mls_errors_make(500, "mls_buffer_holder.buffer is nil");
    }

    if (h->buffer->entity)
    {
        return NULL; // entity is existed
    }

    mls_error err = mls_buffer_create(h->buffer);
    if (err)
    {
        return err;
    }
    if (h->buffer->entity == NULL)
    {
        return mls_errors_make(500, "make byte-buffer-entity result nil");
    }

    h->buffer->entity->owner = h;
    return NULL;
}

void mls_buffer_holder_release(mls_buffer_holder *h)
{
    if (h)
    {
        if (h->buffer)
        {
            if (h->buffer->entity)
            {
                if (h->buffer->entity->owner == h)
                {
                    mls_buffer_release(h->buffer);
                }
            }
        }
    }
}

mls_bool mls_buffer_holder_is_ready(mls_buffer_holder *h)
{
    if (h)
    {
        if (h->buffer)
        {
            if (h->buffer->entity)
            {
                return YES;
            }
        }
    }
    return NO;
}

////////////////////////////////////////////////////////////////////////////////
// mls_buffer_slice

mls_error mls_buffer_slice_init(mls_buffer_slice *slice, mls_buffer *buffer)
{
    if (slice && buffer)
    {
        memset(slice, 0, sizeof(slice[0]));
        slice->buffer = buffer;
        slice->data = buffer->data;
        slice->length = buffer->size;
        return NULL;
    }
    return mls_errors_make(500, "mls_buffer_slice is nil");
}

void mls_buffer_slice_reset(mls_buffer_slice *slice)
{
    if (slice)
    {
        mls_buffer *buffer = slice->buffer;
        if (buffer)
        {
            slice->data = buffer->data;
            slice->length = buffer->size;
        }
        else
        {
            slice->data = NULL;
            slice->length = 0;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// mls_buffer_writer

mls_bool mls_buffer_writer_has_space_for_data(mls_buffer_writer *writer, size_t data_len);

mls_error mls_buffer_writer_init(mls_buffer_writer *writer, mls_buffer *buffer)
{
    if (writer == NULL)
    {
        return mls_errors_make(500, "mls_buffer_writer is nil");
    }
    if (buffer == NULL)
    {
        return mls_errors_make(500, "mls_buffer is nil");
    }

    memset(writer, 0, sizeof(writer[0]));

    mls_buffer_slice *slice = &writer->slice;
    mls_error err = mls_buffer_slice_init(slice, buffer);
    if (err)
    {
        return err;
    }

    writer->overflow = NO;
    slice->length = 0;
    slice->data = buffer->data;
    slice->buffer = buffer;

    return NULL;
}

mls_error mls_buffer_writer_get_error(mls_buffer_writer *writer)
{
    if (writer == NULL)
    {
        return NULL;
    }
    return mls_error_holder_get_error(&writer->err_holder);
}

mls_bool mls_buffer_writer_has_error(mls_buffer_writer *writer)
{
    if (writer == NULL)
    {
        return NO;
    }
    return mls_error_holder_has_error(&writer->err_holder);
}

mls_error mls_buffer_writer_write(mls_buffer_writer *writer, const void *data, size_t len)
{
    if (writer == NULL)
    {
        return mls_errors_make(500, "mls_buffer_writer is nil");
    }

    if (data == NULL)
    {
        return mls_errors_make(500, "data is nil");
    }

    if (!mls_buffer_writer_has_space_for_data(writer, len))
    {
        mls_error err = mls_errors_make(500, "buffer overflow");
        mls_error_holder_push(&writer->err_holder, err);
        writer->overflow = YES;
        return err;
    }

    const void *data_src = data;
    void *data_dst = writer->slice.data + writer->slice.length;
    memcpy(data_dst, data_src, len);
    writer->slice.length += len;
    return NULL;
}

mls_bool mls_buffer_writer_has_space_for_data(mls_buffer_writer *writer, size_t data_len)
{
    if (writer == NULL)
    {
        return NO;
    }

    mls_buffer_slice *slice = &writer->slice;
    mls_buffer *buffer = slice->buffer;
    if (buffer == NULL)
    {
        return NO;
    }

    mls_buffer_entity *entity = buffer->entity;
    if (buffer->data == NULL || entity == NULL)
    {
        return NO;
    }

    mls_byte *p0 = entity->data;
    mls_byte *p1 = slice->data;
    mls_byte *p2 = slice->data + slice->length;
    mls_byte *p2n = p2 + data_len;
    mls_byte *p3 = entity->data + entity->capacity;

    mls_bool b1 = p0 <= p1;
    mls_bool b2 = p1 <= p2;
    mls_bool b3 = p2 <= p2n;
    mls_bool b4 = p2n <= p3;

    return (b1 && b2 && b3 && b4);
}

void mls_buffer_writer_flush(mls_buffer_writer *writer)
{
    if (writer == NULL)
    {
        return;
    }
    mls_buffer_slice *slice = &writer->slice;
    mls_buffer *buffer = slice->buffer;
    if (buffer == NULL)
    {
        return;
    }
    buffer->size = slice->length;
}

void mls_buffer_writer_reset(mls_buffer_writer *writer)
{
    if (writer == NULL)
    {
        return;
    }
    mls_buffer_slice *slice = &writer->slice;
    mls_buffer *buffer = slice->buffer;
    mls_error_holder *eh = &writer->err_holder;
    if (buffer)
    {
        mls_buffer_reset(buffer);
        slice->data = buffer->data;
    }
    writer->overflow = NO;
    slice->length = 0;
    mls_error_holder_reset(eh);
}

mls_bool mls_buffer_writer_is_overflow(mls_buffer_writer *writer)
{
    if (writer)
    {
        return writer->overflow;
    }
    return NO;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
