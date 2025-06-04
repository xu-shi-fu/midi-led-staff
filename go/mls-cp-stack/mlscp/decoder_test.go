package mlscp

import (
	"fmt"
	"reflect"
	"testing"
)

type decoderUnit struct {
	decoder decoder
}

func (inst *decoderUnit) checkResult(value any, data []byte, err error) {
	if err != nil {
		panic(err)
	}
	t := reflect.TypeOf(value)
	fmt.Printf("decoderUnit.checkResult(ok) type:%v value:%v  data:%v \n", t.Name(), value, data)
}

func (inst *decoderUnit) tryInt8(buf []byte) {
	dec := &inst.decoder
	value, err := dec.decodeInt8(buf)
	inst.checkResult(value, buf, err)
}

func (inst *decoderUnit) tryInt16(buf []byte) {
	dec := &inst.decoder
	value, err := dec.decodeInt16(buf)
	inst.checkResult(value, buf, err)
}

func (inst *decoderUnit) tryInt32(buf []byte) {
	dec := &inst.decoder
	value, err := dec.decodeInt32(buf)
	inst.checkResult(value, buf, err)
}

func (inst *decoderUnit) tryInt64(buf []byte) {
	dec := &inst.decoder
	value, err := dec.decodeInt64(buf)
	inst.checkResult(value, buf, err)
}

func (inst *decoderUnit) tryUint8(buf []byte) {
	dec := &inst.decoder
	value, err := dec.decodeUint8(buf)
	inst.checkResult(value, buf, err)
}

func (inst *decoderUnit) tryUint16(buf []byte) {
	dec := &inst.decoder
	value, err := dec.decodeUint16(buf)
	inst.checkResult(value, buf, err)
}

func (inst *decoderUnit) tryUint32(buf []byte) {
	dec := &inst.decoder
	value, err := dec.decodeUint32(buf)
	inst.checkResult(value, buf, err)
}

func (inst *decoderUnit) tryUint64(buf []byte) {
	dec := &inst.decoder
	value, err := dec.decodeUint64(buf)
	inst.checkResult(value, buf, err)
}

func (inst *decoderUnit) tryFloat32(buf []byte) {
	dec := &inst.decoder
	value, err := dec.decodeFloat32(buf)
	inst.checkResult(value, buf, err)
}

func (inst *decoderUnit) tryFloat64(buf []byte) {
	dec := &inst.decoder
	value, err := dec.decodeFloat64(buf)
	inst.checkResult(value, buf, err)
}

func (inst *decoderUnit) tryString(buf []byte) {
	dec := &inst.decoder
	value, err := dec.decodeString(buf)
	inst.checkResult(value, buf, err)
}

func (inst *decoderUnit) tryBytes(buf []byte) {
	dec := &inst.decoder
	value, err := dec.decodeBytes(buf)
	inst.checkResult(value, buf, err)
}

////////////////////////////////////////////////////////////////////////////////

func TestDecoder(t *testing.T) {

	unit := &decoderUnit{}

	unit.tryInt8([]byte{0, 1, 2})
	unit.tryInt16([]byte{0, 1, 2})
	unit.tryInt32([]byte{0xaf, 1, 2, 3})
	unit.tryInt64([]byte{0, 1, 2, 3, 4, 5, 6, 7})

	unit.tryUint8([]byte{0, 1, 2})
	unit.tryUint16([]byte{0, 1, 2})
	unit.tryUint32([]byte{0, 1, 2, 3})
	unit.tryUint64([]byte{0, 1, 2, 3, 4, 5, 6, 7})

	unit.tryFloat32([]byte{0, 1, 2, 3})
	unit.tryFloat64([]byte{0, 1, 2, 3, 4, 5, 6, 7})

	unit.tryString([]byte{0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57})
	unit.tryBytes([]byte{0, 1, 2, 3, 4, 5, 6, 7})

}
