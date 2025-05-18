// mls_settings.c

#include "mls_settings.h"

////////////////////////////////////////////////////////////////////////////////
// internal

mls_error mls_settings_module_on_init(mls_module *m);
mls_error mls_settings_module_on_loop(mls_module *m);

////////////////////////////////////////////////////////////////////////////////

static SettingsAll the_settings_all;

mls_error mls_settings_module_on_init(mls_module *m)
{
    SettingsAll *all = &the_settings_all;
    memset(all, 0, sizeof(the_settings_all));

    // temp: 暂时写死这些参数,便于调试
    all->led.output_offset = 0; // 从第 0 键开始输出
    all->led.output_limit = 12; // 共 12 键 (C to B)

    return NULL;
}

mls_error mls_settings_module_on_loop(mls_module *m)
{
    return NULL;
}

SettingsAll *mls_settings_get_all()
{
    return &the_settings_all;
}

mls_module *mls_settings_module_init(mls_settings_module *m1)
{
    mls_module *m2 = &m1->module;
    m2->name = "mls_settings_module";
    m2->on_init = mls_settings_module_on_init;
    m2->on_run = mls_settings_module_on_loop;
    return m2;
}
