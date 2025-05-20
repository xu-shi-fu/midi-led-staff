// mls_cp_block.h

#ifndef __mls_cp_block_h__
#define __mls_cp_block_h__

#include "mls_api.h"
#include "mls_common_std.h"
#include "mls_buffer.h"
#include "mls_errors.h"
#include "mls_cp_base.h"

struct mls_cp_block_array_holder_t;

/*******************************************************************************
 * 结构
 */

// 协议数据块的开头
typedef struct mls_cp_block_head_t
{

    mls_cp_block_size size;
    mls_cp_block_type type;
    mls_cp_group_id group;
    mls_cp_field_id field;

} mls_cp_block_head;

// 协议数据块的实体
typedef struct mls_cp_block_entity_t
{
    mls_cp_block_head head;

    uint8_t body[0];

} mls_cp_block_entity;

// 对协议数据块开头的引用
typedef struct mls_cp_block_ref_t
{

    mls_cp_block_entity *block;

} mls_cp_block_ref;

/*******************************************************************************
 * block-array
 */

typedef struct mls_cp_block_array_entity_t
{

    mls_uint capacity;
    struct mls_cp_block_array_holder_t *owner;

    mls_cp_block_ref blocks[0];

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
    mls_cp_block_ref *blocks; // -> entity.blocks

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

void mls_cp_block_array_add_entity(mls_cp_block_array *buffer, mls_cp_block_entity *entity);
void mls_cp_block_array_add_ref(mls_cp_block_array *buffer, mls_cp_block_ref *ref);

// block-array-holder

void mls_cp_block_array_holder_init(mls_cp_block_array_holder *holder, mls_cp_block_array *array);
mls_error mls_cp_block_array_holder_create(mls_cp_block_array_holder *holder, mls_uint capacity);
void mls_cp_block_array_holder_release(mls_cp_block_array_holder *holder);

#endif // __mls_cp_block_h__
