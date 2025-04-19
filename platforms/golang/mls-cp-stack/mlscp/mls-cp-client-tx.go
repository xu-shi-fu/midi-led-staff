package mlscp

// Request 表示一个请求包
type Request struct {
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

type txFilterChainNode struct {
	filter TxFilter
	next   TxFilterChain
}

func (inst *txFilterChainNode) _impl() TxFilterChain {
	return inst
}

func (inst *txFilterChainNode) Tx(req *Request) error {
	return inst.filter.Tx(req, inst.next)
}

////////////////////////////////////////////////////////////////////////////////

type txFilterChainEnding struct{}

func (inst *txFilterChainEnding) _impl() TxFilterChain {
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
