// mlb_settings.c

#include "mlb_settings.h"

static SettingsAll the_settings_all;

void mlb_settings_init()
{
    SettingsAll *all = &the_settings_all;
    memset(all, 0, sizeof(the_settings_all));

    // temp: 暂时写死这些参数,便于调试
    all->led.output_offset = 24; // 从第 24 键开始输出
    all->led.output_limit = 61;  // 共 61 键
}

void mlb_settings_loop()
{
}

SettingsAll *mlb_settings_get_all()
{
    return &the_settings_all;
}
