// mls_cp_mock_adapter.h

#ifndef __mls_cp_mock_adapter_h__
#define __mls_cp_mock_adapter_h__

#include "mls_common_mls.h"
#include "mls_buffer.h"
#include "mls_errors.h"
#include "mls_control_protocol.h"
#include "mls_cp_server.h"

// 用于调试|测试的控制协议适配器
typedef struct mls_cp_mock_module_t
{

    mls_module module;

} mls_cp_mock_module;

mls_module *mls_cp_mock_module_init(mls_cp_mock_module *m1);

#endif // __mls_cp_mock_adapter_h__
