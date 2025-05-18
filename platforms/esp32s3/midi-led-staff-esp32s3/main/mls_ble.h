// ble.h

#ifndef __ble_h__
#define __ble_h__

#include "mls_common.h"
#include "mls_errors.h"
#include "mls_module.h"

typedef struct mls_ble_module_t
{

    mls_module module;

} mls_ble_module;

////////////////////////////////////////////////////////////////////////////////

mls_module *mls_ble_module_init(mls_ble_module *m1);

// void mls_ble_init();
// void mls_ble_loop();

#endif // __ble_h__
