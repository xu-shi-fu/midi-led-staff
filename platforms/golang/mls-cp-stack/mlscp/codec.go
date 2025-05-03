package mlscp

import (
	"bytes"
	"fmt"
)

////////////////////////////////////////////////////////////////////////////////
// Encoder

type encodingFunction func(*BlockEntity, *bytes.Buffer) error

type Encoder struct {
	inner                 encoder
	encodingFunctionTable map[BlockType]encodingFunction
}

func (inst *Encoder) initEncodingFunctionTable(table map[BlockType]encodingFunction) {
	// types:

	table[TypeUint8] = inst.encodeUint8
	table[TypeUint16] = inst.encodeUint16
	table[TypeUint32] = inst.encodeUint32
	table[TypeUint64] = inst.encodeUint64

	table[TypeInt8] = inst.encodeInt8
	table[TypeInt16] = inst.encodeInt16
	table[TypeInt32] = inst.encodeInt32
	table[TypeInt64] = inst.encodeInt64

	table[TypeFloat32] = inst.encodeFloat32
	table[TypeFloat64] = inst.encodeFloat64

	table[TypeString] = inst.encodeString
	table[TypeBytes] = inst.encodeBytes
	table[TypeBoolean] = inst.encodeBoolean

	table[TypeARGB] = inst.encodeARGB
}

func (inst *Encoder) getEncodingFunctionTable() map[BlockType]encodingFunction {
	table := inst.encodingFunctionTable
	if table == nil {
		table = make(map[BlockType]encodingFunction)
		inst.initEncodingFunctionTable(table)
		inst.encodingFunctionTable = table
	}
	return table
}

func (inst *Encoder) encodeUint8(b *BlockEntity, dst *bytes.Buffer) error {

	const bodySize = 1
	head := &b.Head
	inst.encodeBlockHead(head, bodySize, dst)

	body := b.Body.(*BodyUint8)
	return inst.inner.encodeUint8(body.Value, dst)
}
func (inst *Encoder) encodeUint16(b *BlockEntity, dst *bytes.Buffer) error {

	const bodySize = 2
	head := &b.Head
	inst.encodeBlockHead(head, bodySize, dst)

	body := b.Body.(*BodyUint16)
	return inst.inner.encodeUint16(body.Value, dst)
}
func (inst *Encoder) encodeUint32(b *BlockEntity, dst *bytes.Buffer) error {

	const bodySize = 4
	head := &b.Head
	inst.encodeBlockHead(head, bodySize, dst)

	body := b.Body.(*BodyUint32)
	return inst.inner.encodeUint32(body.Value, dst)
}
func (inst *Encoder) encodeUint64(b *BlockEntity, dst *bytes.Buffer) error {

	const bodySize = 8
	head := &b.Head
	inst.encodeBlockHead(head, bodySize, dst)

	body := b.Body.(*BodyUint64)
	return inst.inner.encodeUint64(body.Value, dst)
}

func (inst *Encoder) encodeInt8(b *BlockEntity, dst *bytes.Buffer) error {

	const bodySize = 1
	head := &b.Head
	inst.encodeBlockHead(head, bodySize, dst)

	body := b.Body.(*BodyInt8)
	return inst.inner.encodeInt8(body.Value, dst)
}
func (inst *Encoder) encodeInt16(b *BlockEntity, dst *bytes.Buffer) error {

	const bodySize = 2
	head := &b.Head
	inst.encodeBlockHead(head, bodySize, dst)

	body := b.Body.(*BodyInt16)
	return inst.inner.encodeInt16(body.Value, dst)
}
func (inst *Encoder) encodeInt32(b *BlockEntity, dst *bytes.Buffer) error {

	const bodySize = 4
	head := &b.Head
	inst.encodeBlockHead(head, bodySize, dst)

	body := b.Body.(*BodyInt32)
	return inst.inner.encodeInt32(body.Value, dst)
}
func (inst *Encoder) encodeInt64(b *BlockEntity, dst *bytes.Buffer) error {

	const bodySize = 8
	head := &b.Head
	inst.encodeBlockHead(head, bodySize, dst)

	body := b.Body.(*BodyInt64)
	return inst.inner.encodeInt64(body.Value, dst)
}

func (inst *Encoder) encodeFloat32(b *BlockEntity, dst *bytes.Buffer) error {

	const bodySize = 4
	head := &b.Head
	inst.encodeBlockHead(head, bodySize, dst)

	body := b.Body.(*BodyFloat32)
	return inst.inner.encodeFloat(body.Value, dst)
}

func (inst *Encoder) encodeFloat64(b *BlockEntity, dst *bytes.Buffer) error {

	const bodySize = 8
	head := &b.Head
	inst.encodeBlockHead(head, bodySize, dst)

	body := b.Body.(*BodyFloat64)
	return inst.inner.encodeDouble(body.Value, dst)
}

func (inst *Encoder) encodeString(b *BlockEntity, dst *bytes.Buffer) error {

	head := &b.Head
	body := b.Body.(*BodyString)
	str := body.Value
	data := []byte(str)

	bodySize := len(data)
	inst.encodeBlockHead(head, bodySize, dst)

	return inst.inner.encodeString(data, dst)
}

