// mls_udp.c

#include "mls_cp_udp_adapter.h"
#include "mls_control_protocol.h"
#include "mls_buffer.h"
#include "mls_common_esp.h"
#include "mls_app.h"

////////////////////////////////////////////////////////////////////////////////
// internal structures

typedef struct mls_cp_udp_adapter_t
{
    mls_cp_implementation impl; // 注意: 这个字段必须放在结构的开头, 以便使其地址与 owner 相同

    mls_cp_server *server;

    int port;
    int socket_fd;
    struct sockaddr_in address;

    mls_cp_context context;
    mls_cp_request request;
    mls_cp_response response;
    mls_buffer rx_buffer;
    mls_buffer tx_buffer;
    mls_cp_block_array rx_blocks;
    mls_cp_block_array tx_blocks;

    mls_task task;

} mls_cp_udp_adapter;

////////////////////////////////////////////////////////////////////////////////
// 内部函数(定义)

void convert_address_from_sock_to_cp(struct sockaddr_in *src, mls_cp_address *dst);
void convert_address_from_cp_to_sock(mls_cp_address *src, struct sockaddr_in *dst);

mls_error mls_cp_udp_module_on_init(mls_module *m);
mls_error mls_cp_udp_module_on_create(mls_module *m);
mls_error mls_cp_udp_module_on_start(mls_module *m);
mls_cp_udp_adapter *mls_cp_udp_module_get_adapter(mls_module *m);

mls_error mls_cp_udp_adapter_init(mls_cp_udp_adapter *adapter);
mls_error mls_cp_udp_adapter_create(mls_cp_udp_adapter *adapter);
mls_error mls_cp_udp_adapter_start(mls_cp_udp_adapter *adapter);
mls_error mls_cp_udp_adapter_listen(mls_cp_udp_adapter *adapter);
mls_error mls_cp_udp_adapter_run_loop(mls_cp_udp_adapter *adapter, bool infinity);

////////////////////////////////////////////////////////////////////////////////
// 内部函数(实现)

mls_error mls_cp_udp_module_on_init(mls_module *m)
{
    mls_cp_udp_adapter *adapter = mls_cp_udp_module_get_adapter(m);

    adapter->server = &m->app->server.server;

    return mls_cp_udp_adapter_init(adapter);
}

mls_error mls_cp_udp_module_on_create(mls_module *m)
{
    mls_cp_udp_adapter *adapter = mls_cp_udp_module_get_adapter(m);
    return mls_cp_udp_adapter_create(adapter);
}

mls_error mls_cp_udp_module_on_start(mls_module *m)
{
    mls_cp_udp_adapter *adapter = mls_cp_udp_module_get_adapter(m);
    return mls_cp_udp_adapter_start(adapter);
}

mls_cp_udp_adapter *mls_cp_udp_module_get_adapter(mls_module *m)
{
    if (m == NULL)
    {
        return NULL;
    }

    mls_cp_udp_adapter *adapter = m->inner; // inner==adapter

    if (adapter == NULL)
    {
        size_t size = sizeof(mls_cp_udp_adapter);
        adapter = malloc(size);
        if (adapter)
        {
            memset(adapter, 0, size);
            adapter->context.implementation = &adapter->impl;
            adapter->impl.name = m->name;
            adapter->impl.outer = adapter;
        }
        m->inner = adapter;
    }

    return adapter;
}

mls_error mls_cp_udp_adapter_init(mls_cp_udp_adapter *adapter)
{

    mls_buffer *rx_buffer = &adapter->rx_buffer;
    mls_buffer *tx_buffer = &adapter->tx_buffer;
    mls_cp_context *context = &adapter->context;
    mls_cp_request *request = &adapter->request;
    mls_cp_response *response = &adapter->response;
    mls_cp_block_array *rx_blocks = &adapter->rx_blocks;
    mls_cp_block_array *tx_blocks = &adapter->tx_blocks;
    mls_task *task = &adapter->task;

    mls_buffer_init(rx_buffer);
    mls_buffer_init(tx_buffer);
    mls_cp_block_array_init(rx_blocks);
    mls_cp_block_array_init(tx_blocks);
    mls_buffer_slice_init(&request->buffer, rx_buffer);
    mls_buffer_slice_init(&response->buffer, tx_buffer);
    mls_task_init(task);

    context->request = request;
    context->response = response;
    context->server = adapter->server;
    context->implementation = &adapter->impl;
    context->dispatcher = NULL;
    context->handler = NULL;

    request->context = context;
    request->blocks = rx_blocks;

    response->context = context;
    response->blocks = tx_blocks;

    task->name = "mls_cp_udp_adapter_task";

    return NULL;
}

