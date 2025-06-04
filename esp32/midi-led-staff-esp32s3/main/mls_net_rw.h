// mls_net_rw.h

#ifndef __mls_net_rw_h__
#define __mls_net_rw_h__

#include "mls_common_mls.h"
#include "mls_buffer.h"

////////////////////////////////////////////////////////////////////////////////

#if __BIG_ENDIAN__
#define htonll(x) (x)
#define ntohll(x) (x)
#else
#define htonll(x) (((uint64_t)htonl((x) & 0xFFFFFFFF) << 32) | htonl((x) >> 32))
#define ntohll(x) (((uint64_t)ntohl((x) & 0xFFFFFFFF) << 32) | ntohl((x) >> 32))
#endif

////////////////////////////////////////////////////////////////////////////////

// mls_net_reader 用于按照网络字节序读取数据
typedef struct mls_net_reader_t
{

    mls_buffer_reader reader;

} mls_net_reader;

// mls_net_writer 用于按照网络字节序写入数据
typedef struct mls_net_writer_t
{

    mls_buffer_writer writer;

} mls_net_writer;

////////////////////////////////////////////////////////////////////////////////

// mls_net_reader

mls_error mls_net_reader_init(mls_net_reader *reader, mls_buffer *buffer);
mls_error mls_net_reader_error(mls_net_reader *reader);
void mls_net_reader_reset(mls_net_reader *reader);

// mls_net_writer

mls_error mls_net_writer_init(mls_net_writer *writer, mls_buffer *buffer);
mls_error mls_net_writer_error(mls_net_writer *writer);
void mls_net_writer_reset(mls_net_writer *writer);
void mls_net_writer_flush(mls_net_writer *writer);

void mls_net_writer_write_bool(mls_net_writer *writer, mls_bool n);
void mls_net_writer_write_byte(mls_net_writer *writer, mls_byte n);
void mls_net_writer_write_bytes(mls_net_writer *writer, const mls_byte *data, size_t len);
void mls_net_writer_write_uint8(mls_net_writer *writer, mls_uint8 n);
void mls_net_writer_write_uint16(mls_net_writer *writer, mls_uint16 n);
void mls_net_writer_write_uint32(mls_net_writer *writer, mls_uint32 n);
void mls_net_writer_write_uint64(mls_net_writer *writer, mls_uint64 n);
void mls_net_writer_write_int8(mls_net_writer *writer, mls_int8 n);
void mls_net_writer_write_int16(mls_net_writer *writer, mls_int16 n);
void mls_net_writer_write_int32(mls_net_writer *writer, mls_int32 n);
void mls_net_writer_write_int64(mls_net_writer *writer, mls_int64 n);

#endif // __mls_net_rw_h__
