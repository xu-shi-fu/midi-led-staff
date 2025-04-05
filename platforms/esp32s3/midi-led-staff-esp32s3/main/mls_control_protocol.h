// control_protocol.h

#ifndef __control_protocol_h__
#define __control_protocol_h__

#include "mls_common.h"
#include "mls_errors.h"

/***
 * 基础类型
 */

typedef uint8_t mls_cp_block_size; // 注意:这个类型必须是 uint8
typedef uint8_t mls_cp_block_type; // 注意:这个类型必须是 uint8
typedef uint8_t mls_cp_group_id;   // 注意:这个类型必须是 uint8
typedef uint8_t mls_cp_field_id;   // 注意:这个类型必须是 uint8

struct mls_cp_tx_context_t;

/***
 * 函数指针
 */

typedef mls_error (*mls_cp_tx_func)(struct mls_cp_tx_context_t *);

/***
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
typedef struct
{
    mls_cp_block_head head;
    uint8_t body[0];

} mls_cp_block_entity;

// 对协议数据块开头的引用
typedef struct
{

    mls_cp_block_entity *block;

} mls_cp_block_ref;

// 对协议数据块开头的引用
typedef struct
{

    uint count; // 当前 buffer 中, 有效的 block 个数
    mls_cp_block_ref blocks[32];
    mls_cp_block_ref end; // 最后一块

} mls_cp_block_buffer;

// 数据接收上下文
typedef struct
{

    uint8_t *data;
    size_t length;
    size_t capacity;

    mls_cp_block_buffer *blocks;

} mls_cp_rx_context;

// 数据发送上下文
typedef struct mls_cp_tx_context_t
{

    uint8_t *data;
    size_t length;
    size_t capacity;

    mls_cp_block_buffer *blocks;

} mls_cp_tx_context;

// 数据收发上下文
typedef struct
{

    mls_cp_rx_context *rx;
    mls_cp_tx_context *tx;

    mls_cp_tx_func dispatcher;

} mls_cp_rtx_context;

// pack-parser
typedef struct
{

} mls_cp_pack_parser;

// pack-builder
typedef struct
{

} mls_cp_pack_builder;

/***
 * 函数
 */

void mls_cp_block_buffer_init(mls_cp_block_buffer *buffer);
void mls_cp_block_buffer_add_entity(mls_cp_block_buffer *buffer, mls_cp_block_entity *entity);
void mls_cp_block_buffer_add_ref(mls_cp_block_buffer *buffer, mls_cp_block_ref *ref);

void mls_cp_pack_parser_init(mls_cp_pack_parser *parser);
void mls_cp_pack_parser_parse(mls_cp_pack_parser *parser, uint8_t *data, size_t len);

void mls_cp_pack_builder_init(mls_cp_pack_builder *builder);
void mls_cp_pack_builder_add_uint8(mls_cp_pack_builder *builder, mls_cp_block_head *head, uint8_t value);
void mls_cp_pack_builder_add_uint16(mls_cp_pack_builder *builder, mls_cp_block_head *head, uint16_t value);
void mls_cp_pack_builder_add_uint32(mls_cp_pack_builder *builder, mls_cp_block_head *head, uint32_t value);
void mls_cp_pack_builder_add_uint64(mls_cp_pack_builder *builder, mls_cp_block_head *head, uint64_t value);
void mls_cp_pack_builder_add_bytes(mls_cp_pack_builder *builder, mls_cp_block_head *head, uint8_t *data, size_t len);
void mls_cp_pack_builder_add_string(mls_cp_pack_builder *builder, mls_cp_block_head *head, char *str);

mls_error mls_cp_handle_rx(mls_cp_rtx_context *ctx);

#endif // __control_protocol_h__