mls_error mls_cp_udp_adapter_create(mls_cp_udp_adapter *adapter)
{
    mls_error err;
    mls_error_holder err_h;
    mls_error_holder_init(&err_h);

    mls_buffer *rx_buffer = &adapter->rx_buffer;
    mls_buffer *tx_buffer = &adapter->tx_buffer;

    rx_buffer->capacity = UDP_RX_BUFFER_SIZE;
    tx_buffer->capacity = UDP_TX_BUFFER_SIZE;

    err = mls_buffer_create(rx_buffer);
    mls_error_holder_push(&err_h, err);

    err = mls_buffer_create(tx_buffer);
    mls_error_holder_push(&err_h, err);

    mls_buffer_slice_reset(&adapter->request.buffer);
    mls_buffer_slice_reset(&adapter->response.buffer);

    return err_h.err;
}

mls_error mls_cp_udp_adapter_start(mls_cp_udp_adapter *adapter)
{
    mls_error err = mls_cp_udp_adapter_listen(adapter);
    if (err)
    {
        return err;
    }
    mls_task *task = &adapter->task;
    return mls_task_start(task);
}

mls_error mls_cp_udp_adapter_listen(mls_cp_udp_adapter *adapter)
{

    mls_cp_udp_adapter *ctx = adapter;

    ctx->port = 2333;
    // ctx->rx_buffer.capacity = 1024;
    // ctx->tx_buffer.capacity = 1024;

    // create socket
    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0)
    {
        ESP_LOGE(TAG, "error: udp socket create failed");
        return mls_errors_make(500, "udp socket create error");
    }

    // address
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    addr.sin_port = htons(ctx->port);

    // bind
    int ret = bind(sock_fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0)
    {
        ESP_LOGE(TAG, "error: udp bind return: %d", ret);
        return mls_errors_make(0, "udp bind error");
    }

    ESP_LOGI(TAG, "UDP: listen @local-port:%d", ctx->port);

    ctx->address = addr;
    ctx->socket_fd = sock_fd;

    return NULL;
}

mls_error mls_cp_udp_adapter_run_loop(mls_cp_udp_adapter *adapter, bool infinity)
{
    mls_cp_udp_adapter *ctx = adapter;

    // rx buffer
    uint8_t *rx_buffer_data = ctx->rx_buffer.data;
    size_t rx_buffer_capacity = ctx->rx_buffer.capacity;
    ESP_LOGI(TAG, "udp_server.rx_buffer.at   = %d", (int)rx_buffer_data);
    ESP_LOGI(TAG, "udp_server.rx_buffer.size = %d", rx_buffer_capacity);

    // socket
    int sock_fd = ctx->socket_fd;

    // remote address
    struct sockaddr_in remote_sock_addr;
    mls_cp_address remote_cp_addr;
    socklen_t remote_addr_len = sizeof(remote_sock_addr);

    // context
    mls_cp_context context;
    memset(&context, 0, sizeof(context));

    context.server = ctx->server;

    do
    {
        size_t rx_len = recvfrom(sock_fd, rx_buffer_data, rx_buffer_capacity, 0, (struct sockaddr *)&remote_sock_addr, &remote_addr_len);

        convert_address_from_sock_to_cp(&remote_sock_addr, &remote_cp_addr);

        context.request->buffer.data = rx_buffer_data;
        context.request->buffer.length = rx_len;
        context.request->remote = remote_cp_addr;

        mls_error err = mls_cp_server_handle(&context);
        if (err)
        {
            mls_errors_log(err);
        }

    } while (infinity);

    return NULL;
}

mls_error mls_cp_udp_adapter_send(mls_cp_udp_adapter *adapter)
{
    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// public functions

mls_module *mls_cp_udp_module_init(mls_cp_udp_module *m1)
{
    mls_module *m2 = &m1->module;
    m2->name = "mls_cp_udp_adapter_module";
    m2->on_init = mls_cp_udp_module_on_init;
    m2->on_create = mls_cp_udp_module_on_create;
    m2->on_start = mls_cp_udp_module_on_start;
    return m2;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
