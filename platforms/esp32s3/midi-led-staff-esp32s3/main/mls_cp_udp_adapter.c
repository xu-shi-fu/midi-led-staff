// mls_udp.c

#include "mls_cp_udp_adapter.h"
#include "mls_control_protocol.h"
#include "mls_buffer.h"

////////////////////////////////////////////////////////////////////////////////
// internal functions

mls_error mls_cp_udp_module_on_init(mls_module *m);
mls_error mls_cp_udp_module_on_start(mls_module *m);

mls_error mls_cp_udp_module_on_init(mls_module *m)
{
    return NULL;
}

mls_error mls_cp_udp_module_on_start(mls_module *m)
{
    return NULL;
}

////////////////////////////////////////////////////////////////////////////////

mls_module *mls_cp_udp_module_init(mls_cp_udp_module *m1)
{
    mls_module *m2 = &m1->module;
    m2->name = "mls_cp_udp_module";
    m2->on_init = mls_cp_udp_module_on_init;
    m2->on_start = mls_cp_udp_module_on_start;
    return m2;
}

mls_error mls_cp_udp_adapter_init(mls_cp_udp_adapter *adapter)
{
    // memset(ctx, 0, sizeof(ctx[0]));
    mls_cp_udp_context *ctx = adapter->context;

    ctx->port = 2333;
    // ctx->rx_buffer.capacity = 1024;
    // ctx->tx_buffer.capacity = 1024;

    // create socket
    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

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

mls_error mls_cp_udp_adapter_send(struct mls_cp_tx_context_t *ctx)
{
    return NULL;
}

mls_error mls_cp_udp_adapter_loop(mls_cp_udp_adapter *adapter, bool infinity)
{
    mls_cp_udp_context *ctx = adapter->context;

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
    context.adapter = mls_cp_udp_adapter_get_adapter(adapter);
    context.server = ctx->server;

    do
    {
        size_t rx_len = recvfrom(sock_fd, rx_buffer_data, rx_buffer_capacity, 0, (struct sockaddr *)&remote_sock_addr, &remote_addr_len);

        convert_address_from_sock_to_cp(&remote_sock_addr, &remote_cp_addr);

        context.request.buffer.data = rx_buffer_data;
        context.request.buffer.length = rx_len;
        context.request.remote = remote_cp_addr;

        mls_error err = mls_cp_server_handle(&context);
        if (err)
        {
            mls_errors_log(err);
        }

    } while (infinity);

    return NULL;
}
