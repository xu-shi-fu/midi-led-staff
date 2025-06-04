#include "mls_cp_mock_adapter.h"

#include "mls_app.h"
#include "mls_common.h"

////////////////////////////////////////////////////////////////////////////////
// struct

typedef struct mls_cp_mock_adapter_t
{
    mls_cp_implementation implementation; // 适配器实现, 必须放在开头!

    mls_cp_server *server;

    mls_cp_context context;
    mls_cp_request request;
    mls_cp_response response;
    mls_cp_dispatcher dispatcher;

    mls_buffer rx_buffer;
    mls_buffer tx_buffer;
    mls_cp_block_array rx_blocks;
    mls_cp_block_array tx_blocks;

} mls_cp_mock_adapter;

////////////////////////////////////////////////////////////////////////////////
// function

mls_cp_mock_adapter *mls_cp_mock_module_get_adapter_with_module(mls_module *m);
mls_cp_mock_adapter *mls_cp_mock_module_get_adapter_with_context(mls_cp_context *context);

mls_error mls_cp_mock_module_dispatcher_func(struct mls_cp_context_t *context, struct mls_cp_response_t *resp);

mls_error mls_cp_mock_module_on_init(mls_module *m);
mls_error mls_cp_mock_module_on_create(mls_module *m);
mls_error mls_cp_mock_module_on_start(mls_module *m);
mls_error mls_cp_mock_module_on_run_loop(mls_module *m);

mls_error mls_cp_mock_adapter_init(mls_cp_mock_adapter *adapter);
mls_error mls_cp_mock_adapter_create(mls_cp_mock_adapter *adapter);
mls_error mls_cp_mock_adapter_start(mls_cp_mock_adapter *adapter);
mls_error mls_cp_mock_adapter_run(mls_cp_mock_adapter *adapter);

mls_error mls_cp_mock_adapter_run_test1(mls_cp_mock_adapter *adapter);
mls_error mls_cp_mock_adapter_run_test2(mls_cp_mock_adapter *adapter);

////////////////////////////////////////////////////////////////////////////////
// implementation

mls_module *mls_cp_mock_module_init(mls_cp_mock_module *m1)
{
    mls_module *m2 = &m1->module;

    m2->name = "mls_cp_mock_module";
    m2->inner = NULL;

    m2->on_init = mls_cp_mock_module_on_init;
    m2->on_create = mls_cp_mock_module_on_create;
    m2->on_start = mls_cp_mock_module_on_start;
    m2->on_run = mls_cp_mock_module_on_run_loop;

    return m2;
}

mls_error mls_cp_mock_module_dispatcher_func(struct mls_cp_context_t *context, struct mls_cp_response_t *resp)
{
    ESP_LOGI(TAG, "mls_cp_mock_module_dispatcher_func:  send response ... ");

    mls_cp_status status = resp->status;
    mls_buffer *buffer = resp->buffer;
    mls_cp_block_array *blocks = resp->blocks;

    int tid = context->transaction;
    int len = buffer->size;
    int code = status.code;
    const char *msg = status.message;

    if (msg == NULL)
    {
        msg = "[nil]";
    }

    ESP_LOGI(TAG, "dispatch [response length:%d tid:%d code:%d msg:%s]", len, tid, code, msg);

    mls_cp_block_array_log_all(blocks);

    return NULL;
}

mls_cp_mock_adapter *mls_cp_mock_module_get_adapter_with_context(mls_cp_context *context)
{
    if (context == NULL)
    {
        return NULL;
    }
    mls_cp_implementation *impl = context->implementation;
    if (impl == NULL)
    {
        return NULL;
    }
    mls_cp_mock_adapter *adapter = (mls_cp_mock_adapter *)impl;
    return adapter;
}

mls_cp_mock_adapter *mls_cp_mock_module_get_adapter_with_module(mls_module *m)
{
    if (m == NULL)
    {
        return NULL;
    }

    mls_cp_mock_adapter *adapter = m->inner; // inner is adapter

    if (adapter == NULL)
    {
        size_t size = sizeof(adapter[0]);
        adapter = malloc(size);
        memset(adapter, 0, size);
        m->inner = adapter;
    }

    return adapter;
}

mls_error mls_cp_mock_module_on_init(mls_module *m)
{
    mls_cp_mock_adapter *adapter = mls_cp_mock_module_get_adapter_with_module(m);
    if (adapter == NULL)
    {
        return mls_errors_make(500, "mls_cp_mock_module_on_init: failed to get adapter");
    }
    adapter->server = &m->app->server.server;
    return mls_cp_mock_adapter_init(adapter);
}

mls_error mls_cp_mock_module_on_create(mls_module *m)
{
    mls_cp_mock_adapter *adapter = mls_cp_mock_module_get_adapter_with_module(m);
    return mls_cp_mock_adapter_create(adapter);
}

