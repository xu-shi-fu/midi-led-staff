// buffer.h

#ifndef __buffer_h__
#define __buffer_h__

#include "mls_common.h"
#include "mls_errors.h"

////////////////////////////////////////////////////////////////////////////////

// mls_buffer 表示缓冲区的头部
typedef struct
{
    size_t capacity;
    size_t length;
    bool overflow;

    uint8_t data[0];

} mls_buffer;

mls_buffer *mls_buffer_create(size_t capacity);
void mls_buffer_release(mls_buffer *buffer);
void mls_buffer_reset(mls_buffer *buffer);
void mls_buffer_write(mls_buffer *buffer, uint8_t *data, size_t len);
bool mls_buffer_is_overflow(mls_buffer *buffer);

////////////////////////////////////////////////////////////////////////////////

// mls_buffer_holder 结构用于管理缓冲区的分配/释放
typedef struct
{
    size_t capacity;
    mls_buffer *buffer;

} mls_buffer_holder;

void mls_buffer_holder_init(mls_buffer_holder *h, size_t capacity); // 第1步:初始化
void mls_buffer_holder_create(mls_buffer_holder *h);                // 第2步:创建
void mls_buffer_holder_release(mls_buffer_holder *h);               // 第3步:释放
bool mls_buffer_holder_ready(mls_buffer_holder *h);

////////////////////////////////////////////////////////////////////////////////

// mls_buffer_holder_auto 结构用于在作用域内自动分配/释放缓冲区
typedef struct
{
    mls_buffer_holder *holder;
    mls_buffer_holder *mine; // 如果缓冲区是由本对象创建的,则指向 holder; 否则为 NULL

} mls_buffer_holder_auto;

void mls_buffer_holder_auto_create(mls_buffer_holder_auto *a, mls_buffer_holder *holder);
void mls_buffer_holder_auto_release(mls_buffer_holder_auto *a);
bool mls_buffer_holder_auto_ready(mls_buffer_holder_auto *a);

////////////////////////////////////////////////////////////////////////////////

// mls_buffer_slice 指向实际缓冲区的一个片段
typedef struct
{

    mls_buffer *buffer;
    uint8_t *data;
    size_t length;

} mls_buffer_slice;

////////////////////////////////////////////////////////////////////////////////

#endif // __buffer_h__
