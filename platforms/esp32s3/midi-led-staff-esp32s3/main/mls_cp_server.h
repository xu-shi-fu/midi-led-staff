// mls_cp_server.h

#ifndef __control_protocol_server_h__
#define __control_protocol_server_h__

#include "mls_errors.h"
#include "mls_buffer.h"
#include "mls_tasks.h"
#include "mls_control_protocol.h"

/**
 *
 * handler
 *
 * context (parser,builder)
 * server
 * adapter
 */

struct mls_cp_adapter_t;
struct mls_cp_context_t;
struct mls_cp_handler_t;
struct mls_cp_server_t;
struct mls_cp_handler_registration_t;

/*******************************************************************************
 * 函数指针
 */

typedef mls_error (*mls_cp_handler_func)(struct mls_cp_context_t *context);
typedef mls_error (*mls_cp_dispatcher_func)(struct mls_cp_context_t *context, mls_buffer_slice *data);

/*******************************************************************************
 *  adapter
 */

typedef struct mls_cp_adapter_t
{

    struct mls_cp_dispatcher *dispatcher;

} mls_cp_adapter;

/*******************************************************************************
 *  dispatcher
 */

typedef struct mls_cp_dispatcher_t
{

    mls_cp_dispatcher_func fn;

} mls_cp_dispatcher;

/*******************************************************************************
 *  handler
 */

typedef struct mls_cp_handler_t
{

    mls_cp_handler_func fn;

} mls_cp_handler;

typedef struct mls_cp_handler_registration_t
{

    struct mls_cp_handler_registration_t *next;

    mls_cp_handler *handler;

} mls_cp_handler_registration;

/*******************************************************************************
 *  request
 */

typedef struct mls_cp_request_t
{
    struct sockaddr_in remote;
    mls_buffer_slice buffer;
    mls_cp_block_array *blocks;

} mls_cp_request;

/*******************************************************************************
 *  response
 */

typedef struct mls_cp_response_t
{
    struct sockaddr_in remote;
    mls_buffer_slice buffer;
    mls_cp_block_array *blocks;

} mls_cp_response;

/*******************************************************************************
 *  share
 */

// mls_cp_share_t 结构里包含了各个事务之间共享的一些资源 (如,缓冲区等)
typedef struct mls_cp_share_t
{

    mls_mutex mutex;

    mls_buffer_holder response_buffer;

    mls_cp_block_array response_blocks;
    mls_cp_block_array request_blocks;

} mls_cp_share;

mls_error mls_cp_share_init(mls_cp_share *share);

/*******************************************************************************
 *  context
 */

typedef struct mls_cp_context_t
{
    mls_cp_request request;
    mls_cp_response response;

    struct mls_cp_adapter_t *adapter;
    struct mls_cp_server_t *server;

} mls_cp_context;

/*******************************************************************************
 *  server
 */

typedef struct mls_cp_server_t
{

    mls_cp_handler_registration *handlers;
    mls_cp_handler *main;
    mls_cp_share *share;

} mls_cp_server;

mls_error mls_cp_server_init(mls_cp_server *server);
mls_error mls_cp_server_start(mls_cp_server *server);
mls_error mls_cp_server_register_handler(mls_cp_server *server, mls_cp_handler *handler);
mls_error mls_cp_server_register_handler_reg(mls_cp_server *server, mls_cp_handler_registration *hr);

mls_error mls_cp_server_handle(mls_cp_context *context);

/*******************************************************************************
 *  EOF
 */

#endif // __control_protocol_server_h__
