// mls_common_mls.h

#ifndef __common_mls_h__
#define __common_mls_h__

#include "mls_config.h"
#include "mls_common_std.h"
#include "mls_types.h"
#include "mls_errors.h"

extern const char *TAG;

#define MLS_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MLS_MAX(a, b) (((a) > (b)) ? (a) : (b))

#endif // __common_mls_h__
