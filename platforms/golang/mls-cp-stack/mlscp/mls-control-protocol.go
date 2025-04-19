package mlscp

// 基础类型

type BlockSize uint8
type BlockType uint8
type GroupID uint8
type FieldID uint8

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

	TypeFloat  BlockType = 0x21
	TypeDouble BlockType = 0x22

	TypeBoolean BlockType = 0x31
	TypeString  BlockType = 0x32
	TypeBytes   BlockType = 0x33

	TypeARGB BlockType = 0x41
)

// 接口

type BlockBody interface {
	Type() BlockType

	Encoded() []byte

	Decode(src []byte) error
}

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
