// buffer.h

#ifndef __buffer_h__
#define __buffer_h__

#include "mls_common_mls.h"
#include "mls_errors.h"

struct mls_buffer_x_t;
struct mls_buffer_entity_t;
struct mls_buffer_holder_t;
struct mls_buffer_reader_t;
struct mls_buffer_writer_t;

////////////////////////////////////////////////////////////////////////////////

// mls_buffer_entity 表示缓冲区的实体 (头部)
typedef struct mls_buffer_entity_t
{
    size_t capacity;
    struct mls_buffer_holder_t *owner;

    uint8_t data[0];

} mls_buffer_entity;

// mls_buffer 表示缓冲区
typedef struct mls_buffer_x_t
{
    size_t capacity;
    size_t size;

    uint8_t *data;
    mls_buffer_entity *entity;

} mls_buffer_x; // 暂时命名为"mls_buffer_x",

// mls_buffer_holder 结构用于管理缓冲区的分配/释放
typedef struct mls_buffer_holder_t
{
    mls_buffer_x *buffer;

} mls_buffer_holder;

// mls_buffer_slice 表示指向实际缓冲区的一个片段, 
// 这个结构包含以下成员:
// - buffer: 指向数据缓冲区;
// - data: 指向片段的开头;
// - length: 片段的长度;
typedef struct mls_buffer_slice_t
{

    mls_buffer_x *buffer;
    uint8_t *data;
    size_t length;

} mls_buffer_slice;

// mls_buffer_reader 用于从缓冲区读取数据
typedef struct mls_buffer_reader_t
{

    mls_buffer_slice slice;

    uint8_t *ptr;

} mls_buffer_reader;

// mls_buffer_writer 用于向缓冲区写入数据
typedef struct mls_buffer_writer_t
{

    mls_buffer_slice slice;

    uint8_t *ptr;
    bool overflow;
    mls_error_holder err_holder;

} mls_buffer_writer;

////////////////////////////////////////////////////////////////////////////////
// mls_buffer_entity

mls_buffer_entity *mls_buffer_entity_create(size_t capacity);
void mls_buffer_entity_release(mls_buffer_entity *entity);

////////////////////////////////////////////////////////////////////////////////
// mls_buffer_(x)

void mls_buffer_init(mls_buffer_x *buffer);
mls_error mls_buffer_create(mls_buffer_x *buffer);
void mls_buffer_release(mls_buffer_x *buffer);
bool mls_buffer_is_ready(mls_buffer_x *buffer);

////////////////////////////////////////////////////////////////////////////////
// mls_buffer_holder

void mls_buffer_holder_init(mls_buffer_holder *h, mls_buffer_x *buf);      // 第1步:初始化
mls_error mls_buffer_holder_create(mls_buffer_holder *h, size_t capacity); // 第2步:创建
void mls_buffer_holder_release(mls_buffer_holder *h);                      // 第3步:释放
bool mls_buffer_holder_is_ready(mls_buffer_holder *h);

////////////////////////////////////////////////////////////////////////////////
// mls_buffer_slice

void mls_buffer_slice_init(mls_buffer_slice *slice, mls_buffer_x *buffer);

////////////////////////////////////////////////////////////////////////////////
// mls_buffer_reader

void mls_buffer_reader_init(mls_buffer_reader *reader, mls_buffer_x *buffer);
size_t mls_buffer_reader_read(mls_buffer_reader *reader, uint8_t *dst, size_t len);

////////////////////////////////////////////////////////////////////////////////
// mls_buffer_writer

void mls_buffer_writer_init(mls_buffer_writer *writer, mls_buffer_x *buffer);
size_t mls_buffer_writer_write(mls_buffer_writer *writer, uint8_t *data, size_t len);
void mls_buffer_writer_reset(mls_buffer_writer *writer);
bool mls_buffer_writer_is_overflow(mls_buffer_writer *writer);

////////////////////////////////////////////////////////////////////////////////

#endif // __buffer_h__
