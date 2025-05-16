// mls_engine.h

#ifndef __engine_h__
#define __engine_h__

#include "mls_common.h"
#include "mls_errors.h"
#include "mls_module.h"

typedef struct
{

} mls_engine;

typedef struct mls_engine_module_t
{

    mls_module module;

} mls_engine_module;

////////////////////////////////////////////////////////////////////////////////

mls_module *mls_engine_module_init(mls_engine_module *m);

#endif // __engine_h__
