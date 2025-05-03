package mlscp

import "bytes"

var shareEncoder encoder
var shareDecoder decoder

////////////////////////////////////////////////////////////////////////////////
// body:byte

// BodyByte 表示 byte 类型的 BlockBody
type BodyByte struct {
	Value byte
}

func (inst *BodyByte) _impl() BlockBody {
	return inst
}

func (inst *BodyByte) Type() BlockType {
	return TypeUint8
}

func (inst *BodyByte) Encoded() []byte {
	var buffer bytes.Buffer
	shareEncoder.encodeUint8(inst.Value, &buffer)
	return buffer.Bytes()
}

func (inst *BodyByte) Decode(src []byte) error {
	n, err := shareDecoder.decodeUint8(src)
	if err != nil {
		return err
	}
	inst.Value = n
	return nil
}

////////////////////////////////////////////////////////////////////////////////
// body:bytes

// BodyBytes 表示 byte 数组类型的 BlockBody
type BodyBytes struct {
	Value []byte
}

func (inst *BodyBytes) _impl() BlockBody {
	return inst
}

func (inst *BodyBytes) Type() BlockType {
	return TypeBytes
}

func (inst *BodyBytes) Encoded() []byte {
	return bytes.Clone(inst.Value)
}

func (inst *BodyBytes) Decode(src []byte) error {
	inst.Value = bytes.Clone(src)
	return nil
}

////////////////////////////////////////////////////////////////////////////////
// body:uint8

// BodyUint8 表示 uint8 类型的 BlockBody
type BodyUint8 struct {
	Value uint8
}

func (inst *BodyUint8) _impl() BlockBody {
	return inst
}

func (inst *BodyUint8) Type() BlockType {
	return TypeUint8
}

func (inst *BodyUint8) Encoded() []byte {
	var buffer bytes.Buffer
	shareEncoder.encodeUint8(inst.Value, &buffer)
	return buffer.Bytes()
}

func (inst *BodyUint8) Decode(src []byte) error {
	n, err := shareDecoder.decodeUint8(src)
	if err != nil {
		return err
	}
	inst.Value = n
	return nil
}

////////////////////////////////////////////////////////////////////////////////
// body:uint16

// BodyUint16 表示 uint16 类型的 BlockBody
type BodyUint16 struct {
	Value uint16
}

func (inst *BodyUint16) _impl() BlockBody {
	return inst
}

func (inst *BodyUint16) Type() BlockType {
	return TypeUint16
}

func (inst *BodyUint16) Encoded() []byte {
	var buffer bytes.Buffer
	shareEncoder.encodeUint16(inst.Value, &buffer)
	return buffer.Bytes()
}

func (inst *BodyUint16) Decode(src []byte) error {
	n, err := shareDecoder.decodeUint16(src)
	if err != nil {
		return err
	}
	inst.Value = n
	return nil
}

////////////////////////////////////////////////////////////////////////////////
// body:uint32

// BodyUint32 表示 uint32 类型的 BlockBody
type BodyUint32 struct {
	Value uint32
}

func (inst *BodyUint32) _impl() BlockBody {
	return inst
}

func (inst *BodyUint32) Type() BlockType {
	return TypeUint32
}

func (inst *BodyUint32) Encoded() []byte {
	var buffer bytes.Buffer
	shareEncoder.encodeUint32(inst.Value, &buffer)
	return buffer.Bytes()
}

func (inst *BodyUint32) Decode(src []byte) error {
	n, err := shareDecoder.decodeUint32(src)
	if err != nil {
		return err
	}
	inst.Value = n
	return nil
}

////////////////////////////////////////////////////////////////////////////////
// body:uint64

// BodyUint64 表示 uint64 类型的 BlockBody
type BodyUint64 struct {
	Value uint64
}

func (inst *BodyUint64) _impl() BlockBody {
	return inst
}

func (inst *BodyUint64) Type() BlockType {
	return TypeUint64
}

func (inst *BodyUint64) Encoded() []byte {
	var buffer bytes.Buffer
	shareEncoder.encodeUint64(inst.Value, &buffer)
	return buffer.Bytes()
}

func (inst *BodyUint64) Decode(src []byte) error {
	n, err := shareDecoder.decodeUint64(src)
	if err != nil {
		return err
	}
	inst.Value = n
	return nil
}

////////////////////////////////////////////////////////////////////////////////
// body:int8

// BodyInt8 表示 int8 类型的 BlockBody
type BodyInt8 struct {
	Value int8
}

func (inst *BodyInt8) _impl() BlockBody {
	return inst
}

func (inst *BodyInt8) Type() BlockType {
	return TypeInt8
}

func (inst *BodyInt8) Encoded() []byte {
	var buffer bytes.Buffer
	shareEncoder.encodeInt8(inst.Value, &buffer)
	return buffer.Bytes()
}

func (inst *BodyInt8) Decode(src []byte) error {
	n, err := shareDecoder.decodeInt8(src)
	if err != nil {
		return err
	}
	inst.Value = n
	return nil
}

////////////////////////////////////////////////////////////////////////////////
// body:int16

// BodyInt16 表示 int16 类型的 BlockBody
type BodyInt16 struct {
	Value int16
}

