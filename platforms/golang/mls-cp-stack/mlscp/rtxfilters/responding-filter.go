package rtxfilters

import (
	"time"

	"github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/mlscp"
)

// RespondingFilter 用于监听服务端的响应, 并与对应的请求相关联
type RespondingFilter struct {
	table map[mlscp.TransactionID]*mlscp.TransactionContext
}

func (inst *RespondingFilter) Impl() mlscp.RTXFilter {
	return inst
}

func (inst *RespondingFilter) Init() {
	inst.table = make(map[mlscp.TransactionID]*mlscp.TransactionContext)
}

func (inst *RespondingFilter) Rx(resp *mlscp.Response, chain mlscp.RxFilterChain) error {
	err := inst.onReceive(resp)
	if err != nil {
		return err
	}
	return chain.Rx(resp)
}

func (inst *RespondingFilter) Tx(req *mlscp.Request, chain mlscp.TxFilterChain) error {
	err := inst.onSend(req)
	if err != nil {
		return err
	}
	return chain.Tx(req)
}

func (inst *RespondingFilter) getTable() map[mlscp.TransactionID]*mlscp.TransactionContext {
	t := inst.table
	if t == nil {
		t = make(map[mlscp.TransactionID]*mlscp.TransactionContext)
		inst.table = t
	}
	return t
}

func (inst *RespondingFilter) onSend(req *mlscp.Request) error {

	tc := req.Context
	cc := inst.getCC(tc)
	tid := tc.TransactionID

	cc.Lock()
	defer cc.Unlock()

	table := inst.getTable()
	table[tid] = tc

	return nil
}

func (inst *RespondingFilter) onReceive(resp *mlscp.Response) error {

	tc1 := resp.Context
	tid := tc1.TransactionID
	cc := inst.getCC(resp.Context)
	now := time.Now()

	cc.Lock()
	defer cc.Unlock()

	table := inst.getTable()
	tc2 := table[tid]
	if tc2 == nil {
		return nil
	}

	resp.Context = tc2
	tc2.Response = resp
	tc2.ResponseAt = now

	return nil
}

func (inst *RespondingFilter) getCC(tc *mlscp.TransactionContext) *mlscp.ClientContext {
	return tc.Parent.Parent
}
