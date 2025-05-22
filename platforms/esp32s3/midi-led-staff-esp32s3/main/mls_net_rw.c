// mls_net_rw.c

#include "mls_net_rw.h"

#include <netinet/in.h>

/*******************************************************************************
 * mls_net_reader
 */

/*******************************************************************************
 * mls_net_writer
 */

mls_buffer_writer *mls_net_writer_get_inner(mls_net_writer *writer);

mls_error mls_net_writer_init(mls_net_writer *writer, mls_buffer *buffer)
{
    mls_buffer_writer *inner = mls_net_writer_get_inner(writer);
    return mls_buffer_writer_init(inner, buffer);
}

mls_error mls_net_writer_error(mls_net_writer *writer)
{
    mls_error_holder *eh = &writer->writer.err_holder;
    return mls_error_holder_get_error(eh);
}

void mls_net_writer_reset(mls_net_writer *writer)
{
    mls_buffer_writer *inner = mls_net_writer_get_inner(writer);
    return mls_buffer_writer_reset(inner);
}

void mls_net_writer_flush(mls_net_writer *writer)
{
    mls_buffer_writer *inner = mls_net_writer_get_inner(writer);
    return mls_buffer_writer_flush(inner);
}

mls_buffer_writer *mls_net_writer_get_inner(mls_net_writer *writer)
{
    if (writer)
    {
        return &writer->writer;
    }
    return NULL;
}

void mls_net_writer_write_bool(mls_net_writer *writer, mls_bool n)
{
    char b = n;
    mls_buffer_writer *inner = mls_net_writer_get_inner(writer);
    mls_buffer_writer_write(inner, &b, sizeof(b));
}

void mls_net_writer_write_byte(mls_net_writer *writer, mls_byte n)
{
    mls_buffer_writer *inner = mls_net_writer_get_inner(writer);
    mls_buffer_writer_write(inner, &n, sizeof(n));
}

void mls_net_writer_write_bytes(mls_net_writer *writer, const mls_byte *data, size_t len)
{
    mls_buffer_writer *inner = mls_net_writer_get_inner(writer);
    mls_buffer_writer_write(inner, data, len);
}

void mls_net_writer_write_uint8(mls_net_writer *writer, mls_uint8 n)
{
    mls_buffer_writer *inner = mls_net_writer_get_inner(writer);
    mls_buffer_writer_write(inner, &n, sizeof(n));
}

void mls_net_writer_write_uint16(mls_net_writer *writer, mls_uint16 n)
{
    mls_uint16 n2 = htons(n);
    mls_buffer_writer *inner = mls_net_writer_get_inner(writer);
    mls_buffer_writer_write(inner, &n2, sizeof(n2));
}

void mls_net_writer_write_uint32(mls_net_writer *writer, mls_uint32 n)
{
    mls_uint32 n2 = htonl(n);
    mls_buffer_writer *inner = mls_net_writer_get_inner(writer);
    mls_buffer_writer_write(inner, &n2, sizeof(n2));
}

void mls_net_writer_write_uint64(mls_net_writer *writer, mls_uint64 n)
{
    mls_uint64 n2 = htonll(n);
    mls_buffer_writer *inner = mls_net_writer_get_inner(writer);
    mls_buffer_writer_write(inner, &n2, sizeof(n2));
}

void mls_net_writer_write_int8(mls_net_writer *writer, mls_int8 n)
{
    mls_buffer_writer *inner = mls_net_writer_get_inner(writer);
    mls_buffer_writer_write(inner, &n, sizeof(n));
}

void mls_net_writer_write_int16(mls_net_writer *writer, mls_int16 n)
{
    mls_uint16 n2 = htons(n);
    mls_buffer_writer *inner = mls_net_writer_get_inner(writer);
    mls_buffer_writer_write(inner, &n2, sizeof(n2));
}

void mls_net_writer_write_int32(mls_net_writer *writer, mls_int32 n)
{
    mls_uint32 n2 = htonl(n);
    mls_buffer_writer *inner = mls_net_writer_get_inner(writer);
    mls_buffer_writer_write(inner, &n2, sizeof(n2));
}

void mls_net_writer_write_int64(mls_net_writer *writer, mls_int64 n)
{
    mls_uint64 n2 = htonll(n);
    mls_buffer_writer *inner = mls_net_writer_get_inner(writer);
    mls_buffer_writer_write(inner, &n2, sizeof(n2));
}

/*******************************************************************************
 * EOF
 */
