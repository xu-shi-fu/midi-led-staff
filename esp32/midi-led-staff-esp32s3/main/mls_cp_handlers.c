#include "mls_cp_server.h"
#include "mls_common.h"

#include "handlers/handlers.h"

////////////////////////////////////////////////////////////////////////////////
// functions

mls_error mls_cp_register_handler(mls_cp_server *server, mls_cp_method method, mls_cp_location location, mls_cp_handler_func fn);

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

    err = mls_cp_register_handler(server, MLS_CP_METHOD_GET, MLS_CP_LOCATION_FOO_BAR, mlscp_get_example);
    mls_error_holder_push(&eh, err);

    err = mls_cp_register_handler(server, MLS_CP_METHOD_GET, MLS_CP_LOCATION_PING, mlscp_get_ping);
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
