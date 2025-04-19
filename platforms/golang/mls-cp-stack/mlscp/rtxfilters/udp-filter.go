package rtxfilters

import "github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/mlscp"

// DatagramFilter 用于执行 UDP 包的收发
type DatagramFilter struct {
}

func (inst *DatagramFilter) _impl() mlscp.RTXFilter {
	return inst
}

func (inst *DatagramFilter) Rx(resp *mlscp.Response, chain mlscp.RxFilterChain) error {
	return chain.Rx(resp)
}

func (inst *DatagramFilter) Tx(req *mlscp.Request, chain mlscp.TxFilterChain) error {
	return chain.Tx(req)
}
