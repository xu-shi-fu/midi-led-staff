package rtxfilters

import "github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/mlscp"

type CodecFilter struct {
}

func (inst *CodecFilter) _impl() mlscp.RTXFilter {
	return inst
}

func (inst *CodecFilter) Rx(resp *mlscp.Response, chain mlscp.RxFilterChain) error {
	return chain.Rx(resp)
}

func (inst *CodecFilter) Tx(req *mlscp.Request, chain mlscp.TxFilterChain) error {
	return chain.Tx(req)
}
