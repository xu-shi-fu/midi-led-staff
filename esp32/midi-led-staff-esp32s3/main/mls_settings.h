// settings.h

#ifndef __settings_h__
#define __settings_h__

#include "mls_common.h"
#include "mls_errors.h"
#include "mls_module.h"

////////////////////////////////////////////////////////////////////////////////
// settings for modules

typedef struct mls_settings_wifi_t
{
} mls_settings_wifi;

typedef struct mls_settings_ble_t
{
} mls_settings_ble;

typedef struct mls_settings_udp_t
{
    mls_uint16 port;

} mls_settings_udp;

typedef struct mls_settings_midi_t
{
} mls_settings_midi;

typedef struct mls_settings_led_t
{

    uint8_t output_offset; // 需要输出的的位置
    uint8_t output_limit;  // 需要输出的个数

} mls_settings_led;

////////////////////////////////////////////////////////////////////////////////
// settings

typedef struct mls_settings_t
{
    mls_settings_led led;

    mls_settings_wifi wifi;

    mls_settings_udp udp;

    mls_settings_ble ble;

    mls_settings_midi midi;

} mls_settings;

////////////////////////////////////////////////////////////////////////////////
// module

typedef struct mls_settings_module_t
{
    mls_module module;

    mls_settings settings;

} mls_settings_module;

////////////////////////////////////////////////////////////////////////////////
// functions

mls_module *mls_settings_module_init(mls_settings_module *m1);

// void mls_settings_init();
// void mls_settings_loop();
// SettingsAll *mls_settings_get_all();

#endif // __settings_h__
