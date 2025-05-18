// mls_ble.c

#include "mls_nvs.h"

mls_error mls_nvs_on_init(mls_module *m);

mls_module *mls_nvs_module_init(mls_nvs_module *m1)
{
    mls_module *m2 = &m1->module;
    m2->name = "mls_nvs_module";
    m2->on_init = mls_nvs_on_init;
    return m2;
}

mls_error mls_nvs_on_init(mls_module *m)
{
    // ESP_LOGI(TAG, "mls_nvs_module::on_init");

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    return NULL;
}

mls_error mls_nvs_loop()
{
    return NULL;
}
