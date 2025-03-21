// errors.h

#ifndef __errors_h__
#define __errors_h__

// #include "mlb_common.h"

typedef struct
{

    int code;
    char *const message;

} error_t, *error;

// void mlb_errors_init();
// void mlb_errors_loop();

error make_error(int code, char *const msg);

#endif // __errors_h__
