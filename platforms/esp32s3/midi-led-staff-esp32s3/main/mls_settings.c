// mls_settings.c

#include "mls_settings.h"

////////////////////////////////////////////////////////////////////////////////
// internal

mls_settings_module *mls_settings_module_get_module(mls_module *m);

mls_error mls_settings_module_on_init(mls_module *m);
mls_error mls_settings_module_on_create(mls_module *m);
mls_error mls_settings_module_on_loop(mls_module *m);

////////////////////////////////////////////////////////////////////////////////

mls_settings_module *mls_settings_module_get_module(mls_module *m)
{
    void *p = m->inner;
    return p;
}

mls_error mls_settings_module_on_init(mls_module *m1)
{
    mls_settings_module *m2 = mls_settings_module_get_module(m1);
    mls_settings *all = &m2->settings;
    memset(all, 0, sizeof(all[0]));

    // temp: 暂时写死这些参数,便于调试

    all->led.output_offset = 0; // 从第 0 键开始输出
    all->led.output_limit = 12; // 共 12 键 (C to B)

    all->udp.port = 7923;

    return NULL;
}

mls_error mls_settings_module_on_create(mls_module *m)
{
    return NULL;
}

mls_error mls_settings_module_on_loop(mls_module *m)
{
    return NULL;
}

mls_module *mls_settings_module_init(mls_settings_module *m1)
{
    mls_module *m2 = &m1->module;
    m2->name = "mls_settings_module";
    m2->on_init = mls_settings_module_on_init;
    m2->on_create = mls_settings_module_on_create;
    m2->on_run = mls_settings_module_on_loop;
    m2->inner = m1;
    return m2;
}
