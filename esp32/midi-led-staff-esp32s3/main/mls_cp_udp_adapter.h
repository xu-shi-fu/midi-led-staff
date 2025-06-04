// udp_server.h

#ifndef __udp_server_h__
#define __udp_server_h__

#include "mls_common_mls.h"
#include "mls_buffer.h"
#include "mls_errors.h"
#include "mls_module.h"
#include "mls_control_protocol.h"
#include "mls_cp_server.h"

typedef struct mls_cp_udp_module_t
{
    mls_module module;

} mls_cp_udp_module;

////////////////////////////////////////////////////////////////////////////////

mls_module *mls_cp_udp_module_init(mls_cp_udp_module *module);

#endif // __udp_server_h__
