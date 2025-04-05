// mls_udp.c

#include "mls_udp_server.h"
#include "mls_control_protocol.h"
#include "mls_buffer.h"

mls_error mls_udp_server_init(mls_udp_server *ctx)
{
    memset(ctx, 0, sizeof(ctx[0]));

    ctx->port = 2333;
    ctx->rx_buffer.capacity = 1024;
    ctx->tx_buffer.capacity = 1024;

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

mls_error mls_udp_server_send(struct mls_cp_tx_context_t *ctx)
{
    return NULL;
}

mls_error mls_udp_server_loop(mls_udp_server *ctx, bool infinity)
{
    mls_buffer_holder_auto auto_rx_buffer, auto_tx_buffer;

    // prepare rx buffer
    mls_buffer_holder *rx_buffer_holder = &ctx->rx_buffer;
    mls_buffer_holder_auto_create(&auto_rx_buffer, rx_buffer_holder);
    if (!mls_buffer_holder_auto_ready(&auto_rx_buffer))
    {
        return mls_errors_make(0, "udp-server rx buffer is not ready");
    }
    uint8_t *rx_buffer = rx_buffer_holder->buffer->data;
    size_t rx_buffer_size = rx_buffer_holder->capacity;

    // prepare tx buffer
    mls_buffer_holder *tx_buffer_holder = &ctx->tx_buffer;
    mls_buffer_holder_auto_create(&auto_tx_buffer, tx_buffer_holder);
    if (!mls_buffer_holder_auto_ready(&auto_tx_buffer))
    {
        return mls_errors_make(0, "udp-server tx buffer is not ready");
    }
    uint8_t *tx_buffer = tx_buffer_holder->buffer->data;
    size_t tx_buffer_size = tx_buffer_holder->capacity;

    ESP_LOGI(TAG, "udp_server.rx_buffer.at   = %d", (int)rx_buffer);
    ESP_LOGI(TAG, "udp_server.rx_buffer.size = %d", rx_buffer_size);
    ESP_LOGI(TAG, "udp_server.tx_buffer.at   = %d", (int)tx_buffer);
    ESP_LOGI(TAG, "udp_server.tx_buffer.size = %d", tx_buffer_size);

    // socket
    int sock_fd = ctx->socket_fd;

    struct sockaddr_in remote_addr;
    socklen_t remote_addr_len = sizeof(remote_addr);

    mls_cp_rx_context rx;
    mls_cp_tx_context tx;
    mls_cp_rtx_context rtx;

    rtx.rx = &rx;
    rtx.tx = &tx;
    rtx.dispatcher = mls_udp_server_send;

    do
    {

        size_t rx_len = recvfrom(sock_fd, rx_buffer, rx_buffer_size, 0, (struct sockaddr *)&remote_addr, &remote_addr_len);

        // ESP_LOGI(TAG, "UDP: rx data.length = %d", rx_len);

        rx.length = rx_len;
        rx.data = rx_buffer;
        mls_error err = mls_cp_handle_rx(&rtx);
        if (err)
        {
            // ESP_LOGE (TAG, "UDP: rx data.length = %d",  err->message );
            mls_errors_log(err);
        }

    } while (infinity);

    mls_buffer_holder_auto_release(&auto_rx_buffer);
    return NULL;
}
