// handlers.h

#ifndef __all_handlers_h__
#define __all_handlers_h__

#include "mls_cp_context.h"
#include "mls_cp_request.h"
#include "mls_app.h"

mls_error mlscp_get_ping(mls_cp_context *ctx, mls_cp_request *req);
mls_error mlscp_get_example(mls_cp_context *ctx, mls_cp_request *req);

mls_error mlscp_get_leds(mls_cp_context *ctx, mls_cp_request *req);
mls_error mlscp_post_leds(mls_cp_context *ctx, mls_cp_request *req);

#endif // __all_handlers_h__
