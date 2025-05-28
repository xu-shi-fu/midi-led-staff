// mls_cp_base.h

#ifndef __mls_cp_base_h__
#define __mls_cp_base_h__

#include "mls_api.h"
#include "mls_common_mls.h"
#include "mls_buffer.h"
#include "mls_errors.h"

/*******************************************************************************
 * types
 */

#define MLS_CP_TYPE_NO_VALUE 0

#define MLS_CP_TYPE_UINT8 0x01 // aka. MLS_CP_TYPE_BYTE
#define MLS_CP_TYPE_UINT16 0x02
#define MLS_CP_TYPE_UINT32 0x03
#define MLS_CP_TYPE_UINT64 0x04

#define MLS_CP_TYPE_INT8 0x11
#define MLS_CP_TYPE_INT16 0x12
#define MLS_CP_TYPE_INT32 0x13
#define MLS_CP_TYPE_INT64 0x14

#define MLS_CP_TYPE_FLOAT 0x21
#define MLS_CP_TYPE_DOUBLE 0x22

#define MLS_CP_TYPE_BOOL 0x31
#define MLS_CP_TYPE_STRING 0x32
#define MLS_CP_TYPE_BYTES 0x33
#define MLS_CP_TYPE_BYTE MLS_CP_TYPE_UINT8

#define MLS_CP_TYPE_ARGB 0x41

/*******************************************************************************
 * groups
 */

#define MLS_CP_GROUP_COMMON 0
#define MLS_CP_GROUP_SYSTEM 1
#define MLS_CP_GROUP_MIDI 2
#define MLS_CP_GROUP_LED 3
#define MLS_CP_GROUP_EXAMPLE 4
#define MLS_CP_GROUP_TEST 5

#define MLS_CP_GROUP_EXT_MIN 128
#define MLS_CP_GROUP_EXT_MAX 255

/*******************************************************************************
 * fields
 */

// @group:COMMON

#define MLS_CP_FIELD_COMMON_END_OF_PACK 0 // :uint8 (aka. MLS_CP_FIELD_COMMON_CHECK_SUM)
#define MLS_CP_FIELD_COMMON_CHECK_SUM 0   // :uint8 (aka. MLS_CP_FIELD_COMMON_END_OF_PACK)

#define MLS_CP_FIELD_COMMON_METHOD 1         // :uint8
#define MLS_CP_FIELD_COMMON_LOCATION 2       // :string
#define MLS_CP_FIELD_COMMON_VERSION 3        // :uint16
#define MLS_CP_FIELD_COMMON_STATUS_CODE 4    // :uint16
#define MLS_CP_FIELD_COMMON_STATUS_MSG 5     // :string
#define MLS_CP_FIELD_COMMON_TRANSACTION_ID 6 // :uint32
#define MLS_CP_FIELD_COMMON_TIMESTAMP 8      // :uint64

// @group:example

#define MLS_CP_FIELD_EXAMPLE_FOO 1 // :string
#define MLS_CP_FIELD_EXAMPLE_BAR 2 // :int32

// @group:test

/*******************************************************************************
 * methods
 */

#define MLS_CP_METHOD_GET 1
#define MLS_CP_METHOD_POST 2
#define MLS_CP_METHOD_PUT 3
#define MLS_CP_METHOD_DELETE 4

/*******************************************************************************
 * statuses
 */

#define MLS_CP_STATUS_CONTINUE 100

#define MLS_CP_STATUS_OK 200
#define MLS_CP_STATUS_CREATED 201
#define MLS_CP_STATUS_ACCEPTED 202

#define MLS_CP_STATUS_MULTIPLE_CHOICE 300
#define MLS_CP_STATUS_MOVED_PERMANENTLY 301
#define MLS_CP_STATUS_FOUND 302
#define MLS_CP_STATUS_SEE_OTHER 303
#define MLS_CP_STATUS_TEMPORARY_REDIRECT 307
#define MLS_CP_STATUS_PERMANENT_REDIRECT 308

#define MLS_CP_STATUS_BAD_REQUEST 400
#define MLS_CP_STATUS_UNAUTHORIZED 401
#define MLS_CP_STATUS_PAYMENT_REQUIRED 402
#define MLS_CP_STATUS_FORBIDDEN 403
#define MLS_CP_STATUS_NOT_FOUND 404

#define MLS_CP_STATUS_INTERNAL_SERVER_ERROR 500
#define MLS_CP_STATUS_NOT_IMPLEMENTED 501
#define MLS_CP_STATUS_BAD_GATEWAY 502
#define MLS_CP_STATUS_SERVICE_UNAVAILABLE 503
#define MLS_CP_STATUS_GATEWAY_TIMEOUT 504
#define MLS_CP_STATUS_VERSION_NOT_SUPPORTED 505

/*******************************************************************************
 * 基础类型
 */

typedef uint8_t mls_cp_block_size; // 注意: 这个类型必须是 uint8
typedef uint8_t mls_cp_block_type; // 注意: 这个类型必须是 uint8
typedef uint8_t mls_cp_group_id;   // 注意: 这个类型必须是 uint8
typedef uint8_t mls_cp_field_id;   // 注意: 这个类型必须是 uint8

typedef uint32_t mls_cp_transaction_id; // 表示请求事务ID的 uint32
typedef uint8_t mls_cp_method;          // 表示请求方法的 uint8
typedef const char *mls_cp_location;    // 表示请求位置的字符串
typedef uint16_t mls_cp_status_code;    // 表示响应状态 (uint16)

typedef struct mls_cp_version_t
{
    mls_uint8 major;
    mls_uint8 minor;

} mls_cp_version;

// mls_cp_status 表示 mls-cp 响应的状态,
// 它包含以下2个成员:
// - code:uint
// - message:string
typedef struct mls_cp_status_t
{
    mls_cp_status_code code;
    mls_string message;

} mls_cp_status;

typedef struct mls_argb_t
{
    mls_byte a; // alpha
    mls_byte r; // red
    mls_byte g; // green
    mls_byte b; // blue

} mls_argb;

/*******************************************************************************
 * functions
 *  */

mls_string mls_cp_block_type_stringify(mls_cp_block_type b_type);
mls_string mls_cp_group_field_stringify(mls_cp_group_id group, mls_cp_field_id field);
mls_string mls_cp_status_stringify(mls_cp_status_code code);

mls_uint16 mls_cp_version_to_uint16(mls_cp_version *version);

/*******************************************************************************
 * EOF
 *  */

#endif // __mls_cp_base_h__
