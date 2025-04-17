// udp_server.h

#ifndef __udp_server_h__
#define __udp_server_h__

#include "mls_common.h"
#include "mls_buffer.h"
#include "mls_errors.h"
#include "mls_control_protocol.h"
#include "mls_cp_server.h"

typedef struct
{
    mls_cp_adapter    base_adapter  ;

    int port;
    int socket_fd;

    struct sockaddr_in address;

    mls_buffer_holder rx_buffer;

    // mls_buffer_holder tx_buffer;
    // mls_cp_handler *handler;

    mls_cp_server *server;

} mls_cp_udp_adapter;

mls_error mls_cp_udp_adapter_init(mls_cp_udp_adapter *self);
mls_error mls_cp_udp_adapter_loop(mls_cp_udp_adapter *self, bool infinity);

#endif // __udp_server_h__
