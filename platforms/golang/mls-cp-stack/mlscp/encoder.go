package mlscp

import "bytes"

type encoder struct {
}

func (inst *encoder) encodeUint8(value uint8, dst *bytes.Buffer) {
	dst.WriteByte(byte(value))
}

func (inst *encoder) encodeUint16(value uint16, dst *bytes.Buffer) {}
func (inst *encoder) encodeUint32(value uint32, dst *bytes.Buffer) {}
func (inst *encoder) encodeUint64(value uint64, dst *bytes.Buffer) {}

func (inst *encoder) encodeInt8(value int8, dst *bytes.Buffer) {
	dst.WriteByte(byte(value))
}

func (inst *encoder) encodeInt16(value int16, dst *bytes.Buffer) {}
func (inst *encoder) encodeInt32(value int32, dst *bytes.Buffer) {}
func (inst *encoder) encodeInt64(value int64, dst *bytes.Buffer) {}

func (inst *encoder) encodeFloat(value float32, dst *bytes.Buffer)  {}
func (inst *encoder) encodeDouble(value float64, dst *bytes.Buffer) {}

func (inst *encoder) encodeBoolean(value bool, dst *bytes.Buffer)  {}
func (inst *encoder) encodeString(value string, dst *bytes.Buffer) {}
func (inst *encoder) encodeBytes(value []byte, dst *bytes.Buffer)  {}
