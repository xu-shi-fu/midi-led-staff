// mlb_udp.c

#include "mlb_udp_server.h"
#include "mlb_control_protocol.h"

#include <sys/types.h>
#include <sys/socket.h>

typedef struct
{

    int port;
    int socket_fd;

    struct sockaddr_in address;

    char rx_buffer[64];

} UDPContext;

static UDPContext the_udp_context;

void mlb_udp_init()
{
    memset(&the_udp_context, 0, sizeof(the_udp_context));
    UDPContext *ctx = &the_udp_context;
    ctx->port = 2333;

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
        return;
    }

    ESP_LOGI(TAG, "UDP: listen @local-port:%d", ctx->port);

    ctx->address = addr;
    ctx->socket_fd = sock_fd;
}

void mlb_udp_loop(bool infinity)
{

    UDPContext *ctx = &the_udp_context;
    int sock_fd = ctx->socket_fd;
    char *rx_buffer = ctx->rx_buffer;
    size_t rx_buffer_size = sizeof(ctx->rx_buffer);

    struct sockaddr_in remote_addr;
    socklen_t remote_addr_len = sizeof(remote_addr);

    do
    {

        int rx_len = recvfrom(sock_fd, rx_buffer, rx_buffer_size, 0, (struct sockaddr *)&remote_addr, &remote_addr_len);

        ESP_LOGI(TAG, "UDP: rx data.length = %d", rx_len);

    } while (infinity);
}
