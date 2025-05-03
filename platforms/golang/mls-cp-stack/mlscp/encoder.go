package mlscp

import (
	"bytes"
	"encoding/binary"
)

type encoder struct {
}

func (inst *encoder) order() binary.ByteOrder {
	return binary.BigEndian // 网络字节序
}

func (inst *encoder) encodeUint8(value uint8, dst *bytes.Buffer) error {
	order := inst.order()
	return binary.Write(dst, order, value)
}

func (inst *encoder) encodeUint16(value uint16, dst *bytes.Buffer) error {
	order := inst.order()
	return binary.Write(dst, order, value)
}

func (inst *encoder) encodeUint32(value uint32, dst *bytes.Buffer) error {
	order := inst.order()
	return binary.Write(dst, order, value)
}

func (inst *encoder) encodeUint64(value uint64, dst *bytes.Buffer) error {
	order := inst.order()
	return binary.Write(dst, order, value)
}

func (inst *encoder) encodeInt8(value int8, dst *bytes.Buffer) error {
	order := inst.order()
	return binary.Write(dst, order, value)
}

func (inst *encoder) encodeInt16(value int16, dst *bytes.Buffer) error {
	order := inst.order()
	return binary.Write(dst, order, value)
}

func (inst *encoder) encodeInt32(value int32, dst *bytes.Buffer) error {
	order := inst.order()
	return binary.Write(dst, order, value)
}

func (inst *encoder) encodeInt64(value int64, dst *bytes.Buffer) error {
	order := inst.order()
	return binary.Write(dst, order, value)
}

func (inst *encoder) encodeFloat(value float32, dst *bytes.Buffer) error {
	order := inst.order()
	return binary.Write(dst, order, value)
}

func (inst *encoder) encodeDouble(value float64, dst *bytes.Buffer) error {
	order := inst.order()
	return binary.Write(dst, order, value)
}

func (inst *encoder) encodeBoolean(value bool, dst *bytes.Buffer) error {
	order := inst.order()
	return binary.Write(dst, order, value)
}

func (inst *encoder) encodeString(strData []byte, dst *bytes.Buffer) error {
	_, err := dst.Write(strData)
	return err
}

func (inst *encoder) encodeBytes(value []byte, dst *bytes.Buffer) error {
	_, err := dst.Write(value)
	return err
}

func (inst *encoder) encodeARGB(value ARGB, dst *bytes.Buffer) error {
	dst.WriteByte(value.A)
	dst.WriteByte(value.R)
	dst.WriteByte(value.G)
	dst.WriteByte(value.B)
	return nil
}

func (inst *encoder) encodeBlockHead(value BlockHead, dst *bytes.Buffer) error {
	dst.WriteByte(byte(value.Size))
	dst.WriteByte(byte(value.Type))
	dst.WriteByte(byte(value.Group))
	dst.WriteByte(byte(value.Field))
	return nil
}
