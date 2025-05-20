#include "mls_app.h"

#include "mls_tasks.h"
#include "mls_module.h"

////////////////////////////////////////////////////////////////////////////////
// internal func

void mls_app_wire_modules(mls_app *app)
{

    // app->udp.context.server = &app->server;
}

mls_error mls_app_enumerate_modules(mls_app *app)
{

    mls_module *mod_nvs = mls_nvs_module_init(&app->nvs);
    mls_module *mod_settings = mls_settings_module_init(&app->settings);
    mls_module *mod_led = mls_led_module_init(&app->led);
    mls_module *mod_tusb_midi = mls_tusb_midi_module_init(&app->tusb_midi);
    mls_module *mod_ble = mls_ble_module_init(&app->ble);
    mls_module *mod_wifi = mls_wifi_module_init(&app->wifi);
    mls_module *mod_udp = mls_cp_udp_module_init(&app->udp);
    mls_module *mod_server = mls_cp_server_module_init(&app->server);
    mls_module *mod_engine = mls_engine_module_init(&app->engine);

    mod_nvs->enabled = true;
    mod_settings->enabled = true;
    mod_led->enabled = true;
    mod_udp->enabled = true;

    // list modules
    mls_module_array *modules = &app->modules;
    mls_module_array_init(modules);
    mls_module_array_create(modules, 10);

    // 这里的顺序决定了启动顺序
    mls_module_array_add(modules, mod_nvs);
    mls_module_array_add(modules, mod_settings);
    mls_module_array_add(modules, mod_led);
    mls_module_array_add(modules, mod_tusb_midi);
    mls_module_array_add(modules, mod_ble);
    mls_module_array_add(modules, mod_wifi);
    mls_module_array_add(modules, mod_udp);
    mls_module_array_add(modules, mod_server);
    mls_module_array_add(modules, mod_engine);

    if (mls_module_array_is_overflow(modules))
    {
        return mls_errors_make(500, "mls_module_array_is_overflow");
    }

    return NULL;
}

mls_error mls_app_init_pre(mls_app *app)
{
    memset(app, 0, sizeof(app[0]));

    mls_error err = mls_app_enumerate_modules(app);
    if (err)
    {
        return err;
    }

    mls_app_wire_modules(app);

    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// app::lifecycle

mls_error mls_app_init(mls_app *app)
{
    mls_error err = mls_app_init_pre(app);
    if (err)
    {
        mls_panic(err);
    }

    return mls_module_array_invoke_lifecycle_fn(&app->modules, MLS_LIFECYCLE_PHASE_INIT);
}

mls_error mls_app_create(mls_app *app)
{
    return mls_module_array_invoke_lifecycle_fn(&app->modules, MLS_LIFECYCLE_PHASE_CREATE);
}

mls_error mls_app_start(mls_app *app)
{
    return mls_module_array_invoke_lifecycle_fn(&app->modules, MLS_LIFECYCLE_PHASE_START);
}

mls_error mls_app_resume(mls_app *app)
{
    return mls_module_array_invoke_lifecycle_fn(&app->modules, MLS_LIFECYCLE_PHASE_RESUME);
}

mls_error mls_app_loop(mls_app *app)
{
    return mls_module_array_invoke_lifecycle_fn(&app->modules, MLS_LIFECYCLE_PHASE_RUN);
}

mls_error mls_app_pause(mls_app *app)
{
    return mls_module_array_invoke_lifecycle_fn(&app->modules, MLS_LIFECYCLE_PHASE_PAUSE);
}

mls_error mls_app_stop(mls_app *app)
{
    return mls_module_array_invoke_lifecycle_fn(&app->modules, MLS_LIFECYCLE_PHASE_STOP);
}

mls_error mls_app_destroy(mls_app *app)
{
    return mls_module_array_invoke_lifecycle_fn(&app->modules, MLS_LIFECYCLE_PHASE_DESTROY);
}

////////////////////////////////////////////////////////////////////////////////
// EOF
