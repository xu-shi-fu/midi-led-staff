// control_protocol.h

#ifndef __control_protocol_h__
#define __control_protocol_h__

#include "mls_common.h"
#include "mls_errors.h"
#include "mls_tasks.h"
#include "mls_buffer.h"

/*******************************************************************************
 * 宏
 */

// types

#define MLS_CP_TYPE_NO_VALUE 0

#define MLS_CP_TYPE_UINT8 0x01
#define MLS_CP_TYPE_UINT16 0x02
#define MLS_CP_TYPE_UINT32 0x03
#define MLS_CP_TYPE_UINT64 0x04

#define MLS_CP_TYPE_INT8 0x11
#define MLS_CP_TYPE_INT16 0x12
#define MLS_CP_TYPE_INT32 0x13
#define MLS_CP_TYPE_INT64 0x14

#define MLS_CP_TYPE_FLOAT 0x21
#define MLS_CP_TYPE_DOUBLE 0x22

#define MLS_CP_TYPE_BOOL 0x31
#define MLS_CP_TYPE_STRING 0x32
#define MLS_CP_TYPE_BYTES 0x33

#define MLS_CP_TYPE_ARGB 0x41

// groups

#define MLS_CP_GROUP_COMMON 0
#define MLS_CP_GROUP_SYSTEM 1
#define MLS_CP_GROUP_MIDI 2
#define MLS_CP_GROUP_LED 3

// fields:COMMON

#define MLS_CP_FIELD_COMMON_END_OF_PACK 0
#define MLS_CP_FIELD_COMMON_METHOD 1
#define MLS_CP_FIELD_COMMON_ACTION 2

/*******************************************************************************
 * 基础类型
 */

typedef uint8_t mls_cp_block_size; // 注意:这个类型必须是 uint8
typedef uint8_t mls_cp_block_type; // 注意:这个类型必须是 uint8
typedef uint8_t mls_cp_group_id;   // 注意:这个类型必须是 uint8
typedef uint8_t mls_cp_field_id;   // 注意:这个类型必须是 uint8

struct mls_cp_tx_context_t;

struct mls_cp_pack_parser_t;

struct mls_cp_block_entity_t;

/*******************************************************************************
 * 函数指针
 */

typedef mls_error (*mls_cp_parser_callback_func)(struct mls_cp_pack_parser_t *, struct mls_cp_block_entity_t *block);

/*******************************************************************************
 * 结构
 */

// 协议数据块的开头
typedef struct
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
typedef struct
{

    mls_cp_block_entity *block;

} mls_cp_block_ref;

/*******************************************************************************
 * array
 */

// array of blocks
typedef struct
{

    uint count;    // 当前 buffer 中, 有效的 block 个数
    uint capacity; // 当前 buffer 中, 最大的 block 个数
    bool overflow;

    mls_cp_block_ref *blocks; // blocks [n]

} mls_cp_block_array;

void mls_cp_block_array_init(mls_cp_block_array *buffer);
mls_error mls_cp_block_array_create(mls_cp_block_array *buffer, uint size);
void mls_cp_block_array_reset(mls_cp_block_array *buffer);
bool mls_cp_block_array_is_overflow(mls_cp_block_array *buffer);

void mls_cp_block_array_add_entity(mls_cp_block_array *buffer, mls_cp_block_entity *entity);
void mls_cp_block_array_add_ref(mls_cp_block_array *buffer, mls_cp_block_ref *ref);

/*******************************************************************************
 * parser
 */

// pack-parser
typedef struct mls_cp_pack_parser_t
{

    void *params; // user defined data
    mls_cp_parser_callback_func callback;

} mls_cp_pack_parser;

void mls_cp_pack_parser_init(mls_cp_pack_parser *parser);
mls_error mls_cp_pack_parser_parse(mls_cp_pack_parser *parser, uint8_t *data, size_t len);

/*******************************************************************************
 *  builder
 */

// pack-builder
typedef struct
{

    mls_cp_block_array *blocks;
    mls_buffer *buffer;

} mls_cp_pack_builder;

void mls_cp_pack_builder_init(mls_cp_pack_builder *builder);
void mls_cp_pack_builder_reset(mls_cp_pack_builder *builder);
bool mls_cp_pack_builder_is_overflow(mls_cp_pack_builder *builder);

void mls_cp_pack_builder_add_uint8(mls_cp_pack_builder *builder, mls_cp_block_head *head, uint8_t value);
void mls_cp_pack_builder_add_uint16(mls_cp_pack_builder *builder, mls_cp_block_head *head, uint16_t value);
void mls_cp_pack_builder_add_uint32(mls_cp_pack_builder *builder, mls_cp_block_head *head, uint32_t value);
void mls_cp_pack_builder_add_uint64(mls_cp_pack_builder *builder, mls_cp_block_head *head, uint64_t value);
void mls_cp_pack_builder_add_bytes(mls_cp_pack_builder *builder, mls_cp_block_head *head, uint8_t *data, size_t len);
void mls_cp_pack_builder_add_string(mls_cp_pack_builder *builder, mls_cp_block_head *head, char *str);

/*******************************************************************************
 *  EOF
 */

#endif // __control_protocol_h__
