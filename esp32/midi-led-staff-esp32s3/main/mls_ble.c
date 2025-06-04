#include "mls_ble.h"

mls_error mls_ble_module_on_init(mls_module *m);
mls_error mls_ble_module_on_loop(mls_module *m);

////////////////////////////////////////////////////////////////////////////////

mls_error mls_ble_module_on_init(mls_module *m)
{
    // ESP_LOGI(TAG, "run mls_ble_init");
    return NULL;
}

mls_error mls_ble_module_on_loop(mls_module *m)
{
    // ESP_LOGI(TAG, "run mls_ble_loop");
    return NULL;
}

mls_module *mls_ble_module_init(mls_ble_module *m1)
{
    mls_module *m2 = &m1->module;
    m2->name = "mls_ble_module";
    m2->on_init = mls_ble_module_on_init;
    m2->on_run = mls_ble_module_on_loop;
    return m2;
}