func (inst *Encoder) encodeBytes(b *BlockEntity, dst *bytes.Buffer) error {

	head := &b.Head
	body := b.Body.(*BodyBytes)

	bodySize := len(body.Value)
	inst.encodeBlockHead(head, bodySize, dst)

	return inst.inner.encodeBytes(body.Value, dst)
}

func (inst *Encoder) encodeBoolean(b *BlockEntity, dst *bytes.Buffer) error {

	const bodySize = 1
	head := &b.Head
	inst.encodeBlockHead(head, bodySize, dst)

	body := b.Body.(*BodyBoolean)
	return inst.inner.encodeBoolean(body.Value, dst)
}

func (inst *Encoder) encodeARGB(b *BlockEntity, dst *bytes.Buffer) error {

	const bodySize = 4
	head := &b.Head
	inst.encodeBlockHead(head, bodySize, dst)

	body := b.Body.(*BodyARGB)
	return inst.inner.encodeARGB(body.Value, dst)
}

func (inst *Encoder) encodeBlockHead(head *BlockHead, bodySize int, dst *bytes.Buffer) error {

	// check: body-size [0,250]
	if bodySize < 0 {
		return fmt.Errorf("bad block-body-size: %d", bodySize)
	}
	if bodySize > 250 {
		return fmt.Errorf("bad block-body-size: %d", bodySize)
	}

	const headSize = 4
	head.Size = headSize + BlockSize(bodySize)
	return inst.inner.encodeBlockHead(*head, dst)
}

func (inst *Encoder) EncodeBlock(b *BlockEntity, dst *bytes.Buffer) error {
	bt := b.Head.Type
	table := inst.getEncodingFunctionTable()
	fn, ok := table[bt]
	if !ok {
		return fmt.Errorf("ErrUnsupportedBlockType:%d", bt)
	}
	return fn(b, dst)
}

func (inst *Encoder) EncodeBlockList(list []*BlockEntity) ([]byte, error) {
	builder := bytes.NewBuffer(nil)
	for _, item := range list {
		err := inst.EncodeBlock(item, builder)
		if err != nil {
			return nil, err
		}
	}
	return builder.Bytes(), nil
}

func (inst *Encoder) EncodeRequest(req *Request) ([]byte, error) {

	method := inst.makeBlockOfRequestMethod(req.Method)
	location := inst.makeBlockOfRequestLocation(req.Location)
	tid := inst.makeBlockOfRequestTID(req.Context.TransactionID)
	ver := inst.makeBlockOfRequestVersion(req.Version)

	all := req.Blocks

	all = append(all, method)
	all = append(all, tid)
	all = append(all, location)
	all = append(all, ver)

	return inst.EncodeBlockList(all)
}

func (inst *Encoder) makeBlockOfRequestVersion(value Version) *BlockEntity {

	body := &BodyUint16{}
	body.Value = uint16(value)

	entity := &BlockEntity{}
	entity.Head.Size = 0
	entity.Head.Type = TypeUint16
	entity.Head.Group = GroupCommon
	entity.Head.Field = FieldCommonVersion
	entity.Body = body

	return entity
}

func (inst *Encoder) makeBlockOfRequestMethod(value Method) *BlockEntity {

	body := &BodyUint8{}
	body.Value = uint8(value)

	entity := &BlockEntity{}
	entity.Head.Size = 0
	entity.Head.Type = TypeUint8
	entity.Head.Group = GroupCommon
	entity.Head.Field = FieldCommonMethod
	entity.Body = body

	return entity
}

func (inst *Encoder) makeBlockOfRequestLocation(value Location) *BlockEntity {

	body := &BodyString{}
	body.Value = string(value)

	entity := &BlockEntity{}
	entity.Head.Size = 0
	entity.Head.Type = TypeString
	entity.Head.Group = GroupCommon
	entity.Head.Field = FieldCommonLocation
	entity.Body = body

	return entity
}

func (inst *Encoder) makeBlockOfRequestTID(value TransactionID) *BlockEntity {

	body := &BodyUint32{}
	body.Value = uint32(value)

	entity := &BlockEntity{}
	entity.Head.Size = 0
	entity.Head.Type = TypeUint32
	entity.Head.Group = GroupCommon
	entity.Head.Field = FieldCommonTransactionID
	entity.Body = body

	return entity
}

////////////////////////////////////////////////////////////////////////////////
// Decoder

type Decoder struct{}

func (inst *Decoder) DecodeBlock(data []byte) (*BlockEntity, error) {
	return nil, fmt.Errorf("no impl")
}

func (inst *Decoder) DecodeBlockList(data []byte) ([]*BlockEntity, error) {
	return nil, fmt.Errorf("no impl")
}

func (inst *Decoder) DecodeResponse(data []byte, dst *Response) (*Response, error) {
	return nil, fmt.Errorf("no impl")
}

////////////////////////////////////////////////////////////////////////////////
// EOF
