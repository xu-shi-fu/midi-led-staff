#include "mls_app.h"

#include "mls_tasks.h"

////////////////////////////////////////////////////////////////////////////////
// task group

typedef struct
{

    mls_task midi;
    mls_task udp_server;
    mls_task engine;
    mls_task led;

} mls_task_group;

static mls_task_group the_mls_task_group;

////////////////////////////////////////////////////////////////////////////////
// tasks

mls_error mls_task_ble(mls_app *app)
{
    mls_ble_loop();
    return NULL;
}

mls_error mls_task_led(mls_app *app)
{
    return mls_led_loop(&app->led);
}

mls_error mls_task_midi(mls_app *app)
{
    // mls_midi_loop();

    return mls_errors_make(404, "no impl this task");
}

mls_error mls_task_engine(mls_app *app)
{
    return mls_engine_loop(&app->engine);
}

mls_error mls_task_udp_server(mls_app *app)
{
    const bool infinity = true;
    mls_udp_server *server = &app->udp_server;
    return mls_udp_server_loop(server, infinity);
}

////////////////////////////////////////////////////////////////////////////////

mls_error mls_app_init(mls_app *app)
{
    mls_error err;

    err = mls_nvs_init();
    if (err)
    {
        return err;
    }

    mls_settings_init();
    mls_ble_init();
    mls_wifi_init();

    // mls_midi_init();

    err = mls_udp_server_init(&app->udp_server);
    if (err)
    {
        return err;
    }

    err = mls_led_init(&app->led);
    if (err)
    {
        return err;
    }

    err = mls_engine_init(&app->engine);
    if (err)
    {
        return err;
    }

    return NULL;
}

mls_error mls_app_create(mls_app *app)
{

    return NULL;
}

mls_error mls_app_start(mls_app *app)
{
    mls_task_group *tg = &the_mls_task_group;
    mls_task *task;

    memset(&the_mls_task_group, 0, sizeof(the_mls_task_group));

    // init all tasks

    mls_tasks_init(&tg->led);
    mls_tasks_init(&tg->midi);
    mls_tasks_init(&tg->engine);
    mls_tasks_init(&tg->udp_server);

    // config

    task = &tg->engine;
    task->name = "engine";
    task->fn = mls_task_engine;
    task->app = app;

    task = &tg->led;
    task->name = "led";
    task->fn = mls_task_led;
    task->app = app;

    task = &tg->midi;
    task->name = "midi";
    task->fn = mls_task_midi;
    task->app = app;

    task = &tg->udp_server;
    task->name = "udp-server";
    task->fn = mls_task_udp_server;
    task->app = app;

    // start all
    mls_tasks_start(&tg->midi);
    mls_tasks_start(&tg->led);
    mls_tasks_start(&tg->udp_server);
    mls_tasks_start(&tg->engine);

    return NULL;
}

mls_error mls_app_loop(mls_app *app)
{
    // main loop

    return NULL;
}
