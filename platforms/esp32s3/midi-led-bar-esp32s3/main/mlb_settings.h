// settings.h

#ifndef __settings_h__
#define __settings_h__

#include "mlb_common.h"

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

void mlb_settings_init();
void mlb_settings_loop();

SettingsAll *mlb_settings_get_all();

#endif // __settings_h__
