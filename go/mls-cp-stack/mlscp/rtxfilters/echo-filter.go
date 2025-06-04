package rtxfilters

import "github.com/xu-shi-fu/midi-led-staff/go/mls-cp-stack/mlscp"

// EchoFilter 用于调试, 它把发送出去的请求直接当作响应返回
type EchoFilter struct {
}

func (inst *EchoFilter) _impl() mlscp.RTXFilter {
	return inst
}

func (inst *EchoFilter) Rx(resp *mlscp.Response, chain mlscp.RxFilterChain) error {
	return chain.Rx(resp)
}

func (inst *EchoFilter) Tx(req *mlscp.Request, chain mlscp.TxFilterChain) error {

	err := chain.Tx(req)
	if err != nil {
		return err
	}

	// 直接把请求当作响应返回
	resp := &mlscp.Response{}
	resp.Context = req.Context
	resp.Data = req.Data

	rx := req.Context.Parent.Filters.Rx
	return rx.Rx(resp)
}
