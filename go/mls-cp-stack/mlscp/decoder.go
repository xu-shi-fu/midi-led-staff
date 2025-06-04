package mlscp

import (
	"bytes"
	"encoding/binary"
	"fmt"
)

type decoder struct{}

func (inst *decoder) order() binary.ByteOrder {
	return binary.BigEndian // 网络字节序
}

func (inst *decoder) decodeUint8(data []byte) (uint8, error) {
	var value uint8
	order := inst.order()
	src := bytes.NewReader(data)
	err := binary.Read(src, order, &value)
	return value, err
}

func (inst *decoder) decodeUint16(data []byte) (uint16, error) {
	var value uint16
	order := inst.order()
	src := bytes.NewReader(data)
	err := binary.Read(src, order, &value)
	return value, err
}

func (inst *decoder) decodeUint32(data []byte) (uint32, error) {
	var value uint32
	order := inst.order()
	src := bytes.NewReader(data)
	err := binary.Read(src, order, &value)
	return value, err
}

func (inst *decoder) decodeUint64(data []byte) (uint64, error) {
	var value uint64
	order := inst.order()
	src := bytes.NewReader(data)
	err := binary.Read(src, order, &value)
	return value, err
}

func (inst *decoder) decodeInt8(data []byte) (int8, error) {
	var value int8
	order := inst.order()
	src := bytes.NewReader(data)
	err := binary.Read(src, order, &value)
	return value, err
}

func (inst *decoder) decodeInt16(data []byte) (int16, error) {
	var value int16
	order := inst.order()
	src := bytes.NewReader(data)
	err := binary.Read(src, order, &value)
	return value, err
}

func (inst *decoder) decodeInt32(data []byte) (int32, error) {
	var value int32
	order := inst.order()
	src := bytes.NewReader(data)
	err := binary.Read(src, order, &value)
	return value, err
}

func (inst *decoder) decodeInt64(data []byte) (int64, error) {
	var value int64
	order := inst.order()
	src := bytes.NewReader(data)
	err := binary.Read(src, order, &value)
	return value, err
}

func (inst *decoder) decodeFloat32(data []byte) (float32, error) {
	var value float32
	order := inst.order()
	src := bytes.NewReader(data)
	err := binary.Read(src, order, &value)
	return value, err
}

func (inst *decoder) decodeFloat64(data []byte) (float64, error) {
	var value float64
	order := inst.order()
	src := bytes.NewReader(data)
	err := binary.Read(src, order, &value)
	return value, err
}

func (inst *decoder) decodeBoolean(data []byte) (bool, error) {
	return false, fmt.Errorf("no impl")
}

func (inst *decoder) decodeString(data []byte) (string, error) {

	iend := len(data) - 1
	if iend >= 0 {
		if data[iend] == 0 {
			data = data[0:iend]
		}
	}

	str := string(data)
	return str, nil
}

func (inst *decoder) decodeBytes(data []byte) ([]byte, error) {
	return data, nil
}

func (inst *decoder) decodeARGB(data []byte) (ARGB, error) {
	var argb ARGB
	size := len(data)
	if size < 4 {
		return argb, fmt.Errorf("bad size of struct: ARGB")
	}
	argb.A = data[0]
	argb.R = data[1]
	argb.G = data[2]
	argb.B = data[3]
	return argb, nil
}
