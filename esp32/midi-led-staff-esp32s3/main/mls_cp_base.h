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
#define MLS_CP_TYPE_ARGB_ARRAY 0x42

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
#define MLS_CP_FIELD_COMMON_END_OF_GROUP 9   // :uint8
#define MLS_CP_FIELD_COMMON_FLUSH 10         // :(NO_VALUE)

// @group:example

#define MLS_CP_FIELD_EXAMPLE_FOO 1 // :string
#define MLS_CP_FIELD_EXAMPLE_BAR 2 // :int32

// @group:test

// @group:LED

#define MLS_CP_FIELD_LED_VIEW_POSITION 1 // :uint8
#define MLS_CP_FIELD_LED_VIEW_SIZE 2     // :uint8
#define MLS_CP_FIELD_LED_PART_ITEMS 3    // :argb[]
#define MLS_CP_FIELD_LED_PART_POSITION 4 // :uint8
#define MLS_CP_FIELD_LED_PART_SIZE 5     // :uint8

/*******************************************************************************
 * group & field
 */

#define MLSCP_GROUP_FIELD(gid, fid) mls_cp_group_field_value_of(gid, fid)

// group:common

#define MLSCP_GF_COMMON_EOP /* ............. */ MLSCP_GROUP_FIELD(MLS_CP_GROUP_COMMON, MLS_CP_FIELD_COMMON_END_OF_PACK) // End of Packet
#define MLSCP_GF_COMMON_METHOD /* .......... */ MLSCP_GROUP_FIELD(MLS_CP_GROUP_COMMON, MLS_CP_FIELD_COMMON_METHOD)
#define MLSCP_GF_COMMON_LOCATION /* ........ */ MLSCP_GROUP_FIELD(MLS_CP_GROUP_COMMON, MLS_CP_FIELD_COMMON_LOCATION)
#define MLSCP_GF_COMMON_VERSION /* ......... */ MLSCP_GROUP_FIELD(MLS_CP_GROUP_COMMON, MLS_CP_FIELD_COMMON_VERSION)
#define MLSCP_GF_COMMON_STATUS_CODE /* ..... */ MLSCP_GROUP_FIELD(MLS_CP_GROUP_COMMON, MLS_CP_FIELD_COMMON_STATUS_CODE)
#define MLSCP_GF_COMMON_STATUS_MSG /* ...... */ MLSCP_GROUP_FIELD(MLS_CP_GROUP_COMMON, MLS_CP_FIELD_COMMON_STATUS_MSG)
#define MLSCP_GF_COMMON_TRANSACTION /* ..... */ MLSCP_GROUP_FIELD(MLS_CP_GROUP_COMMON, MLS_CP_FIELD_COMMON_TRANSACTION_ID)
#define MLSCP_GF_COMMON_TIMESTAMP /* ....... */ MLSCP_GROUP_FIELD(MLS_CP_GROUP_COMMON, MLS_CP_FIELD_COMMON_TIMESTAMP)
#define MLSCP_GF_COMMON_EOG /* ............. */ MLSCP_GROUP_FIELD(MLS_CP_GROUP_COMMON, MLS_CP_FIELD_COMMON_END_OF_GROUP) // End of Group
#define MLSCP_GF_COMMON_FLUSH /* ........... */ MLSCP_GROUP_FIELD(MLS_CP_GROUP_COMMON, MLS_CP_FIELD_COMMON_FLUSH)

// group:led

#define MLSCP_GF_LED_VIEW_POSITION /* ... */ MLSCP_GROUP_FIELD(MLS_CP_GROUP_LED, MLS_CP_FIELD_LED_VIEW_POSITION)
#define MLSCP_GF_LED_VIEW_SIZE /* ....... */ MLSCP_GROUP_FIELD(MLS_CP_GROUP_LED, MLS_CP_FIELD_LED_VIEW_SIZE)
#define MLSCP_GF_LED_PART_ITEMS /* ...... */ MLSCP_GROUP_FIELD(MLS_CP_GROUP_LED, MLS_CP_FIELD_LED_PART_ITEMS)
#define MLSCP_GF_LED_PART_POSITION /* ... */ MLSCP_GROUP_FIELD(MLS_CP_GROUP_LED, MLS_CP_FIELD_LED_PART_POSITION)
#define MLSCP_GF_LED_PART_SIZE /* ....... */ MLSCP_GROUP_FIELD(MLS_CP_GROUP_LED, MLS_CP_FIELD_LED_PART_SIZE)

/*******************************************************************************
 * methods
 */

#define MLS_CP_METHOD_GET 1
#define MLS_CP_METHOD_POST 2
#define MLS_CP_METHOD_PUT 3
#define MLS_CP_METHOD_DELETE 4

/*******************************************************************************
 * locations
 */

#define MLS_CP_LOCATION_EXAMPLE "/example"
#define MLS_CP_LOCATION_FOO_BAR "/foo/bar"
#define MLS_CP_LOCATION_PING "/ping"
#define MLS_CP_LOCATION_LEDS "/leds"
#define MLS_CP_LOCATION_KEYS "/keys"
#define MLS_CP_LOCATION_STYLES "/styles"
#define MLS_CP_LOCATION_SETTINGS "/settings"
#define MLS_CP_LOCATION_MODES "/modes"
#define MLS_CP_LOCATION_MODES_CURRENT "/modes/current"

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

// 注意: 这个结构中的字段顺序是按照 ws2812 的时序 "G-R-B" 排列的
typedef struct mls_rgb_t
{

    mls_byte g; // green
    mls_byte r; // red
    mls_byte b; // blue

} mls_rgb;

/*******************************************************************************
 * functions
 *  */

mls_string mls_cp_block_type_stringify(mls_cp_block_type b_type);
mls_string mls_cp_group_field_stringify(mls_cp_group_id group, mls_cp_field_id field);
mls_string mls_cp_status_stringify(mls_cp_status_code code);

mls_uint16 mls_cp_version_to_uint16(mls_cp_version *version);
mls_cp_version mls_cp_version_impl(); // 获取当前实现的协议版本

void mls_argb_to_rgb(mls_argb *src, mls_rgb *dest);
void mls_rgb_to_argb(mls_rgb *src, mls_argb *dest);

mls_argb mls_argb_color(int a, int r, int g, int b);
mls_argb mls_argb_red();
mls_argb mls_argb_green();
mls_argb mls_argb_blue();
mls_argb mls_argb_orange();
mls_argb mls_argb_yellow();
mls_argb mls_argb_azure();
mls_argb mls_argb_purple();
mls_argb mls_argb_white();
mls_argb mls_argb_black();

/*******************************************************************************
 * EOF
 *  */

#endif // __mls_cp_base_h__
