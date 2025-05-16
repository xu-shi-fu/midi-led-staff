// control_protocol.h

#ifndef __control_protocol_h__
#define __control_protocol_h__

#include "mls_common.h"
#include "mls_errors.h"
#include "mls_tasks.h"
#include "mls_buffer.h"
#include "mls_cp_base.h"
#include "mls_cp_block.h"

struct mls_cp_tx_context_t;
struct mls_cp_pack_parser_t;
struct mls_cp_block_entity_t;

/*******************************************************************************
 * 函数指针
 */

typedef mls_error (*mls_cp_parser_callback_func)(struct mls_cp_pack_parser_t *, struct mls_cp_block_entity_t *block);

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
    mls_buffer_holder *buffer;
    mls_buffer_writer *writer;

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
