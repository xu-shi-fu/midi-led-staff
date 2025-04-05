#include "mls_buffer.h"
#include <memory.h>

////////////////////////////////////////////////////////////////////////////////

mls_buffer *mls_buffer_create(size_t capacity)
{
    size_t len = sizeof(mls_buffer) + capacity;
    void *p = malloc(len);
    if (p == NULL)
    {
        return NULL;
    }
    mls_buffer *head = p;
    head->length = 0;
    head->capacity = capacity;
    return head;
}

void mls_buffer_release(mls_buffer *buffer)
{
    if (buffer == NULL)
    {
        return;
    }
    free(buffer);
}

////////////////////////////////////////////////////////////////////////////////

void mls_buffer_holder_init(mls_buffer_holder *holder, size_t capacity)
{
    if (holder == NULL)
    {
        return;
    }
    memset(holder, 0, sizeof(holder[0]));
    holder->capacity = capacity;
}

void mls_buffer_holder_create(mls_buffer_holder *holder)
{
    if (holder == NULL)
    {
        return;
    }
    if (holder->buffer)
    {
        return;
    }
    holder->buffer = mls_buffer_create(holder->capacity);
}

void mls_buffer_holder_release(mls_buffer_holder *holder)
{
    if (holder == NULL)
    {
        return;
    }
    if (holder->buffer)
    {
        mls_buffer_release(holder->buffer);
        holder->buffer = NULL;
    }
}

bool mls_buffer_holder_ready(mls_buffer_holder *h)
{
    if (h == NULL)
    {
        return false;
    }
    if (h->buffer == NULL)
    {
        return false;
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////

void mls_buffer_holder_auto_create(mls_buffer_holder_auto *a, mls_buffer_holder *holder)
{
    if (a == NULL || holder == NULL)
    {
        return;
    }
    a->mine = NULL;
    a->holder = NULL;
    if (holder->buffer)
    {
        return;
    }
    mls_buffer_holder_create(holder);
    a->mine = holder;
    a->holder = holder;
}

void mls_buffer_holder_auto_release(mls_buffer_holder_auto *a)
{
    if (a == NULL)
    {
        return;
    }
    if (a->mine)
    {
        mls_buffer_holder_release(a->mine);
        a->mine = NULL;
    }
}

bool mls_buffer_holder_auto_ready(mls_buffer_holder_auto *a)
{
    if (a == NULL)
    {
        return false;
    }
    if (a->holder == NULL)
    {
        return false;
    }
    if (a->holder->buffer == NULL)
    {
        return false;
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////
