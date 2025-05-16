// mls_cp_adapter.h

#ifndef __mls_cp_adapter_h__
#define __mls_cp_adapter_h__

#include "mls_api.h"
#include "mls_common.h"
#include "mls_buffer.h"
#include "mls_errors.h"
#include "mls_control_protocol.h"

typedef struct mls_cp_adapter_t
{

    char *name;
    struct mls_cp_dispatcher *dispatcher;

} mls_cp_adapter;

#endif // __mls_cp_adapter_h__
