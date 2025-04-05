// settings.h

#ifndef __settings_h__
#define __settings_h__

#include "mls_common.h"
#include "mls_errors.h"

typedef struct
{
} SettingsWifi;

typedef struct
{
} SettingsBLE;

typedef struct
{
} SettingsMIDI;

typedef struct
{

    uint8_t output_offset; // 需要输出的的位置
    uint8_t output_limit;  // 需要输出的个数

} SettingsLED;

typedef struct
{
    SettingsLED led;

    SettingsWifi wifi;

    SettingsBLE ble;

    SettingsMIDI midi;

} SettingsAll;

void mls_settings_init();
void mls_settings_loop();

SettingsAll *mls_settings_get_all();

#endif // __settings_h__
