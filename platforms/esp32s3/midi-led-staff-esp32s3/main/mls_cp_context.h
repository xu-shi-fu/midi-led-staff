// mls_cp_context.h

#ifndef __mls_cp_context_h__
#define __mls_cp_context_h__

#include "mls_common.h"
#include "mls_buffer.h"
#include "mls_api.h"
#include "mls_control_protocol.h"
#include "mls_cp_address.h"

/*******************************************************************************
 *  request
 */

typedef struct mls_cp_request_t
{
    mls_cp_address remote;
    mls_buffer_slice buffer;
    mls_cp_block_array *blocks;

} mls_cp_request;

/*******************************************************************************
 *  response
 */

typedef struct mls_cp_response_t
{
    mls_cp_address remote;
    mls_buffer_slice buffer;
    mls_cp_block_array *blocks;

} mls_cp_response;

/*******************************************************************************
 *  context
 */

typedef struct mls_cp_context_detail_t
{

    struct mls_cp_udp_context_t *udp;
    struct mls_cp_ble_context_t *ble;

} mls_cp_context_detail;

typedef struct mls_cp_context_t
{
    mls_cp_request request;
    mls_cp_response response;

    struct mls_cp_adapter_t *adapter;
    struct mls_cp_server_t *server;

    mls_cp_context_detail detail;

} mls_cp_context;

#endif // __mls_cp_context_h__
