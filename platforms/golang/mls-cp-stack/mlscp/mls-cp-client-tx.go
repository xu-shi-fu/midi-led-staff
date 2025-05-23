package mlscp

const (

	// MethodGet 表示一个 GET 请求
	MethodGet Method = 1

	// MethodPost 表示一个 POST 请求
	MethodPost = 2

	// MethodPut 表示一个 PUT 请求
	MethodPut = 3

	// MethodDelete 表示一个 DELETE 请求
	MethodDelete = 4
)

////////////////////////////////////////////////////////////////////////////////

// Request 表示一个请求包
type Request struct {
	Version  Version
	Method   Method
	Location Location

	Context *TransactionContext
	Blocks  []*BlockEntity
	Data    []byte
}

type TxFilter interface {
	Tx(req *Request, chain TxFilterChain) error
}

type TxFilterChain interface {
	Tx(req *Request) error
}

type Dispatcher interface {
	TxFilterChain
}

////////////////////////////////////////////////////////////////////////////////

type RequestBuilder struct {
	context *TransactionContext

	method   Method
	location Location
	group    GroupID

	blocks []*BlockEntity
}

func (inst *RequestBuilder) Context(ctx *TransactionContext) *RequestBuilder {
	inst.context = ctx
	return inst
}

func (inst *RequestBuilder) Method(m Method) *RequestBuilder {
	inst.method = m
	return inst
}

func (inst *RequestBuilder) Location(l Location) *RequestBuilder {
	inst.location = l
	return inst
}

func (inst *RequestBuilder) Group(g GroupID) *RequestBuilder {
	inst.group = g
	return inst
}

func (inst *RequestBuilder) Build() *Request {

	req := &Request{
		Method:   inst.method,
		Location: inst.location,
		Context:  inst.context,
	}

	return req
}

func (inst *RequestBuilder) AddFieldUint8(fid FieldID, value uint8) *RequestBuilder {
	body := &BodyUint8{
		Value: value,
	}
	block := &BlockEntity{}
	block.Head.Group = inst.group
	block.Head.Field = fid
	block.Head.Type = body.Type()
	block.Body = body
	inst.blocks = append(inst.blocks, block)
	return inst
}
func (inst *RequestBuilder) AddFieldUint16(fid FieldID, value uint16) *RequestBuilder {
	body := &BodyUint16{
		Value: value,
	}
	block := &BlockEntity{}
	block.Head.Group = inst.group
	block.Head.Field = fid
	block.Head.Type = body.Type()
	block.Body = body
	inst.blocks = append(inst.blocks, block)
	return inst
}
func (inst *RequestBuilder) AddFieldUint32(fid FieldID, value uint32) *RequestBuilder {
	body := &BodyUint32{
		Value: value,
	}
	block := &BlockEntity{}
	block.Head.Group = inst.group
	block.Head.Field = fid
	block.Head.Type = body.Type()
	block.Body = body
	inst.blocks = append(inst.blocks, block)
	return inst
}
func (inst *RequestBuilder) AddFieldUint64(fid FieldID, value uint64) *RequestBuilder {
	body := &BodyUint64{
		Value: value,
	}
	block := &BlockEntity{}
	block.Head.Group = inst.group
	block.Head.Field = fid
	block.Head.Type = body.Type()
	block.Body = body
	inst.blocks = append(inst.blocks, block)
	return inst
}

func (inst *RequestBuilder) AddFieldInt8(fid FieldID, value int8) *RequestBuilder {
	body := &BodyInt8{
		Value: value,
	}
	block := &BlockEntity{}
	block.Head.Group = inst.group
	block.Head.Field = fid
	block.Head.Type = body.Type()
	block.Body = body
	inst.blocks = append(inst.blocks, block)
	return inst
}
func (inst *RequestBuilder) AddFieldInt16(fid FieldID, value int16) *RequestBuilder {
	body := &BodyInt16{
		Value: value,
	}
	block := &BlockEntity{}
	block.Head.Group = inst.group
	block.Head.Field = fid
	block.Head.Type = body.Type()
	block.Body = body
	inst.blocks = append(inst.blocks, block)
	return inst
}
func (inst *RequestBuilder) AddFieldInt32(fid FieldID, value int32) *RequestBuilder {
	body := &BodyInt32{
		Value: value,
	}
	block := &BlockEntity{}
	block.Head.Group = inst.group
	block.Head.Field = fid
	block.Head.Type = body.Type()
	block.Body = body
	inst.blocks = append(inst.blocks, block)
	return inst
}
func (inst *RequestBuilder) AddFieldInt64(fid FieldID, value int64) *RequestBuilder {
	body := &BodyInt64{
		Value: value,
	}
	block := &BlockEntity{}
	block.Head.Group = inst.group
	block.Head.Field = fid
	block.Head.Type = body.Type()
	block.Body = body
	inst.blocks = append(inst.blocks, block)
	return inst
}

func (inst *RequestBuilder) AddFieldByte(fid FieldID, value byte) *RequestBuilder {
	body := &BodyByte{
		Value: value,
	}
	block := &BlockEntity{}
	block.Head.Group = inst.group
	block.Head.Field = fid
	block.Head.Type = body.Type()
	block.Body = body
	inst.blocks = append(inst.blocks, block)
	return inst
}

func (inst *RequestBuilder) AddFieldBytes(fid FieldID, value []byte) *RequestBuilder {
	body := &BodyBytes{
		Value: value,
	}
	block := &BlockEntity{}
	block.Head.Group = inst.group
	block.Head.Field = fid
	block.Head.Type = body.Type()
	block.Body = body
	inst.blocks = append(inst.blocks, block)
	return inst
}

func (inst *RequestBuilder) AddFieldString(fid FieldID, value string) *RequestBuilder {
	body := &BodyString{
		Value: value,
	}
	block := &BlockEntity{}
	block.Head.Group = inst.group
	block.Head.Field = fid
	block.Head.Type = body.Type()
	block.Body = body
	inst.blocks = append(inst.blocks, block)
	return inst
}

////////////////////////////////////////////////////////////////////////////////

type txFilterChainNode struct {
	filter TxFilter
	next   TxFilterChain
}

func (inst *txFilterChainNode) Impl() TxFilterChain {
	return inst
}

func (inst *txFilterChainNode) Tx(req *Request) error {
	return inst.filter.Tx(req, inst.next)
}

////////////////////////////////////////////////////////////////////////////////

type txFilterChainEnding struct{}

func (inst *txFilterChainEnding) Impl() TxFilterChain {
	return inst
}

func (inst *txFilterChainEnding) Tx(req *Request) error {
	return nil // NOP
}

////////////////////////////////////////////////////////////////////////////////

type TxFilterChainBuilder struct {
	filters []TxFilter
}

func (inst *TxFilterChainBuilder) Add(f TxFilter) {
	if f == nil {
		return
	}
	inst.filters = append(inst.filters, f)
}

func (inst *TxFilterChainBuilder) Build() TxFilterChain {
	chain := TxFilterChain(nil)
	chain = &txFilterChainEnding{}
	for _, f := range inst.filters {
		node := &txFilterChainNode{
			filter: f,
			next:   chain,
		}
		chain = node
	}
	return chain
}

////////////////////////////////////////////////////////////////////////////////
