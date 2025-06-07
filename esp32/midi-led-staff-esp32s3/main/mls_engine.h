// mls_engine.h

#ifndef __engine_h__
#define __engine_h__

#include "mls_common_mls.h"
#include "mls_errors.h"
#include "mls_tasks.h"
#include "mls_module.h"
#include "mls_cp_base.h"

////////////////////////////////////////////////////////////////////////////////

typedef struct mls_engine_key_item_t
{

    mls_byte key;      // MIDI 按键的值
    mls_byte velocity; // 表示按键速率, 0 表示按键已释放
    mls_byte style;    // 这里的取值为 styles[index] 中的 index

} mls_engine_key_item;

typedef struct mls_engine_key_buffer_t
{
    mls_revision revision;

    mls_uint total; // 总项数

    size_t total_size; // 全部项占用的字节
    size_t unit_size;  // 单项占用的字节

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

    mls_uint total; // 样式的总个数

    size_t total_size; // 全部项占用的字节
    size_t unit_size;  // 单项占用的字节

    mls_engine_style_item items[256];

} mls_engine_style_buffer;

////////////////////////////////////////////////////////////////////////////////

typedef struct mls_engine_led_buffer_t
{
    mls_revision revision; // 表示总体的改变

    mls_uint total;         // LED 的总个数
    mls_uint view_position; // 使用中的首个 LED 的 index
    mls_uint view_size;     // 使用中的 LED 的个数

    size_t unit_size;  // 单项占用的字节
    size_t total_size; // 全部项占用的字节

    mls_argb items[128]; // 与 key-buffer 的 128 个 items 一一对应

} mls_engine_led_buffer;

mls_error mls_engine_led_buffer_init(mls_engine_led_buffer *inst);
mls_error mls_engine_led_buffer_init_as_demo(mls_engine_led_buffer *inst);

////////////////////////////////////////////////////////////////////////////////

typedef struct mls_engine_t
{

    mls_byte mode; // current mode

    mls_engine_key_buffer key_buffer;

    mls_engine_led_buffer led_buffer;

    mls_engine_style_buffer style_buffer;

    mls_task task;

} mls_engine;

typedef struct mls_engine_module_t
{

    mls_module module;

    mls_engine engine;

} mls_engine_module;

////////////////////////////////////////////////////////////////////////////////

mls_module *mls_engine_module_init(mls_engine_module *m);

#endif // __engine_h__
