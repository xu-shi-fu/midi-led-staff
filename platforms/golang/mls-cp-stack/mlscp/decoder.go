package mlscp

import "fmt"

type decoder struct{}

func (inst *decoder) decodeUint8(data []byte) (uint8, error) {
	return 0, fmt.Errorf("no impl")
}

func (inst *decoder) decodeUint16(data []byte) (uint16, error) {
	return 0, fmt.Errorf("no impl")
}

func (inst *decoder) decodeUint32(data []byte) (uint32, error) {
	return 0, fmt.Errorf("no impl")
}

func (inst *decoder) decodeUint64(data []byte) (uint64, error) {
	return 0, fmt.Errorf("no impl")
}

func (inst *decoder) decodeInt8(data []byte) (int8, error) {
	return 0, fmt.Errorf("no impl")
}

func (inst *decoder) decodeInt16(data []byte) (int16, error) {
	return 0, fmt.Errorf("no impl")
}

func (inst *decoder) decodeInt32(data []byte) (int32, error) {
	return 0, fmt.Errorf("no impl")
}

func (inst *decoder) decodeInt64(data []byte) (int64, error) {
	return 0, fmt.Errorf("no impl")
}

func (inst *decoder) decodeFloat(data []byte) (float32, error) {
	return 0, fmt.Errorf("no impl")
}

func (inst *decoder) decodeDouble(data []byte) (float64, error) {
	return 0, fmt.Errorf("no impl")
}

func (inst *decoder) decodeBoolean(data []byte) (bool, error) {
	return false, fmt.Errorf("no impl")
}

func (inst *decoder) decodeString(data []byte) (string, error) {
	return "", fmt.Errorf("no impl")
}

// func (inst * decoder) decodeBytes   ( data [] byte ) ( int , error)  {}
