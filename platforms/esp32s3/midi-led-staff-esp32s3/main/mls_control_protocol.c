// mls_control_protocol.c

#include "mls_control_protocol.h"

mls_error mls_cp_handle_rx(mls_cp_rtx_context *ctx)
{
    return NULL;
}

/*******************************************************************************
 * mls_cp_block_buffer
 */

void mls_cp_block_buffer_init(mls_cp_block_buffer *buffer)
{
    if (buffer)
    {
        memset(buffer, 0, sizeof(buffer[0]));
    }
}

void mls_cp_block_buffer_add_entity(mls_cp_block_buffer *buffer, mls_cp_block_entity *entity)
{
    if (buffer == NULL || entity == NULL)
    {
        return;
    }
    uint count = buffer->count;
    mls_cp_block_ref *current = buffer->blocks + count;
    mls_cp_block_ref *end = &buffer->end;
    mls_cp_block_ref r1;
    if (current < end)
    {
        r1.block = entity;
        *current = r1;
        buffer->count = count + 1;
    }
}

void mls_cp_block_buffer_add_ref(mls_cp_block_buffer *buffer, mls_cp_block_ref *ref)
{
    if (ref)
    {
        mls_cp_block_buffer_add_entity(buffer, ref->block);
    }
}

/*******************************************************************************
 * mls_cp_pack_builder
 */

/*******************************************************************************
 * mls_cp_pack_parser
 */

/*******************************************************************************
 * EOF
 */
