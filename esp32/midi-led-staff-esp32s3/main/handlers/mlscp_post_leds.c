#include "handlers.h"

typedef struct mlscp_post_leds_handling_t
{

    mls_cp_context *context;
    mls_cp_request *request;
    mls_cp_response *response;

} mlscp_post_leds_handling;

mls_error mlscp_post_leds_scan_request(mlscp_post_leds_handling *handling);

mls_error mlscp_post_leds(mls_cp_context *ctx, mls_cp_request *req)
{

    mlscp_post_leds_handling handling;
    handling.context = ctx;
    handling.request = req;
    handling.response = ctx->response;

    mlscp_post_leds_scan_request(&handling);

    return NULL;
}

mls_error mlscp_post_leds_scan_request(mlscp_post_leds_handling *handling)
{

    return NULL;
}
