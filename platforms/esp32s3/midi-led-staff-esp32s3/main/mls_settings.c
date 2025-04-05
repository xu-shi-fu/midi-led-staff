// mls_settings.c

#include "mls_settings.h"

static SettingsAll the_settings_all;

void mls_settings_init()
{
    SettingsAll *all = &the_settings_all;
    memset(all, 0, sizeof(the_settings_all));

    // temp: 暂时写死这些参数,便于调试
    all->led.output_offset = 0; // 从第 0 键开始输出
    all->led.output_limit = 12; // 共 12 键 (C to B)
}

void mls_settings_loop()
{
}

SettingsAll *mls_settings_get_all()
{
    return &the_settings_all;
}
