package mlscp

type PackBuilder struct {
	blocks  []*BlockEntity
	current BlockHead
}

func (inst *PackBuilder) Build() []*BlockEntity {
	res := inst.blocks
	inst.blocks = nil
	if res == nil {
		res = make([]*BlockEntity, 0)
	}
	return res
}

func (inst *PackBuilder) WithGroup(id GroupID) *PackBuilder {
	inst.current.Group = id
	return inst
}

func (inst *PackBuilder) WithField(id FieldID) *PackBuilder {
	inst.current.Field = id
	return inst
}

func (inst *PackBuilder) innerAdd(body BlockBody) *PackBuilder {
	item := &BlockEntity{}
	item.Head = inst.current
	item.Head.Type = body.Type()
	item.Head.Size = 0 // 暂时不需要设置
	item.Body = body
	return inst.AddEntity(item)
}

func (inst *PackBuilder) AddUint8(n uint8) *PackBuilder {
	body := &Uint8Body{
		Value: n,
	}
	return inst.innerAdd(body)
}

func (inst *PackBuilder) AddUint16(n uint16) *PackBuilder {
	body := &Uint16Body{
		Value: n,
	}
	return inst.innerAdd(body)
}

func (inst *PackBuilder) AddUint32(n uint32) *PackBuilder {
	body := &Uint32Body{
		Value: n,
	}
	return inst.innerAdd(body)
}

func (inst *PackBuilder) AddUint64(n uint64) *PackBuilder {
	body := &Uint64Body{
		Value: n,
	}
	return inst.innerAdd(body)
}

func (inst *PackBuilder) AddInt8(n int8) *PackBuilder {
	body := &Int8Body{
		Value: n,
	}
	return inst.innerAdd(body)
}

func (inst *PackBuilder) AddInt16(n int16) *PackBuilder {

	return inst
}

func (inst *PackBuilder) AddInt32(n int32) *PackBuilder {
	return inst
}

func (inst *PackBuilder) AddInt64(n int64) *PackBuilder {
	return inst
}

func (inst *PackBuilder) AddFloat(n float32) *PackBuilder {
	return inst
}

func (inst *PackBuilder) AddDouble(n float64) *PackBuilder {
	return inst
}

func (inst *PackBuilder) AddBytes(data []byte) *PackBuilder {
	return inst
}

func (inst *PackBuilder) AddString(value string) *PackBuilder {
	return inst
}

func (inst *PackBuilder) AddBoolean(value bool) *PackBuilder {
	return inst
}

func (inst *PackBuilder) AddARGB(value ARGB) *PackBuilder {
	return inst
}

func (inst *PackBuilder) AddEntity(block *BlockEntity) *PackBuilder {
	if block != nil {
		inst.blocks = append(inst.blocks, block)
	}
	return inst
}
