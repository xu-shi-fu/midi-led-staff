// mls_cp_context.h

#ifndef __mls_cp_context_h__
#define __mls_cp_context_h__

#include "mls_common_mls.h"
#include "mls_buffer.h"
#include "mls_api.h"
#include "mls_control_protocol.h"
#include "mls_cp_address.h"

struct mls_cp_context_t;
struct mls_cp_request_t;
struct mls_cp_response_t;

/*******************************************************************************
 *  request
 */

typedef struct mls_cp_request_t
{
    struct mls_cp_context_t *context;
    mls_cp_address remote;
    mls_buffer_slice buffer;
    mls_cp_block_array *blocks;

} mls_cp_request;

/*******************************************************************************
 *  response
 */

typedef struct mls_cp_response_t
{
    struct mls_cp_context_t *context;
    mls_cp_address remote;
    mls_buffer_slice buffer;
    mls_cp_block_array *blocks;

} mls_cp_response;

// mls_cp_implementation 是抽象的控制协议上下文实现
typedef struct mls_cp_implementation_t
{

    const char *name;
    void *outer; // 指向具体实现的结构

} mls_cp_implementation;

/*******************************************************************************
 *  context
 */

// mls_cp_context 是抽象的控制协议上下文
typedef struct mls_cp_context_t
{
    struct mls_cp_request_t *request;
    struct mls_cp_response_t *response;
    struct mls_cp_dispatcher_t *dispatcher;
    struct mls_cp_handler_t *handler;
    struct mls_cp_server_t *server;
    struct mls_cp_implementation_t *implementation;

} mls_cp_context;

#endif // __mls_cp_context_h__
