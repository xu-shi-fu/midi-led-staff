// mls_engine.h

#ifndef __engine_h__
#define __engine_h__

#include "mls_common.h"
#include "mls_errors.h"

typedef struct
{

} mls_engine;

mls_error mls_engine_init(mls_engine *engine);
mls_error mls_engine_loop(mls_engine *engine);

#endif // __engine_h__
