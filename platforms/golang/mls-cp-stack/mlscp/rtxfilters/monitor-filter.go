package rtxfilters

import (
	"strconv"
	"strings"

	"github.com/starter-go/vlog"
	"github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/mlscp"
)

// MonitorFilter 用于调试, 它把收发的数据输出到日志
type MonitorFilter struct {
}

func (inst *MonitorFilter) _impl() mlscp.RTXFilter {
	return inst
}

func (inst *MonitorFilter) Rx(resp *mlscp.Response, chain mlscp.RxFilterChain) error {
	inst.log("rx", resp.Data)
	return chain.Rx(resp)
}

func (inst *MonitorFilter) Tx(req *mlscp.Request, chain mlscp.TxFilterChain) error {
	err := chain.Tx(req)
	inst.log("tx", req.Data)
	return err
}

func (inst *MonitorFilter) log(tag string, data []byte) {

	buffer := &strings.Builder{}
	count := len(data)

	for _, b := range data {
		str := strconv.Itoa(int(b))
		buffer.WriteRune(' ')
		buffer.WriteString(str)
		buffer.WriteRune(',')
	}

	vlog.Info("MonitorFilter(%s %d bytes): %s", tag, count, buffer.String())
}
