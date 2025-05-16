// nvs.h

#ifndef __nvs_h__
#define __nvs_h__

#include "mls_common.h"
#include "mls_errors.h"
#include "mls_module.h"

typedef struct mls_nvs_module_t
{

    mls_module module;

} mls_nvs_module;

mls_module *mls_nvs_module_init(mls_nvs_module *m);

#endif // __nvs_h__
