// mls_cp_request.h

#ifndef __mls_cp_request_h__
#define __mls_cp_request_h__

#include "mls_common_mls.h"
#include "mls_api.h"
#include "mls_buffer.h"
#include "mls_cp_base.h"
#include "mls_cp_address.h"

/*******************************************************************************
 *  request
 */

typedef struct mls_cp_request_t
{
    struct mls_cp_context_t *context;

    // transaction: in context

    mls_cp_address remote;
    mls_cp_method method;
    mls_cp_location location;
    mls_cp_version version;
    mls_timestamp timestamp;

    mls_buffer *buffer;
    mls_cp_block_array *blocks;

} mls_cp_request;

/*******************************************************************************
 *  request-builder
 */

typedef struct mls_cp_request_builder_t
{

    mls_cp_method method;
    mls_cp_location location;
    mls_cp_transaction_id transaction;
    mls_cp_version version;

    mls_cp_block_writer writer;

} mls_cp_request_builder;

mls_error mls_cp_request_builder_init(mls_cp_request_builder *inst, mls_buffer *buffer);
mls_buffer_slice mls_cp_request_builder_build(mls_cp_request_builder *inst);
mls_cp_block_writer *mls_cp_request_builder_get_writer(mls_cp_request_builder *inst);

mls_error mls_cp_request_builder_get_error(mls_cp_request_builder *inst);
mls_bool mls_cp_request_builder_has_error(mls_cp_request_builder *inst);

void mls_cp_request_builder_add_byte(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_byte value);
void mls_cp_request_builder_add_bytes(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_byte *data, size_t len);
void mls_cp_request_builder_add_string(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_string value);
void mls_cp_request_builder_add_argb(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_argb value);

void mls_cp_request_builder_add_int8(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_int8 value);
void mls_cp_request_builder_add_int16(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_int16 value);
void mls_cp_request_builder_add_int32(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_int32 value);
void mls_cp_request_builder_add_int64(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_int64 value);

void mls_cp_request_builder_add_uint8(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_uint8 value);
void mls_cp_request_builder_add_uint16(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_uint16 value);
void mls_cp_request_builder_add_uint32(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_uint32 value);
void mls_cp_request_builder_add_uint64(mls_cp_request_builder *inst, mls_cp_group_id group, mls_cp_field_id field, mls_uint64 value);

#endif // __mls_cp_request_h__
