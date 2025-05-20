#include "mls_buffer.h"
#include <memory.h>

////////////////////////////////////////////////////////////////////////////////
// mls_buffer_entity::

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
// mls_buffer::

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

////////////////////////////////////////////////////////////////////////////////
// mls_buffer_holder::

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
// mls_buffer_slice::

void mls_buffer_slice_init(mls_buffer_slice *slice, mls_buffer *buffer)
{
    if (slice && buffer)
    {
        memset(slice, 0, sizeof(slice[0]));
        slice->buffer = buffer;
        slice->data = buffer->data;
        slice->length = buffer->size;
    }
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
