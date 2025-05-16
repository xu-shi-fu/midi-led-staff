// udp_server.h

#ifndef __udp_server_h__
#define __udp_server_h__

#include "mls_common.h"
#include "mls_buffer.h"
#include "mls_errors.h"
#include "mls_module.h"
#include "mls_control_protocol.h"
#include "mls_cp_server.h"
#include "mls_cp_adapter.h"

typedef struct mls_cp_udp_context_t
{
    mls_cp_adapter base_adapter;

    int port;
    int socket_fd;

    struct sockaddr_in address;

    mls_buffer_x rx_buffer;
    mls_buffer_x tx_buffer;

    mls_cp_server *server;

} mls_cp_udp_context;

typedef struct mls_cp_udp_adapter_t
{
    mls_cp_udp_context *context;

} mls_cp_udp_adapter;

typedef struct mls_cp_udp_module_t
{
    mls_module module;
    mls_cp_udp_adapter adapter;
    mls_cp_udp_context context;

} mls_cp_udp_module;

////////////////////////////////////////////////////////////////////////////////

// address

void convert_address_from_sock_to_cp(struct sockaddr_in *src, mls_cp_address *dst);
void convert_address_from_cp_to_sock(mls_cp_address *src, struct sockaddr_in *dst);

// adapter

mls_cp_adapter *mls_cp_udp_adapter_get_adapter(mls_cp_udp_adapter *adapter);

// context

// module

mls_module *mls_cp_udp_module_init(mls_cp_udp_module *module);

#endif // __udp_server_h__
