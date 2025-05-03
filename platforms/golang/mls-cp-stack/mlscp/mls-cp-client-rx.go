package mlscp

import "net"

// Response 表示一个响应包
type Response struct {
	Blocks  []*BlockEntity
	Data    []byte
	Remote  *net.UDPAddr
	Context *TransactionContext

	Version Version
	Status  int
	Message string
}

type RxFilterChain interface {
	Rx(resp *Response) error
}

type RxFilter interface {
	Rx(resp *Response, chain RxFilterChain) error
}

type Handler interface {
	RxFilterChain
}

////////////////////////////////////////////////////////////////////////////////

type rxFilterChainNode struct {
	filter RxFilter
	next   RxFilterChain
}

func (inst *rxFilterChainNode) _impl() RxFilterChain {
	return inst
}

func (inst *rxFilterChainNode) Rx(resp *Response) error {
	return inst.filter.Rx(resp, inst.next)
}

////////////////////////////////////////////////////////////////////////////////

type rxFilterChainEnding struct{}

func (inst *rxFilterChainEnding) _impl() RxFilterChain {
	return inst
}

func (inst *rxFilterChainEnding) Rx(resp *Response) error {
	return nil // NOP
}

////////////////////////////////////////////////////////////////////////////////

type RxFilterChainBuilder struct {
	filters []RxFilter
}

func (inst *RxFilterChainBuilder) Add(f RxFilter) {
	if f == nil {
		return
	}
	inst.filters = append(inst.filters, f)
}

func (inst *RxFilterChainBuilder) Build() RxFilterChain {
	chain := RxFilterChain(nil)
	chain = &rxFilterChainEnding{}
	for _, f := range inst.filters {
		node := &rxFilterChainNode{
			filter: f,
			next:   chain,
		}
		chain = node
	}
	return chain
}

////////////////////////////////////////////////////////////////////////////////
