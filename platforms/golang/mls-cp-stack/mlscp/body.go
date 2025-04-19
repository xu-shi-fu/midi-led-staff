package mlscp

import "bytes"

var shareEncoder encoder
var shareDecoder decoder

////////////////////////////////////////////////////////////////////////////////
// body:byte

type ByteBody struct {
	Value byte
}

func (inst *ByteBody) _impl() BlockBody {
	return inst
}

func (inst *ByteBody) Type() BlockType {
	return TypeUint8
}

func (inst *ByteBody) Encoded() []byte {
	var buffer bytes.Buffer
	shareEncoder.encodeUint8(inst.Value, &buffer)
	return buffer.Bytes()
}

func (inst *ByteBody) Decode(src []byte) error {
	n, err := shareDecoder.decodeUint8(src)
	if err != nil {
		return err
	}
	inst.Value = n
	return nil
}

////////////////////////////////////////////////////////////////////////////////
// body:byte_array

type ByteArrayBody struct {
	Value []byte
}

func (inst *ByteArrayBody) _impl() BlockBody {
	return inst
}

func (inst *ByteArrayBody) Type() BlockType {
	return TypeBytes
}

func (inst *ByteArrayBody) Encoded() []byte {
	return bytes.Clone(inst.Value)
}

func (inst *ByteArrayBody) Decode(src []byte) error {
	inst.Value = bytes.Clone(src)
	return nil
}

////////////////////////////////////////////////////////////////////////////////
// body:uint8

type Uint8Body struct {
	Value uint8
}

func (inst *Uint8Body) _impl() BlockBody {
	return inst
}

func (inst *Uint8Body) Type() BlockType {
	return TypeUint8
}

func (inst *Uint8Body) Encoded() []byte {
	var buffer bytes.Buffer
	shareEncoder.encodeUint8(inst.Value, &buffer)
	return buffer.Bytes()
}

func (inst *Uint8Body) Decode(src []byte) error {
	n, err := shareDecoder.decodeUint8(src)
	if err != nil {
		return err
	}
	inst.Value = n
	return nil
}

////////////////////////////////////////////////////////////////////////////////
// body:uint16

type Uint16Body struct {
	Value uint16
}

func (inst *Uint16Body) _impl() BlockBody {
	return inst
}

func (inst *Uint16Body) Type() BlockType {
	return TypeUint16
}

func (inst *Uint16Body) Encoded() []byte {
	var buffer bytes.Buffer
	shareEncoder.encodeUint16(inst.Value, &buffer)
	return buffer.Bytes()
}

func (inst *Uint16Body) Decode(src []byte) error {
	n, err := shareDecoder.decodeUint16(src)
	if err != nil {
		return err
	}
	inst.Value = n
	return nil
}

////////////////////////////////////////////////////////////////////////////////
// body:uint32

type Uint32Body struct {
	Value uint32
}

func (inst *Uint32Body) _impl() BlockBody {
	return inst
}

func (inst *Uint32Body) Type() BlockType {
	return TypeUint32
}

func (inst *Uint32Body) Encoded() []byte {
	var buffer bytes.Buffer
	shareEncoder.encodeUint32(inst.Value, &buffer)
	return buffer.Bytes()
}

func (inst *Uint32Body) Decode(src []byte) error {
	n, err := shareDecoder.decodeUint32(src)
	if err != nil {
		return err
	}
	inst.Value = n
	return nil
}

////////////////////////////////////////////////////////////////////////////////
// body:uint64

type Uint64Body struct {
	Value uint64
}

func (inst *Uint64Body) _impl() BlockBody {
	return inst
}

func (inst *Uint64Body) Type() BlockType {
	return TypeUint64
}

func (inst *Uint64Body) Encoded() []byte {
	var buffer bytes.Buffer
	shareEncoder.encodeUint64(inst.Value, &buffer)
	return buffer.Bytes()
}

func (inst *Uint64Body) Decode(src []byte) error {
	n, err := shareDecoder.decodeUint64(src)
	if err != nil {
		return err
	}
	inst.Value = n
	return nil
}

////////////////////////////////////////////////////////////////////////////////
// body:int8

type Int8Body struct {
	Value int8
}

func (inst *Int8Body) _impl() BlockBody {
	return inst
}

func (inst *Int8Body) Type() BlockType {
	return TypeInt8
}

func (inst *Int8Body) Encoded() []byte {
	var buffer bytes.Buffer
	shareEncoder.encodeInt8(inst.Value, &buffer)
	return buffer.Bytes()
}

func (inst *Int8Body) Decode(src []byte) error {
	n, err := shareDecoder.decodeInt8(src)
	if err != nil {
		return err
	}
	inst.Value = n
	return nil
}

////////////////////////////////////////////////////////////////////////////////
// body:int16

////////////////////////////////////////////////////////////////////////////////
// body:int32

////////////////////////////////////////////////////////////////////////////////
// body:int64

////////////////////////////////////////////////////////////////////////////////
// body:xxx
