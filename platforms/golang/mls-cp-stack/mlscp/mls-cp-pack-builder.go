package mlscp

type PackBuilder struct{}

func (inst *PackBuilder) AddUint8(h BlockHead, n uint8) {}

func (inst *PackBuilder) AddUint16(h BlockHead, n uint16) {}

func (inst *PackBuilder) AddUint32(h BlockHead, n uint32) {}

func (inst *PackBuilder) AddUint64(h BlockHead, n uint64) {}

func (inst *PackBuilder) AddInt8(h BlockHead, n int8) {}

func (inst *PackBuilder) AddInt16(h BlockHead, n int16) {}

func (inst *PackBuilder) AddInt32(h BlockHead, n int32) {}

func (inst *PackBuilder) AddInt64(h BlockHead, n int64) {}

func (inst *PackBuilder) AddFloat(h BlockHead, n float32) {}

func (inst *PackBuilder) AddDouble(h BlockHead, n float64) {}

func (inst *PackBuilder) AddBytes(h BlockHead, data []byte) {}

func (inst *PackBuilder) AddString(h BlockHead, value string) {}

func (inst *PackBuilder) AddBoolean(h BlockHead, value bool) {}

func (inst *PackBuilder) AddARGB(h BlockHead, value ARGB) {}
