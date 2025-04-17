/*
 * SPDX-FileCopyrightText: 2019 Ha Thach (tinyusb.org)
 *
 * SPDX-License-Identifier: MIT
 *
 * SPDX-FileContributor: 2022-2024 Espressif Systems (Shanghai) CO LTD
 */

// #include "mls_ble.h"
// // #include "mls_tusb_midi.h"
// #include "mls_ws2812_led.h"
// #include "mls_engine.h"
// #include "mls_wifi.h"
// #include "mls_settings.h"
// #include "mls_nvs.h"
// #include "mls_cp_udp_adapter.h"

#include "mls_app.h"
#include "mls_tasks.h"

const char *TAG = "MIDI-LED-STAFF";

static mls_app the_app;

mls_error app_main_inner(void)
{
    mls_error err;
    mls_app *app;
    app = &the_app;

    // init
    err = mls_app_init(app);
    if (err)
    {
        return err;
    }

    // create
    err = mls_app_create(app);
    if (err)
    {
        return err;
    }

    // start
    err = mls_app_start(app);
    if (err)
    {
        return err;
    }

    // run_loop
    return mls_app_loop(app);
}

void app_main(void)
{
    mls_error err;
    err = app_main_inner();
    if (err)
    {
        mls_errors_log(err);
    }
    mls_tasks_sleep(3000);
}
