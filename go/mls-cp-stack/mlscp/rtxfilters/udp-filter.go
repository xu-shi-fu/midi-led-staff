package rtxfilters

import (
	"fmt"

	"github.com/xu-shi-fu/midi-led-staff/go/mls-cp-stack/mlscp"
)

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

	sc := req.Context.Parent
	data := req.Data
	addr := sc.Remote
	conn := sc.Conn
	len1 := len(data)

	len2, err := conn.WriteToUDP(data, addr)
	if err != nil {
		return err
	}

	if len1 != len2 {
		return fmt.Errorf("bad data length, want:%d have:%d", len1, len2)
	}

	return chain.Tx(req)
}
