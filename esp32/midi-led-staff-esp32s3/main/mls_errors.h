// errors.h

#ifndef __errors_h__
#define __errors_h__

#include "mls_common_mls.h"

typedef struct mls_error_t
{

    int code;
    const char *message;

} mls_error_meta, *mls_error;

typedef struct mls_error_holder_t
{

    mls_error err;

} mls_error_holder;

////////////////////////////////////////////////////////////////////////////////

mls_error mls_errors_make(int code, const char *msg);

void mls_error_holder_init(mls_error_holder *holder);
void mls_error_holder_reset(mls_error_holder *holder);
void mls_error_holder_push(mls_error_holder *holder, mls_error err);
mls_bool mls_error_holder_has_error(mls_error_holder *holder);
mls_error mls_error_holder_get_error(mls_error_holder *holder);

void mls_errors_log(mls_error err);
void mls_errors_log_warn(mls_error err);

void mls_panic(mls_error err);
void mls_panic_string(const char *err_msg);

#endif // __errors_h__
