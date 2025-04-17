package rtxfilters

import "github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/mlscp"

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
	return chain.Tx(req)
}
