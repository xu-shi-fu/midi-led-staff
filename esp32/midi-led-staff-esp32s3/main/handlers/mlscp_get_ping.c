// mlscp_get_ping.c

#include "handlers.h"

mls_error mlscp_get_ping(mls_cp_context *ctx, mls_cp_request *req)
{
    mls_cp_response_builder rb;
    mls_cp_response_builder_init_with_context(&rb, ctx);

    mls_cp_status_code status = MLS_CP_STATUS_OK;
    rb.status.code = status;
    rb.status.message = mls_cp_status_stringify(status);
    rb.to = req->remote;

    return mls_cp_response_builder_build_and_send(&rb, ctx);
}

mls_error mlscp_get_example(mls_cp_context *ctx, mls_cp_request *req)
{

    mls_timestamp time = req->timestamp;
    ESP_LOGI(TAG, "mlscp_get_example: handle todo ... time:%lld ", time);

    mls_cp_response_builder rb;
    mls_cp_response_builder_init_with_context(&rb, ctx);

    mls_cp_status_code status = MLS_CP_STATUS_NOT_IMPLEMENTED; // MLS_CP_STATUS_OK;
    rb.status.code = status;
    rb.status.message = mls_cp_status_stringify(status);
    rb.to = req->remote;

    return mls_cp_response_builder_build_and_send(&rb, ctx);
}
