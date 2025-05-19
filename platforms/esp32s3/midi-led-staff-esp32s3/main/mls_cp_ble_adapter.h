// ble_server.h

#ifndef __mls_cp_ble_adapter_h__
#define __mls_cp_ble_adapter_h__

#include "mls_common.h"
#include "mls_buffer.h"
#include "mls_errors.h"
#include "mls_control_protocol.h"
#include "mls_cp_server.h"

typedef struct mls_cp_ble_context_t
{

} mls_cp_ble_context;

typedef struct mls_cp_ble_adapter_t
{

} mls_cp_ble_adapter;

mls_error mls_cp_ble_adapter_init(mls_cp_ble_adapter *self);
mls_error mls_cp_ble_adapter_loop(mls_cp_ble_adapter *self, bool infinity);

#endif // __mls_cp_ble_adapter_h__
