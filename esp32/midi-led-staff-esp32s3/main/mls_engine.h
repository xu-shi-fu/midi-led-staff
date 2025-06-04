// mls_engine.h

#ifndef __engine_h__
#define __engine_h__

#include "mls_common_mls.h"
#include "mls_errors.h"
#include "mls_module.h"
#include "mls_cp_base.h"

////////////////////////////////////////////////////////////////////////////////

typedef struct mls_engine_key_item_t
{

    mls_byte value; // 这里的取值为 styles[index] 中的 index

} mls_engine_key_item;

typedef struct mls_engine_key_buffer_t
{
    mls_revision revision;

    uint total;
    uint offset;
    uint length;

    mls_engine_key_item items[128]; // 与 led-buffer 的 128 个 items 一一对应

} mls_engine_key_buffer;

////////////////////////////////////////////////////////////////////////////////

typedef struct mls_engine_style_item_t
{

    mls_argb color;

} mls_engine_style_item;

typedef struct mls_engine_style_buffer_t
{
    mls_revision revision;

    uint total;
    uint offset;
    uint length;

    mls_engine_style_item items[256];

} mls_engine_style_buffer;

////////////////////////////////////////////////////////////////////////////////

typedef struct mls_engine_led_item_t
{

    mls_byte r;
    mls_byte g;
    mls_byte b;

} mls_engine_led_item;

typedef struct mls_engine_led_buffer_t
{

    uint total;
    uint offset;
    uint length;
    size_t unit_size;
    size_t total_size;

    mls_revision revision_of_config;
    mls_revision revision_of_data;

    mls_engine_led_item items[128]; // 与 key-buffer 的 128 个 items 一一对应

} mls_engine_led_buffer;

mls_error mls_engine_led_buffer_init(mls_engine_led_buffer *inst);
mls_error mls_engine_led_buffer_init_as_demo(mls_engine_led_buffer *inst);

////////////////////////////////////////////////////////////////////////////////

typedef struct mls_engine_t
{

    mls_engine_key_buffer key_buffer;

    mls_engine_led_buffer led_buffer;

    mls_engine_style_buffer style_buffer;

} mls_engine;

typedef struct mls_engine_module_t
{

    mls_module module;

    mls_engine engine;

} mls_engine_module;

////////////////////////////////////////////////////////////////////////////////

mls_module *mls_engine_module_init(mls_engine_module *m);

#endif // __engine_h__
