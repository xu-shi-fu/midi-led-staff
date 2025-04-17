package rtxfilters

import "github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/mlscp"

// MonitorFilter 用于调试, 它把收发的数据输出到日志
type MonitorFilter struct {
}

func (inst *MonitorFilter) _impl() mlscp.RTXFilter {
	return inst
}

func (inst *MonitorFilter) Rx(resp *mlscp.Response, chain mlscp.RxFilterChain) error {
	return chain.Rx(resp)
}

func (inst *MonitorFilter) Tx(req *mlscp.Request, chain mlscp.TxFilterChain) error {
	return chain.Tx(req)
}
