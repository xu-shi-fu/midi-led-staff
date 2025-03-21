// control_protocol.h

#ifndef __control_protocol_h__
#define __control_protocol_h__

#include "mlb_common.h"
#include "mlb_errors.h"

// typedef struct mlb_cp_tx_context;

/***
 * 函数指针
 */

typedef error (*mlb_cp_tx_func)(struct mlb_cp_tx_context *);

/***
 * 结构
 */

typedef struct
{

    uint8_t *data;
    size_t length;
    size_t capacity;

} mlb_cp_rx_context;

typedef struct
{

    uint8_t *data;
    size_t length;
    size_t capacity;

} mlb_cp_tx_context;

typedef struct
{

    mlb_cp_rx_context *rx;
    mlb_cp_tx_context *tx;

    mlb_cp_tx_func dispatcher;

} mlb_cp_rtx_context;

/***
 * 函数
 */

void mlb_control_protocol_init();
void mlb_control_protocol_loop();
error mlb_control_protocol_handle_rx(mlb_cp_rtx_context *ctx);

#endif // __control_protocol_h__
