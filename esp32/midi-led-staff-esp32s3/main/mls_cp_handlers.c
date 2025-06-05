#include "mls_cp_server.h"
#include "mls_common.h"

#include "handlers/handlers.h"

////////////////////////////////////////////////////////////////////////////////
// functions

mls_error mls_cp_register_handler(mls_cp_server *server, mls_cp_method method, mls_cp_location location, mls_cp_handler_func fn);

mls_error mls_simple_cp_handlers_ping(mls_cp_context *ctx, mls_cp_request *req);
mls_error mls_simple_cp_handlers_example(mls_cp_context *ctx, mls_cp_request *req);

////////////////////////////////////////////////////////////////////////////////
// simple-handlers

mls_error mls_simple_cp_handlers_ping(mls_cp_context *ctx, mls_cp_request *req)
{
    mls_timestamp time = req->timestamp;
    ESP_LOGI(TAG, "mls_simple_cp_handlers_ping: handle todo ... time:%lld ", time);

    mls_cp_response_builder rb;
    mls_cp_response_builder_init_with_context(&rb, ctx);

    mls_cp_status_code status = MLS_CP_STATUS_NOT_IMPLEMENTED; // MLS_CP_STATUS_OK;
    rb.status.code = status;
    rb.status.message = mls_cp_status_stringify(status);
    rb.to = req->remote;

    return mls_cp_response_builder_build_and_send(&rb, ctx);
}

mls_error mls_simple_cp_handlers_example(mls_cp_context *ctx, mls_cp_request *req)
{
    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// mls_cp_server - register

mls_error mls_cp_register_handler(mls_cp_server *server, mls_cp_method method, mls_cp_location location, mls_cp_handler_func fn)
{
    if (server == NULL || location == NULL || fn == NULL)
    {
        return NULL;
    }

    mls_cp_handler handler;
    memset(&handler, 0, sizeof(handler));

    handler.method = method;
    handler.location = location;
    handler.fn = fn;

    return mls_cp_server_register_handler(server, &handler);
}

// 把所有的 handlers 注册到 server
mls_error mls_cp_register_all_handlers(mls_cp_server *server)
{
    mls_error err;
    mls_error_holder eh;
    mls_error_holder_init(&eh);

    err = mls_cp_register_handler(server, MLS_CP_METHOD_GET, MLS_CP_LOCATION_FOO_BAR, mls_simple_cp_handlers_example);
    mls_error_holder_push(&eh, err);

    err = mls_cp_register_handler(server, MLS_CP_METHOD_GET, MLS_CP_LOCATION_PING, mls_simple_cp_handlers_ping);
    mls_error_holder_push(&eh, err);

    // '/leds'

    err = mls_cp_register_handler(server, MLS_CP_METHOD_GET, MLS_CP_LOCATION_LEDS, mlscp_get_leds);
    mls_error_holder_push(&eh, err);

    err = mls_cp_register_handler(server, MLS_CP_METHOD_POST, MLS_CP_LOCATION_LEDS, mlscp_post_leds);
    mls_error_holder_push(&eh, err);

    return mls_error_holder_get_error(&eh);
}

////////////////////////////////////////////////////////////////////////////////
// EOF
