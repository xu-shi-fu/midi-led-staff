#include "mls_cp_server.h"

#include "mls_control_protocol.h"
#include "mls_tasks.h"
#include "mls_cp_context.h"

typedef struct mls_cp_request_parser_callback_t
{

    mls_cp_request *request;

} mls_cp_request_parser_callback; // rename: mls__cp_request_builder -> mls_cp_request_parser_callback

/*******************************************************************************
 * internal functions
 */

mls_error mls_cp_h404_handler_fn(mls_cp_context *context, mls_cp_request *req);
mls_error mls_cp_main_handler_fn(mls_cp_context *context, mls_cp_request *req);
mls_error mls_cp_context_parse_request(mls_cp_context *context, mls_cp_request *req);
mls_error mls_cp_context_verify_request(mls_cp_context *context, mls_cp_request *req);

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
mls_error mls_cp_server_setup_h404_handler(mls_cp_server *server);
mls_error mls_cp_server_setup_share(mls_cp_server *server);

mls_error mls_cp_request_parser_callback_fn(mls_cp_pack_parser *, mls_cp_block *block);
mls_error mls_cp_request_parser_callback_init(mls_cp_request_parser_callback *builder);
mls_error mls_cp_request_parser_callback_on_block(mls_cp_request_parser_callback *builder, mls_cp_block *block);

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

    err = mls_cp_server_setup_h404_handler(server);
    mls_error_holder_push(&eh, err);

    err = mls_cp_register_all_handlers(server);
    mls_error_holder_push(&eh, err);

    return mls_error_holder_get_error(&eh);
}

mls_error mls_cp_server_setup_h404_handler(mls_cp_server *server)
{
    mls_cp_handler *handler = NULL;
    size_t size = sizeof(handler[0]);
    handler = malloc(size);
    if (handler == NULL)
    {
        return mls_errors_make(0, "mls_cp_server_setup_h404_handler: malloc failed");
    }
    memset(handler, 0, size);
    handler->fn = mls_cp_h404_handler_fn;
    server->h404 = handler;
    return NULL;
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
 * mls_cp_request_parser_callback
 */

mls_error mls_cp_request_parser_callback_fn(struct mls_cp_pack_parser_t *parser, struct mls_cp_block_t *block)
{
    // ESP_LOGI(TAG, "parse...");

    if (parser == NULL || block == NULL)
    {
        return mls_errors_make(0, "mls_cp_request_parser_callback_callback: param(s) is NULL");
    }
    mls_cp_request_parser_callback *builder = parser->params;
    if (builder == NULL)
    {
        return mls_errors_make(0, "mls_cp_request_parser_callback_callback: builder is NULL");
    }
    return mls_cp_request_parser_callback_on_block(builder, block);
}

mls_error mls_cp_request_parser_callback_on_block(mls_cp_request_parser_callback *builder, mls_cp_block *block)
{
    mls_cp_block_head *head = &block->head;
    mls_cp_request *request = builder->request;
    mls_cp_context *context = request->context;
    mls_cp_block_array *blocks = request->blocks;

    mls_cp_block_array_add_block(blocks, block);

    if (head->group == MLS_CP_GROUP_COMMON)
    {
        switch (head->field)
        {
        case MLS_CP_FIELD_COMMON_METHOD:
            request->method = mls_cp_block_get_body_uint8(block);
            break;

        case MLS_CP_FIELD_COMMON_LOCATION:
            request->location = mls_cp_block_get_body_string(block);
            break;

        case MLS_CP_FIELD_COMMON_TRANSACTION_ID:
            context->transaction = mls_cp_block_get_body_uint32(block);
            break;

        case MLS_CP_FIELD_COMMON_TIMESTAMP:
            request->timestamp = mls_cp_block_get_body_int64(block);
            break;

        default:
            break;
        }
    }

    return NULL;
}

mls_error mls_cp_request_parser_callback_init(mls_cp_request_parser_callback *builder)
{
    size_t size = sizeof(builder[0]);
    memset(builder, 0, size);
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

mls_cp_handler *mls_cp_server_find_handler(mls_cp_context *context)
{
    mls_cp_handler *handler = NULL;
    mls_cp_handler_registration *p = NULL;

    if (context == NULL)
    {
        return NULL;
    }

    mls_cp_server *server = context->server;
    mls_cp_request *req = context->request;

    if (server == NULL || req == NULL)
    {
        return NULL;
    }

    p = server->handlers;

    for (; p; p = p->next)
    {
        mls_cp_handler *h2 = &p->handler;
        int eq = strcmp(h2->location, req->location);
        if ((h2->method == req->method) && (eq == 0))
        {
            handler = h2;
            break;
        }
    }

    return handler;
}

mls_cp_handler *mls_cp_server_get_404_handler(mls_cp_context *context)
{
    return context->server->h404;
}

mls_error mls_cp_h404_handler_fn(mls_cp_context *context, mls_cp_request *req)
{
    mls_cp_response_builder builder;
    mls_error err = mls_cp_response_builder_init_with_context(&builder, context);
    if (err)
    {
        return err;
    }

    mls_cp_status_code code = MLS_CP_STATUS_NOT_FOUND;
    builder.status.code = code;
    builder.status.message = mls_cp_status_stringify(code);

    return mls_cp_response_builder_build_and_send(&builder, context);
}

mls_error mls_cp_main_handler_fn(mls_cp_context *context, mls_cp_request *req)
{
    mls_error err;

    // 1. parse request

    err = mls_cp_context_parse_request(context, req);
    if (err)
    {
        return err;
    }

    mls_cp_block_array_log_all(req->blocks);

    // 1.5 verify request
    err = mls_cp_context_verify_request(context, req);
    if (err)
    {
        return err;
    }

    // 2. find handler

    mls_cp_handler *handler = mls_cp_server_find_handler(context);
    if (handler == NULL)
    {
        handler = mls_cp_server_get_404_handler(context);
    }
    if (handler == NULL)
    {
        return mls_errors_make(0, "mls_cp_main_handler_fn: handler is NULL");
    }
    mls_cp_handler_func fn = handler->fn;
    if (fn == NULL)
    {
        return mls_errors_make(0, "mls_cp_main_handler_fn: handler->fn is NULL");
    }
    context->handler = handler;

    // 3. call handler

    return fn(context, req);
}

mls_error mls_cp_context_verify_request(mls_cp_context *context, mls_cp_request *req)
{

    mls_cp_location location = req->location;
    if (location == NULL)
    {
        return mls_errors_make(0, "mls_cp_context_verify_request: location is NULL");
    }

    // todo: check-sum

    return NULL;
}

mls_error mls_cp_context_parse_request(mls_cp_context *context, mls_cp_request *req)
{
    mls_error err;
    mls_cp_pack_parser parser;
    mls_cp_request_parser_callback builder;

    mls_cp_pack_parser_init(&parser);
    mls_cp_request_parser_callback_init(&builder);

    builder.request = req;

    parser.callback = mls_cp_request_parser_callback_fn;
    parser.params = &builder;

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
