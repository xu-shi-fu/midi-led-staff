package mlscp

import (
	"bytes"
	"fmt"
	"reflect"
	"testing"
)

type encoderUnit struct {
	encoder encoder
	buffer  bytes.Buffer
}

func (inst *encoderUnit) checkResult(value any, buffer *bytes.Buffer, err error) {
	if err != nil {
		panic(err)
	}
	data := buffer.Bytes()
	t := reflect.TypeOf(value)
	fmt.Printf("checkResult(ok) type:%v value:%v  data:%v \n", t.Name(), value, data)
	buffer.Reset()
}

func (inst *encoderUnit) tryInt16(value int16) {
	buf := &inst.buffer
	enc := &inst.encoder
	err := enc.encodeInt16(value, buf)
	inst.checkResult(value, buf, err)
}

func (inst *encoderUnit) tryUint8(value uint8) {
	buf := &inst.buffer
	enc := &inst.encoder
	err := enc.encodeUint8(value, buf)
	inst.checkResult(value, buf, err)
}
func (inst *encoderUnit) tryInt8(value int8) {
	buf := &inst.buffer
	enc := &inst.encoder
	err := enc.encodeInt8(value, buf)
	inst.checkResult(value, buf, err)
}
func (inst *encoderUnit) tryInt32(value int32) {
	buf := &inst.buffer
	enc := &inst.encoder
	err := enc.encodeInt32(value, buf)
	inst.checkResult(value, buf, err)
}
func (inst *encoderUnit) tryInt64(value int64) {
	buf := &inst.buffer
	enc := &inst.encoder
	err := enc.encodeInt64(value, buf)
	inst.checkResult(value, buf, err)
}
func (inst *encoderUnit) tryUint32(value uint32) {
	buf := &inst.buffer
	enc := &inst.encoder
	err := enc.encodeUint32(value, buf)
	inst.checkResult(value, buf, err)
}
func (inst *encoderUnit) tryUint64(value uint64) {
	buf := &inst.buffer
	enc := &inst.encoder
	err := enc.encodeUint64(value, buf)
	inst.checkResult(value, buf, err)
}

func (inst *encoderUnit) tryUint16(value uint16) {
	buf := &inst.buffer
	enc := &inst.encoder
	err := enc.encodeUint16(value, buf)
	inst.checkResult(value, buf, err)
}

func (inst *encoderUnit) tryFloat32(value float32) {
	buf := &inst.buffer
	enc := &inst.encoder
	err := enc.encodeFloat(value, buf)
	inst.checkResult(value, buf, err)
}

func (inst *encoderUnit) tryFloat64(value float64) {
	buf := &inst.buffer
	enc := &inst.encoder
	err := enc.encodeDouble(value, buf)
	inst.checkResult(value, buf, err)
}

////////////////////////////////////////////////////////////////////////////////

func TestEncoder(t *testing.T) {

	unit := &encoderUnit{}

	unit.tryInt8(120)
	unit.tryInt16(768)
	unit.tryInt32(32000)
	unit.tryInt64(32000)

	unit.tryUint8(250)
	unit.tryUint16(10217)
	unit.tryUint32(32000)
	unit.tryUint64(32000)

	unit.tryFloat32(3.14)
	unit.tryFloat64(3.14159265358979323846)

}
