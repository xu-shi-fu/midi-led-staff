// mls_cp_base.h

#ifndef __mls_cp_base_h__
#define __mls_cp_base_h__

#include "mls_api.h"
#include "mls_common.h"
#include "mls_buffer.h"
#include "mls_errors.h"

/*******************************************************************************
 * 宏
 */

// types

#define MLS_CP_TYPE_NO_VALUE 0

#define MLS_CP_TYPE_UINT8 0x01
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

#define MLS_CP_TYPE_ARGB 0x41

// groups

#define MLS_CP_GROUP_COMMON 0
#define MLS_CP_GROUP_SYSTEM 1
#define MLS_CP_GROUP_MIDI 2
#define MLS_CP_GROUP_LED 3

// fields:COMMON

#define MLS_CP_FIELD_COMMON_END_OF_PACK 0
#define MLS_CP_FIELD_COMMON_METHOD 1
#define MLS_CP_FIELD_COMMON_ACTION 2

/*******************************************************************************
 * 基础类型
 */

typedef uint8_t mls_cp_block_size; // 注意: 这个类型必须是 uint8
typedef uint8_t mls_cp_block_type; // 注意: 这个类型必须是 uint8
typedef uint8_t mls_cp_group_id;   // 注意: 这个类型必须是 uint8
typedef uint8_t mls_cp_field_id;   // 注意: 这个类型必须是 uint8

/*******************************************************************************
 * EOF
 *  */

#endif // __mls_cp_base_h__
