// errors.h

#ifndef __errors_h__
#define __errors_h__

#include "mls_common.h"

typedef struct
{

    int code;
    const char *message;

} mls_error_t, *mls_error;

mls_error mls_errors_make(int code, char *const msg);

void mls_errors_log(mls_error err);
void mls_errors_log_warn(mls_error err);

#endif // __errors_h__