func (inst *BodyInt16) _impl() BlockBody {
	return inst
}
func (inst *BodyInt16) Type() BlockType {
	return TypeInt16
}
func (inst *BodyInt16) Encoded() []byte {
	var buffer bytes.Buffer
	shareEncoder.encodeInt16(inst.Value, &buffer)
	return buffer.Bytes()
}
func (inst *BodyInt16) Decode(src []byte) error {
	n, err := shareDecoder.decodeInt16(src)
	if err != nil {
		return err
	}
	inst.Value = n
	return nil
}

////////////////////////////////////////////////////////////////////////////////
// body:int32

// BodyInt32 表示 int32 类型的 BlockBody
type BodyInt32 struct {
	Value int32
}

func (inst *BodyInt32) _impl() BlockBody {
	return inst
}
func (inst *BodyInt32) Type() BlockType {
	return TypeInt32
}
func (inst *BodyInt32) Encoded() []byte {
	var buffer bytes.Buffer
	shareEncoder.encodeInt32(inst.Value, &buffer)
	return buffer.Bytes()
}
func (inst *BodyInt32) Decode(src []byte) error {
	n, err := shareDecoder.decodeInt32(src)
	if err != nil {
		return err
	}
	inst.Value = n
	return nil
}

////////////////////////////////////////////////////////////////////////////////
// body:int64

// BodyInt64 表示 int64 类型的 BlockBody
type BodyInt64 struct {
	Value int64
}

func (inst *BodyInt64) _impl() BlockBody {
	return inst
}
func (inst *BodyInt64) Type() BlockType {
	return TypeInt64
}
func (inst *BodyInt64) Encoded() []byte {
	var buffer bytes.Buffer
	shareEncoder.encodeInt64(inst.Value, &buffer)
	return buffer.Bytes()
}
func (inst *BodyInt64) Decode(src []byte) error {
	n, err := shareDecoder.decodeInt64(src)
	if err != nil {
		return err
	}
	inst.Value = n
	return nil
}

////////////////////////////////////////////////////////////////////////////////
// body:float

// BodyFloat32 表示 float32 类型的 BlockBody
type BodyFloat32 struct {
	Value float32
}

func (inst *BodyFloat32) _impl() BlockBody {
	return inst
}
func (inst *BodyFloat32) Type() BlockType {
	return TypeFloat32
}
func (inst *BodyFloat32) Encoded() []byte {
	var buffer bytes.Buffer
	shareEncoder.encodeFloat(inst.Value, &buffer)
	return buffer.Bytes()
}
func (inst *BodyFloat32) Decode(src []byte) error {
	n, err := shareDecoder.decodeFloat32(src)
	if err != nil {
		return err
	}
	inst.Value = n
	return nil
}

////////////////////////////////////////////////////////////////////////////////
// body:double

// BodyFloat64 表示 float64 类型的 BlockBody
type BodyFloat64 struct {
	Value float64
}

func (inst *BodyFloat64) _impl() BlockBody {
	return inst
}
func (inst *BodyFloat64) Type() BlockType {
	return TypeFloat64
}
func (inst *BodyFloat64) Encoded() []byte {
	var buffer bytes.Buffer
	shareEncoder.encodeDouble(inst.Value, &buffer)
	return buffer.Bytes()
}
func (inst *BodyFloat64) Decode(src []byte) error {
	n, err := shareDecoder.decodeFloat64(src)
	if err != nil {
		return err
	}
	inst.Value = n
	return nil
}

////////////////////////////////////////////////////////////////////////////////
// body:boolean

// BodyBoolean 表示 bool 类型的 BlockBody
type BodyBoolean struct {
	Value bool
}

func (inst *BodyBoolean) _impl() BlockBody {
	return inst
}
func (inst *BodyBoolean) Type() BlockType {
	return TypeBoolean
}
func (inst *BodyBoolean) Encoded() []byte {
	var buffer bytes.Buffer
	shareEncoder.encodeBoolean(inst.Value, &buffer)
	return buffer.Bytes()
}
func (inst *BodyBoolean) Decode(src []byte) error {
	n, err := shareDecoder.decodeBoolean(src)
	if err != nil {
		return err
	}
	inst.Value = n
	return nil
}

////////////////////////////////////////////////////////////////////////////////
// body:string

// BodyString 表示 string 类型的 BlockBody
type BodyString struct {
	Value string
}

func (inst *BodyString) _impl() BlockBody {
	return inst
}

func (inst *BodyString) Type() BlockType {
	return TypeString
}

func (inst *BodyString) Encoded() []byte {
	var buffer bytes.Buffer
	data := []byte(inst.Value)
	shareEncoder.encodeString(data, &buffer)
	return buffer.Bytes()
}

func (inst *BodyString) Decode(src []byte) error {
	n, err := shareDecoder.decodeString(src)
	if err != nil {
		return err
	}
	inst.Value = n
	return nil
}

////////////////////////////////////////////////////////////////////////////////
// body:argb

// BodyARGB 表示 string 类型的 BlockBody
type BodyARGB struct {
	Value ARGB
}

func (inst *BodyARGB) _impl() BlockBody {
	return inst
}

func (inst *BodyARGB) Type() BlockType {
	return TypeARGB
}

func (inst *BodyARGB) Encoded() []byte {
	var buffer bytes.Buffer
	shareEncoder.encodeARGB(inst.Value, &buffer)
	return buffer.Bytes()
}

func (inst *BodyARGB) Decode(src []byte) error {
	value, err := shareDecoder.decodeARGB(src)
	if err != nil {
		return err
	}
	inst.Value = value
	return nil
}

////////////////////////////////////////////////////////////////////////////////
// EOF
