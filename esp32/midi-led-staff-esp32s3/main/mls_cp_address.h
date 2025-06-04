// mls_cp_address.h

#ifndef __mls_cp_address_h__
#define __mls_cp_address_h__

#include "mls_api.h"
#include "mls_common_mls.h"
#include "mls_buffer.h"
#include "mls_errors.h"
#include "mls_control_protocol.h"

typedef struct mls_cp_address_t
{

    char addr[16];

} mls_cp_address;

void mls_cp_address_log(mls_cp_address *addr);

#endif // __mls_cp_address_h__
