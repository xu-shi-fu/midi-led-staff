// wifi.h

#ifndef __wifi_h__
#define __wifi_h__

#include "mls_common.h"
#include "mls_errors.h"
#include "mls_module.h"

typedef struct mls_wifi_module_t
{

    mls_module module;

} mls_wifi_module;

mls_module *mls_wifi_module_init(mls_wifi_module *m1);

#endif // __wifi_h__
