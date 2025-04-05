// udp_server.h

#ifndef __udp_server_h__
#define __udp_server_h__

#include "mls_common.h"
#include "mls_buffer.h"
#include "mls_errors.h"

typedef struct
{

    int port;
    int socket_fd;

    struct sockaddr_in address;

    mls_buffer_holder rx_buffer;
    mls_buffer_holder tx_buffer;

} mls_udp_server;

mls_error mls_udp_server_init(mls_udp_server *self);
mls_error mls_udp_server_loop(mls_udp_server *self, bool infinity);

#endif // __udp_server_h__
