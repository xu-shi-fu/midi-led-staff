#include "mls_app.h"

#include "mls_tasks.h"

////////////////////////////////////////////////////////////////////////////////
// task group

// typedef struct
// {

//     mls_task midi;
//     mls_task udp_server;
//     mls_task engine;
//     mls_task led;

// } mls_task_group;

// static mls_task_group the_mls_task_group;

////////////////////////////////////////////////////////////////////////////////
// tasks  ( deprecated )

// use: modules

// mls_error mls_task_ble(mls_app *app)
// {
//     mls_ble_loop();
//     return NULL;
// }

// mls_error mls_task_led(mls_app *app)
// {
//     return mls_led_loop(&app->led);
// }

// mls_error mls_task_midi(mls_app *app)
// {
//     // mls_midi_loop();

//     return mls_errors_make(404, "no impl this task");
// }

// mls_error mls_task_engine(mls_app *app)
// {
//     return mls_engine_loop(&app->engine);
// }

// mls_error mls_task_cp_udp_adapter(mls_app *app)
// {
//     const bool infinity = true;
//     mls_cp_udp_adapter *adapter = &app->udp_adapter;
//     return mls_cp_udp_adapter_loop(adapter, infinity);
// }

////////////////////////////////////////////////////////////////////////////////

void mls_app_wire_modules(mls_app *app)
{

    // app->udp.context.server = &app->server;
}

mls_error mls_app_init(mls_app *app)
{

    // list modules
    mls_module_array *modules = &app->modules;
    mls_module_array_init(modules);
    mls_module_array_create(modules, 5);

    mls_module_array_add(modules, mls_nvs_module_init(&app->nvs));
    mls_module_array_add(modules, mls_cp_udp_module_init(&app->udp));
    mls_module_array_add(modules, mls_engine_module_init(&app->engine));
    mls_module_array_add(modules, mls_led_module_init(&app->led));

    if (mls_module_array_is_overflow(modules))
    {
        return mls_errors_make(500, "mls_module_array_is_overflow");
    }

    // wire
    mls_app_wire_modules(app);

    // invoke: fn(init)
    return mls_module_array_invoke_each_init(modules);
}

mls_error mls_app_create(mls_app *app)
{

    return NULL;
}

mls_error mls_app_start(mls_app *app)
{

    // memset(&the_mls_task_group, 0, sizeof(the_mls_task_group));

    // init all tasks

    // start all

    return NULL;
}

mls_error mls_app_loop(mls_app *app)
{
    // main loop

    return NULL;
}
