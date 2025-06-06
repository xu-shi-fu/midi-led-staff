// mls_cp_context.h

#ifndef __mls_cp_context_h__
#define __mls_cp_context_h__

#include "mls_common_mls.h"
#include "mls_buffer.h"
#include "mls_api.h"
#include "mls_control_protocol.h"
#include "mls_cp_address.h"
#include "mls_cp_request.h"
#include "mls_cp_response.h"

// mls_cp_implementation 是抽象的控制协议上下文实现
typedef struct mls_cp_implementation_t
{

    const char *name;
    void *outer; // 指向具体实现的结构

} mls_cp_implementation;

// mls_cp_context 是抽象的控制协议上下文
typedef struct mls_cp_context_t
{

    mls_cp_transaction_id transaction; // 事务 ID

    struct mls_cp_request_t *request;
    struct mls_cp_response_t *response;
    struct mls_cp_dispatcher_t *dispatcher;
    struct mls_cp_handler_t *handler;
    struct mls_cp_server_t *server;
    struct mls_cp_implementation_t *implementation;
    struct mls_app_t *app;

} mls_cp_context;

#endif // __mls_cp_context_h__