mls_error mls_cp_mock_module_on_start(mls_module *m)
{
    mls_cp_mock_adapter *adapter = mls_cp_mock_module_get_adapter_with_module(m);
    return mls_cp_mock_adapter_start(adapter);
}

mls_error mls_cp_mock_module_on_run_loop(mls_module *m)
{
    mls_cp_mock_adapter *adapter = mls_cp_mock_module_get_adapter_with_module(m);
    return mls_cp_mock_adapter_run(adapter);
}

mls_error mls_cp_mock_adapter_init(mls_cp_mock_adapter *adapter)
{
    if (adapter == NULL)
    {
        return mls_errors_make(500, "mls_cp_mock_adapter_init: adapter is NULL");
    }

    mls_cp_context *context = &adapter->context;
    mls_cp_request *request = &adapter->request;
    mls_cp_response *response = &adapter->response;
    mls_cp_block_array *rx_blocks = &adapter->rx_blocks;
    mls_cp_block_array *tx_blocks = &adapter->tx_blocks;
    mls_buffer *rx_buffer = &adapter->rx_buffer;
    mls_buffer *tx_buffer = &adapter->tx_buffer;
    mls_cp_dispatcher *dispatcher = &adapter->dispatcher;

    context->handler = NULL; // let it is nil
    context->dispatcher = dispatcher;
    context->server = adapter->server;
    context->implementation = &adapter->implementation;
    context->request = request;
    context->response = response;

    request->blocks = rx_blocks;
    request->buffer = rx_buffer;
    request->context = context;

    response->blocks = tx_blocks;
    response->buffer = tx_buffer;
    response->context = context;

    dispatcher->fn = mls_cp_mock_module_dispatcher_func;

    return NULL;
}

mls_error mls_cp_mock_adapter_create(mls_cp_mock_adapter *adapter)
{
    mls_error err;
    mls_error_holder eh;
    mls_error_holder_init(&eh);

    // mls_cp_context *context = &adapter->context;
    // mls_cp_request *request = &adapter->request;
    // mls_cp_response *response = &adapter->response;

    mls_cp_block_array *rx_blocks = &adapter->rx_blocks;
    mls_cp_block_array *tx_blocks = &adapter->tx_blocks;
    mls_buffer *rx_buffer = &adapter->rx_buffer;
    mls_buffer *tx_buffer = &adapter->tx_buffer;

    rx_buffer->capacity = CP_RX_BUFFER_SIZE;
    tx_buffer->capacity = CP_TX_BUFFER_SIZE;

    err = mls_buffer_create(rx_buffer);
    mls_error_holder_push(&eh, err);

    err = mls_buffer_create(tx_buffer);
    mls_error_holder_push(&eh, err);

    err = mls_cp_block_array_create(rx_blocks, CP_RX_BLOCK_ARRAY_CAPACITY);
    mls_error_holder_push(&eh, err);

    err = mls_cp_block_array_create(tx_blocks, CP_TX_BLOCK_ARRAY_CAPACITY);
    mls_error_holder_push(&eh, err);

    return eh.err;
}

mls_error mls_cp_mock_adapter_start(mls_cp_mock_adapter *adapter)
{
    return NULL;
}

mls_error mls_cp_mock_adapter_run(mls_cp_mock_adapter *adapter)
{
    mls_error err;

    err = mls_cp_mock_adapter_run_test1(adapter);
    if (err)
    {
        return err;
    }

    err = mls_cp_mock_adapter_run_test2(adapter);
    if (err)
    {
        return err;
    }

    return NULL;
}

mls_error mls_cp_mock_adapter_run_test1(mls_cp_mock_adapter *adapter)
{
    mls_cp_context *ctx = &adapter->context;
    mls_buffer *buffer = ctx->request->buffer;

    // mls_cp_block_writer writer;
    // mls_cp_block_head head;
    ////  v2

    mls_cp_group_id group;
    mls_cp_request_builder builder;
    mls_cp_request_builder_init(&builder, buffer);

    builder.method = MLS_CP_METHOD_GET;
    builder.location = "/foo/bar-404";
    builder.transaction = 2233;

    group = MLS_CP_GROUP_EXAMPLE;
    mls_cp_request_builder_add_string(&builder, group, MLS_CP_FIELD_EXAMPLE_FOO, "foo");
    mls_cp_request_builder_add_int32(&builder, group, MLS_CP_FIELD_EXAMPLE_BAR, 666);

    mls_buffer_slice slice = mls_cp_request_builder_build(&builder);
    mls_error err = mls_cp_request_builder_get_error(&builder);
    if (err)
    {
        return err;
    }

    ESP_LOGI(TAG, "mls_cp_request_builder_build: slice.length=%d", slice.length);

    return mls_cp_server_handle(ctx);
}

mls_error mls_cp_mock_adapter_run_test2(mls_cp_mock_adapter *adapter)
{
    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
