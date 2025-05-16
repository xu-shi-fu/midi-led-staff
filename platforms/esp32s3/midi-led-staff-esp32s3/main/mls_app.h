// app.h

#ifndef __app_h__
#define __app_h__

#include "mls_api.h"
#include "mls_common.h"
#include "mls_errors.h"
#include "mls_buffer.h"

#include "mls_ble.h"
#include "mls_ws2812_led.h"
#include "mls_engine.h"
#include "mls_cp_udp_adapter.h"
#include "mls_wifi.h"
#include "mls_settings.h"
#include "mls_nvs.h"
#include "mls_cp_server.h"

typedef struct mls_app_t
{

    // ble,config,ctrl_protocol,engine,nvs,settings,tusb_midi,udp_server,wifi,ws2812,

    // loopers:
    // engine,tusb_midi,udp_server,ws2812

    mls_module_array modules;

    mls_nvs_module nvs;
    mls_cp_server_module server;
    mls_cp_udp_module udp;
    mls_led_module led;
    mls_engine_module engine;

} mls_app;

mls_error mls_app_init(mls_app *app);
mls_error mls_app_create(mls_app *app);
mls_error mls_app_start(mls_app *app);
mls_error mls_app_loop(mls_app *app);

#endif // __app_h__
