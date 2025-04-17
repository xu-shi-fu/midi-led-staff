package mlscp

import "bytes"

type encoder struct {
	buffer bytes.Buffer
}

func (inst *encoder) reset() {}

func (inst *encoder) result() []byte {
	panic("no impl")
}

func (inst *encoder) encodeUint8(value uint8) {
	inst.buffer.WriteByte(byte(value))
}

func (inst *encoder) encodeUint16(value uint16) {}
func (inst *encoder) encodeUint32(value uint32) {}
func (inst *encoder) encodeUint64(value uint64) {}

func (inst *encoder) encodeInt8(value int8) {
	inst.buffer.WriteByte(byte(value))
}

func (inst *encoder) encodeInt16(value int16) {}
func (inst *encoder) encodeInt32(value int32) {}
func (inst *encoder) encodeInt64(value int64) {}

func (inst *encoder) encodeFloat(value float32)  {}
func (inst *encoder) encodeDouble(value float64) {}

func (inst *encoder) encodeBoolean(value bool)  {}
func (inst *encoder) encodeString(value string) {}
func (inst *encoder) encodeBytes(value []byte)  {}
