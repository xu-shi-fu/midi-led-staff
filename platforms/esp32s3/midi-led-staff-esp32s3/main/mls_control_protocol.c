// mls_control_protocol.c

#include "mls_control_protocol.h"
#include "mls_tasks.h"
#include "mls_common.h"

#include <netinet/in.h>

/*******************************************************************************
 * mls_cp_pack_builder
 */

void mls_cp_pack_builder_init(mls_cp_pack_builder *builder)
{
    if (builder)
    {
        memset(builder, 0, sizeof(builder[0]));
    }
}

void mls_cp_pack_builder_reset(mls_cp_pack_builder *builder)
{
    if (builder)
    {
        mls_cp_block_array_reset(builder->blocks);
        mls_buffer_writer_reset(builder->writer);
    }
}

mls_bool mls_cp_pack_builder_is_overflow(mls_cp_pack_builder *builder)
{
    if (builder)
    {
        if (mls_cp_block_array_is_overflow(builder->blocks))
        {
            return YES;
        }
        if (mls_buffer_writer_is_overflow(builder->writer))
        {
            return YES;
        }
    }
    return NO;
}

void mls_cp_pack_builder_add_uint8(mls_cp_pack_builder *builder, mls_cp_block_head *head, uint8_t value) {}
void mls_cp_pack_builder_add_uint16(mls_cp_pack_builder *builder, mls_cp_block_head *head, uint16_t value) {}
void mls_cp_pack_builder_add_uint32(mls_cp_pack_builder *builder, mls_cp_block_head *head, uint32_t value) {}
void mls_cp_pack_builder_add_uint64(mls_cp_pack_builder *builder, mls_cp_block_head *head, uint64_t value) {}
void mls_cp_pack_builder_add_bytes(mls_cp_pack_builder *builder, mls_cp_block_head *head, uint8_t *data, size_t len) {}
void mls_cp_pack_builder_add_string(mls_cp_pack_builder *builder, mls_cp_block_head *head, char *str) {}

/*******************************************************************************
 * mls_cp_checksum
 */

mls_buffer_slice *mls_cp_checksum_get_slice(mls_cp_checksum *inst);

void mls_cp_checksum_init(mls_cp_checksum *inst, mls_buffer_slice *target)
{
    if (inst)
    {
        memset(inst, 0, sizeof(inst[0]));
        if (target)
        {
            inst->slice = *target;
        }
    }
}

// 获取安全可用的 slice
mls_buffer_slice *mls_cp_checksum_get_slice(mls_cp_checksum *inst)
{
    if (inst == NULL)
    {
        return NULL;
    }
    mls_buffer_slice *slice = &inst->slice;
    if (slice)
    {
        const size_t min_len = 5; // sizeof(head)+sizeof(uint8)
        void *buffer = slice->buffer;
        size_t len = slice->length;
        if ((buffer == NULL) || (len < min_len))
        {
            return NULL;
        }
    }
    return slice;
}

void mls_cp_checksum_make(mls_cp_checksum *inst)
{
    mls_buffer_slice *slice = mls_cp_checksum_get_slice(inst);
    if (slice == NULL)
    {
        return;
    }

    size_t len = slice->length;
    mls_byte *buffer = slice->data;
    mls_byte *end = buffer + (len - 1);

    end[0] = 0;
    mls_byte sum1 = mls_cp_checksum_compute(inst);
    end[0] = sum1;
    mls_byte sum2 = mls_cp_checksum_compute(inst);

    ESP_LOGI(TAG, "mls_cp_checksum_make: sum1=%d, sum2=%d, len=%d", sum1, sum2, len);
}

mls_error mls_cp_checksum_verify(mls_cp_checksum *inst)
{
    mls_byte sum = mls_cp_checksum_compute(inst);
    if (sum == 0)
    {
        return NULL;
    }
    return mls_errors_make(500, "mls-cp-pack: bad checksum");
}

mls_byte mls_cp_checksum_compute(mls_cp_checksum *inst)
{
    mls_buffer_slice *slice = mls_cp_checksum_get_slice(inst);
    if (slice == NULL)
    {
        return 0;
    }
    size_t len = slice->length;
    mls_byte *buffer = slice->data;
    mls_byte sum, b;
    sum = 0;
    for (size_t i = 0; i < len; ++i)
    {
        b = buffer[i];
        sum = sum ^ b;
    }
    return sum;
}

/*******************************************************************************
 * mls_cp_pack_parser
 */

void mls_cp_pack_parser_init(mls_cp_pack_parser *parser)
{
    memset(parser, 0, sizeof(parser[0]));
}

mls_error mls_cp_pack_parser_parse(mls_cp_pack_parser *parser, uint8_t *data, size_t len)
{
    if (parser == NULL || data == NULL)
    {
        return mls_errors_make(0, "param(s) is null");
    }

    uint8_t *p = data;
    uint8_t *ending = data + len;
    uint8_t *next_pos;
    mls_cp_parser_callback_func callback = parser->callback;
    mls_cp_block *block;
    mls_error err;

    if (callback == NULL)
    {
        return mls_errors_make(0, "callback function is null");
    }

    for (; p < ending;)
    {
        block = (mls_cp_block *)p;
        next_pos = p + block->head.size;
        if (next_pos > ending)
        {
            return mls_errors_make(0, "ending at bad position");
        }
        err = callback(parser, block);
        if (err)
        {
            return err;
        }
        p = next_pos;
    }

    return NULL;
}

/*******************************************************************************
 * EOF
 */
