#include "mls_cp_server.h"

#include "mls_control_protocol.h"
#include "mls_tasks.h"

mls_error mls_cp_main_handler_fn(mls_cp_context *context);

/*******************************************************************************
 * mls_cp_server
 */

mls_error mls_cp_server_init(mls_cp_server *server)
{

    if (server == NULL)
    {
        return mls_errors_make(0, "mls_cp_server_init: server is NULL");
    }

    memset(server, 0, sizeof(server[0]));

    // init share
    mls_cp_share *share = malloc(sizeof(mls_cp_share));
    mls_cp_share_init(share);
    server->share = share;

    // init main handler
    mls_cp_handler *handler = malloc(sizeof(mls_cp_handler));
    handler->fn = mls_cp_main_handler_fn;
    server->main = handler;

    return NULL;
}

mls_error mls_cp_server_start(mls_cp_server *server)
{

    if (server == NULL)
    {
        return mls_errors_make(0, "mls_cp_server_init: server is NULL");
    }

    return NULL;
}

mls_error mls_cp_server_register_handler(mls_cp_server *server, mls_cp_handler *handler)
{
    if (server == NULL || handler == NULL)
    {
        return mls_errors_make(0, "mls_cp_server_register_handler: param(s) is NULL");
    }
    mls_cp_handler_registration hr;
    memset(&hr, 0, sizeof(hr));
    hr.handler = handler;
    return mls_cp_server_register_handler_reg(server, &hr);
}

mls_error mls_cp_server_register_handler_reg(mls_cp_server *server, mls_cp_handler_registration *hr)
{
    if (server == NULL || hr == NULL)
    {
        return mls_errors_make(0, "mls_cp_server_register_handler_reg: param(s) is NULL");
    }

    if (hr->handler == NULL)
    {
        return mls_errors_make(0, "mls_cp_server_register_handler_reg: handler is NULL");
    }

    mls_cp_handler_registration *hr2 = malloc(sizeof(mls_cp_handler_registration));
    *hr2 = *hr;
    hr2->next = server->handlers;
    server->handlers = hr2;
    return NULL;
}

/*******************************************************************************
 * main-handler
 */

mls_error mls_cp_server_handle(mls_cp_context *context)
{
    mls_cp_server *server = context->server;
    mls_cp_handler *handler = server->main;
    mls_mutex *mutex = &server->share->mutex;

    mls_mutex_lock(mutex);
    mls_error err = handler->fn(context);
    mls_mutex_unlock(mutex);
    return err;
}

mls_error mls_cp_main_handler_fn(mls_cp_context *context)
{
    // todo ...

    mls_error err;

    mls_cp_pack_parser parser;
    mls_cp_pack_parser_init(&parser);
    parser.callback = NULL;
    parser.params = NULL;

    uint8_t *req_data = context->request.buffer.data;
    size_t req_len = context->request.buffer.length;
    err = mls_cp_pack_parser_parse(&parser, req_data, req_len);
    if (err)
    {
        return err;
    }

    return NULL;
}

/*******************************************************************************
 * mls_cp_share
 */

mls_error mls_cp_share_init(mls_cp_share *share)
{
    memset(share, 0, sizeof(share[0]));

    return NULL;
}

/*******************************************************************************
 * EOF
 */
