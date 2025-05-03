package mlscp

// 基础类型

type BlockSize uint8
type BlockType uint8
type GroupID uint8
type FieldID uint8

// Version 表示协议的版本号, 它通常是一个 16 位的无符号整数, 可拆分为两个 8 位的无符号整数,
// 例如: 0x01 0x02, 表示版本号为 1.2
type Version uint16

// Method 表示一个请求的方法, 它通常是一个 HTTP 方法, 例如 GET, POST, PUT, DELETE 等
type Method uint8

// Location 表示一个请求的目标位置, 它通常是一个绝对路径, 例如 '/test/ping'
type Location string

////////////////////////////////////////////////////////////////////////////////
// 常量

const (
	TypeNoValue BlockType = 0

	TypeUint8  BlockType = 0x01
	TypeUint16 BlockType = 0x02
	TypeUint32 BlockType = 0x03
	TypeUint64 BlockType = 0x04

	TypeInt8  BlockType = 0x11
	TypeInt16 BlockType = 0x12
	TypeInt32 BlockType = 0x13
	TypeInt64 BlockType = 0x14

	TypeFloat32 BlockType = 0x21
	TypeFloat64 BlockType = 0x22

	TypeBoolean BlockType = 0x31
	TypeString  BlockType = 0x32
	TypeBytes   BlockType = 0x33

	TypeARGB BlockType = 0x41
)

const (
	GroupCommon = 0
	GroupSystem = 1
	GroupMIDI   = 2
	GroupLED    = 3

	GroupExMin = 128
	GroupExMax = 255
)

const (
	FieldCommonMethod        = 1 // 请求方法:uint8
	FieldCommonLocation      = 2 // 请求位置:string
	FieldCommonVersion       = 3 // 协议版本:uint16 (8bits_x2)
	FieldCommonStatusCode    = 4 // 状态码:uint16
	FieldCommonStatusMessage = 5 // 状态消息:string
	FieldCommonTransactionID = 6 // 事务ID:uint32
	FieldCommonCheckSum      = 7 // 奇偶校验:uint8
)

const (
	LocationPing Location = "/ping"
)

////////////////////////////////////////////////////////////////////////////////
// 接口

type BlockBody interface {
	Type() BlockType

	Encoded() []byte

	Decode(src []byte) error
}

////////////////////////////////////////////////////////////////////////////////
// 结构

type ARGB struct {
	A uint8 // alpha
	R uint8 // red
	G uint8 // green
	B uint8 // blue
}

type BlockHead struct {
	Size  BlockSize
	Type  BlockType
	Group GroupID
	Field FieldID
}

type BlockEntity struct {
	Head BlockHead
	Body BlockBody
}

////////////////////////////////////////////////////////////////////////////////
// EOF
