// mls_cp_block.h

#ifndef __mls_cp_block_h__
#define __mls_cp_block_h__

#include "mls_api.h"
#include "mls_common_std.h"
#include "mls_buffer.h"
#include "mls_errors.h"
#include "mls_cp_base.h"
#include "mls_net_rw.h"

struct mls_cp_block_array_holder_t;

/*******************************************************************************
 * 结构
 */

// 协议数据块的开头
typedef struct mls_cp_block_head_t
{

    mls_cp_block_size size; // 数据块的大小 = sizeof(head) + sizeof(body)
    mls_cp_block_type type;
    mls_cp_group_id group;
    mls_cp_field_id field;

} mls_cp_block_head;

// 协议数据块的实体
typedef struct mls_cp_block_t
{
    mls_cp_block_head head;

    uint8_t body[0];

} mls_cp_block;

// mls-cp 数据块读取器
typedef struct mls_cp_block_reader_t
{

    mls_net_reader reader;

} mls_cp_block_reader;

// mls-cp 数据块写入器
typedef struct mls_cp_block_writer_t
{

    mls_net_writer writer;

} mls_cp_block_writer;

/*******************************************************************************
 * block-array
 */

// 对协议数据块开头的引用
typedef struct mls_cp_block_array_item_t
{

    mls_cp_block *block;

} mls_cp_block_array_item;

typedef struct mls_cp_block_array_entity_t
{

    mls_uint capacity;
    struct mls_cp_block_array_holder_t *owner;

    mls_cp_block_array_item items[0];

} mls_cp_block_array_entity;

// mls_cp_block_array 是一个表示 cp_block 数组的结构,
// 这个结构包含以下直接的成员:
// - count: 数组中包含的 block 个数;
// - capacity: 数组的容量;
// - overflow: 是否发生了溢出;
// - entity: 提供数组的实体结构;
// - blocks: 指向数组的开头;
typedef struct mls_cp_block_array_t
{

    mls_uint count;    // 当前 buffer 中, 有效的 block 个数
    mls_uint capacity; // 当前 buffer 中, 最大的 block 个数
    mls_bool overflow;

    mls_cp_block_array_entity *entity;
    mls_cp_block_array_item *items; // -> entity.blocks

} mls_cp_block_array;

// array of blocks
typedef struct mls_cp_block_array_holder_t
{

    mls_cp_block_array *array;

} mls_cp_block_array_holder;

/*******************************************************************************
 * functions
 */

// block-array-entity

mls_cp_block_array_entity *mls_cp_block_array_entity_create(mls_uint capacity);
void mls_cp_block_array_entity_release(mls_cp_block_array_entity *entity);

// block-array

void mls_cp_block_array_init(mls_cp_block_array *buffer);
mls_error mls_cp_block_array_create(mls_cp_block_array *buffer, mls_uint capacity);
void mls_cp_block_array_reset(mls_cp_block_array *buffer);
mls_bool mls_cp_block_array_is_overflow(mls_cp_block_array *buffer);

void mls_cp_block_array_add_block(mls_cp_block_array *buffer, mls_cp_block *block);
void mls_cp_block_array_add_item(mls_cp_block_array *buffer, mls_cp_block_array_item *item);

// block-array-holder

void mls_cp_block_array_holder_init(mls_cp_block_array_holder *holder, mls_cp_block_array *array);
mls_error mls_cp_block_array_holder_create(mls_cp_block_array_holder *holder, mls_uint capacity);
void mls_cp_block_array_holder_release(mls_cp_block_array_holder *holder);

/**************************************
 * mls_cp_block_reader
 * */

mls_error mls_cp_block_reader_init(mls_cp_block_reader *reader, mls_buffer *buffer);
mls_error mls_cp_block_reader_error(mls_cp_block_reader *reader);

/**************************************
 * mls_cp_block_head
 * */

mls_cp_block_head *mls_cp_block_head_set_field(mls_cp_block_head *head, mls_cp_field_id field);

/**************************************
 * mls_cp_block_writer
 * */

mls_error mls_cp_block_writer_init(mls_cp_block_writer *writer, mls_buffer *buffer);
mls_error mls_cp_block_writer_error(mls_cp_block_writer *writer);
void mls_cp_block_writer_flush(mls_cp_block_writer *writer);
void mls_cp_block_writer_reset(mls_cp_block_writer *writer);

void mls_cp_block_writer_write_block(mls_cp_block_writer *writer, mls_cp_block_head *head, const void *body_data, size_t body_len);
void mls_cp_block_writer_write_block_head(mls_cp_block_writer *writer, mls_cp_block_head *head);

void mls_cp_block_writer_write_byte(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_byte b);
void mls_cp_block_writer_write_bytes(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_byte *data_ptr, size_t data_len);
void mls_cp_block_writer_write_string(mls_cp_block_writer *writer, mls_cp_block_head *head, const char *str);

void mls_cp_block_writer_write_uint8(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_uint8 n);
void mls_cp_block_writer_write_uint16(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_uint16 n);
void mls_cp_block_writer_write_uint32(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_uint32 n);
void mls_cp_block_writer_write_uint64(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_uint64 n);

void mls_cp_block_writer_write_int8(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_int8 n);
void mls_cp_block_writer_write_int16(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_int16 n);
void mls_cp_block_writer_write_int32(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_int32 n);
void mls_cp_block_writer_write_int64(mls_cp_block_writer *writer, mls_cp_block_head *head, mls_int64 n);

#endif // __mls_cp_block_h__
