#include "mls_cp_server.h"

#include "mls_control_protocol.h"
#include "mls_tasks.h"
#include "mls_cp_context.h"

mls_error mls_cp_main_handler_fn(mls_cp_context *context, mls_cp_request *req);

mls_error mls_cp_server_module_on_init(mls_module *m);
mls_error mls_cp_server_module_on_create(mls_module *m);
mls_error mls_cp_server_module_on_start(mls_module *m);
mls_error mls_cp_server_module_on_loop(mls_module *m);

mls_cp_server *mls_cp_server_module_get_server(mls_module *m);
mls_cp_server_module *mls_cp_server_module_get_module(mls_module *m);

mls_error mls_cp_server_init(mls_cp_server *server);
mls_error mls_cp_server_create(mls_cp_server *server);
mls_error mls_cp_server_start(mls_cp_server *server);
mls_error mls_cp_server_run_fg(mls_cp_server *server);
mls_error mls_cp_server_run_bg(mls_cp_server *server);
mls_error mls_cp_server_setup_main_handler(mls_cp_server *server);
mls_error mls_cp_server_setup_share(mls_cp_server *server);

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

    return NULL;
}

mls_error mls_cp_server_create(mls_cp_server *server)
{
    mls_error err;
    mls_error_holder eh;
    mls_error_holder_init(&eh);

    err = mls_cp_server_setup_share(server);
    mls_error_holder_push(&eh, err);

    err = mls_cp_server_setup_main_handler(server);
    mls_error_holder_push(&eh, err);

    return eh.err;
}

mls_error mls_cp_server_setup_main_handler(mls_cp_server *server)
{
    mls_cp_handler *handler = NULL;
    size_t size = sizeof(handler[0]);
    handler = malloc(size);
    if (handler == NULL)
    {
        return mls_errors_make(0, "mls_cp_server_setup_main_handler: malloc failed");
    }
    memset(handler, 0, size);
    handler->fn = mls_cp_main_handler_fn;
    server->main = handler;
    return NULL;
}

mls_error mls_cp_server_setup_share(mls_cp_server *server)
{
    mls_cp_share *share = NULL;
    size_t size = sizeof(share[0]);
    share = malloc(size);
    if (share == NULL)
    {
        return mls_errors_make(0, "mls_cp_server_setup_share: malloc failed");
    }
    mls_cp_share_init(share);
    server->share = share;
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
    hr.handler = *handler;
    return mls_cp_server_register_handler_reg(server, &hr);
}

mls_error mls_cp_server_register_handler_reg(mls_cp_server *server, mls_cp_handler_registration *hr1)
{
    if (server == NULL || hr1 == NULL)
    {
        return mls_errors_make(0, "mls_cp_server_register_handler_reg: param(s) is NULL");
    }
    mls_cp_handler_registration *hr2 = malloc(sizeof(mls_cp_handler_registration));
    if (hr2 == NULL)
    {
        return mls_errors_make(0, "mls_cp_server_register_handler_reg: malloc failed");
    }
    *hr2 = *hr1;
    hr2->next = server->handlers;
    server->handlers = hr2;
    return NULL;
}

mls_error mls_cp_server_run_fg(mls_cp_server *server)
{
    return NULL;
}

mls_error mls_cp_server_run_bg(mls_cp_server *server)
{
    return NULL;
}

/*******************************************************************************
 * main-handler
 */

mls_error mls_cp_server_handle(mls_cp_context *context)
{
    mls_cp_server *server = context->server;
    mls_cp_handler *handler = server->main;
    mls_cp_request *req = context->request;
    mls_mutex *mutex = &server->share->mutex;
    mls_cp_handler_func fn = handler->fn;

    mls_mutex_lock(mutex);
    mls_error err = fn(context, req);
    mls_mutex_unlock(mutex);
    return err;
}

mls_error mls_cp_main_handler_fn(mls_cp_context *context, mls_cp_request *req)
{
    // todo ...

    mls_error err;

    mls_cp_pack_parser parser;
    mls_cp_pack_parser_init(&parser);
    parser.callback = NULL;
    parser.params = NULL;

    uint8_t *req_data = context->request->buffer->data;
    size_t req_len = context->request->buffer->size;
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
 * module
 */

mls_module *mls_cp_server_module_init(mls_cp_server_module *m1)
{
    mls_module *m2 = &m1->module;
    m2->name = "mls_cp_server_module";
    m2->on_init = mls_cp_server_module_on_init;
    m2->on_create = mls_cp_server_module_on_create;
    m2->on_start = mls_cp_server_module_on_start;
    m2->on_run = mls_cp_server_module_on_loop;

    m2->inner = m1; // inner == mls_cp_server_module
    return m2;
}

mls_cp_server *mls_cp_server_module_get_server(mls_module *m1)
{
    mls_cp_server_module *m2 = mls_cp_server_module_get_module(m1);
    if (m2)
    {
        return &m2->server;
    }
    return NULL;
}

mls_cp_server_module *mls_cp_server_module_get_module(mls_module *m1)
{
    if (m1)
    {
        mls_cp_server_module *m2 = m1->inner;
        return m2;
    }
    return NULL;
}

mls_error mls_cp_server_module_on_init(mls_module *m)
{
    mls_cp_server *server = mls_cp_server_module_get_server(m);
    return mls_cp_server_init(server);
}

mls_error mls_cp_server_module_on_create(mls_module *m)
{
    mls_cp_server *server = mls_cp_server_module_get_server(m);
    return mls_cp_server_create(server);
}

mls_error mls_cp_server_module_on_start(mls_module *m)
{
    mls_cp_server *server = mls_cp_server_module_get_server(m);
    return mls_cp_server_start(server);
}

mls_error mls_cp_server_module_on_loop(mls_module *m)
{
    mls_cp_server *server = mls_cp_server_module_get_server(m);
    return mls_cp_server_run_fg(server);
}

/*******************************************************************************
 * EOF
 */
