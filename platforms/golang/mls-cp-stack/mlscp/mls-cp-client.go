package mlscp

import (
	"fmt"
	"io"
	"net"
	"strconv"
	"time"
)

////////////////////////////////////////////////////////////////////////////////

// Configuration ...
type Configuration struct {
	ClientPort int
	ServerPort int
	ServerHost string
	Handler    Handler
	Filters    RTXFilterConfig
}

////////////////////////////////////////////////////////////////////////////////

type Session interface {
	io.Closer
}

type clientRuntime struct {
	context *SessionContext

	// handler Handler // use ResponseListener
	closer io.Closer // ref to conn

	shareTransactionContext *TransactionContext
}

func (inst *clientRuntime) Impl() Session {
	return inst
}

func (inst *clientRuntime) run() {

	defer func() {
		x := recover()
		HandleErrorX(x)
	}()

	ctx := inst.context

	defer func() {
		ctx.Stopped = true
	}()

	ctx.Starting = true
	err := inst.run2()
	ctx.Error = err
	HandleError(err)
}

func (inst *clientRuntime) run2() error {

	const network = "udp"
	conf := inst.context.Parent.Config

	port1 := conf.ClientPort

	host1 := ":" + strconv.Itoa(port1)

	addr1, err := net.ResolveUDPAddr(network, host1)
	if err != nil {
		return err
	}

	conn, err := net.ListenUDP(network, addr1)
	if err != nil {
		return err
	}

	filters, err := inst.loadFilters()
	if err != nil {
		return err
	}

	ctx := inst.context
	ctx.Filters = *filters
	ctx.Conn = conn
	ctx.Started = true
	inst.closer = conn

	return inst.run3()
}

func (inst *clientRuntime) run3() error {

	// rx-loop

	const bufferSize = 1024 * 2 // 实际上每个 UDP 包的大小不应超过大约 1.5K
	ctx := inst.context
	conn := ctx.Conn
	buffer := make([]byte, bufferSize)

	for {
		cb, addr, err := conn.ReadFromUDP(buffer)
		if err != nil {
			return err
		}
		data := buffer[0:cb]
		err = inst.handleRx(data, addr)
		HandleError(err)
	}
}

func (inst *clientRuntime) reverseFilterList(src []RTXFilter) []RTXFilter {
	dst := make([]RTXFilter, 0)
	for i := len(src); i > 0; {
		i--
		dst = append(dst, src[i])
	}
	return dst
}

func (inst *clientRuntime) loadFilters() (*RTX, error) {

	cc := inst.context.Parent
	cfg := inst.context.Parent.Config
	if cfg == nil {
		return nil, fmt.Errorf("mls: config is nil")
	}

	filters := cfg.Filters
	if filters == nil {
		return nil, fmt.Errorf("mls: config.filters is nil")
	}

	src := filters.GetFilters()
	if src == nil {
		return nil, fmt.Errorf("mls: config.filters.list is nil")
	}
	src2 := inst.reverseFilterList(src)

	rxBuilder := &RxFilterChainBuilder{}
	txBuilder := &TxFilterChainBuilder{}

	for _, item := range src {
		rxBuilder.Add(item)
		cc.AddComponent(item)
	}

	for _, item := range src2 {
		txBuilder.Add(item)
	}

	rtx := &RTX{}
	rtx.Rx = rxBuilder.Build()
	rtx.Tx = txBuilder.Build()
	return rtx, nil
}

func (inst *clientRuntime) handleRx(data []byte, addr *net.UDPAddr) error {
	h := inst.context.Filters.Rx
	ctx := inst.getShareTransactionContext()
	resp := &Response{
		Context: ctx,
		Data:    data,
		Remote:  addr,
	}
	return h.Rx(resp)
}

func (inst *clientRuntime) getShareTransactionContext() *TransactionContext {

	share := inst.shareTransactionContext
	if share != nil {
		return share
	}

	share = &TransactionContext{}
	share.Parent = inst.context
	share.Request = nil
	share.Response = nil

	return share
}

func (inst *clientRuntime) start() error {
	ctx := inst.context
	if ctx.Starting {
		return fmt.Errorf("re-call start()")
	}
	ctx.Starting = true
	go func() {
		inst.run()
	}()
	return nil
}

func (inst *clientRuntime) waitUntilStarted() error {
	ctx := inst.context
	if !ctx.Starting {
		return fmt.Errorf("this runtime is not starting")
	}
	for {
		if ctx.Started {
			return nil
		}

		if ctx.Stopped {
			err := ctx.Error
			HandleError(err)
			return fmt.Errorf("this runtime is stopped")
		}

		time.Sleep(time.Second)
	}
}

func (inst *clientRuntime) send(data []byte) error {

	ctx := inst.context
	addr := ctx.Remote
	conn := ctx.Conn
	if addr == nil {
		return fmt.Errorf("remote address is nil")
	}
	if conn == nil {
		return fmt.Errorf("UDP connection is nil")
	}

	cc := ctx.Parent
	cc.Lock()
	defer cc.Unlock()

	cb, err := conn.WriteToUDP(data, addr)
	if err != nil {
		return err
	}
	if cb != len(data) {
		return fmt.Errorf("the data sent is truncated")
	}
	return nil
}

func (inst *clientRuntime) Close() error {

	ctx := inst.context
	if ctx.Stopping {
		return fmt.Errorf("re-call Close()")
	}

	cl := inst.closer
	inst.closer = nil
	ctx.Stopping = true

	if cl == nil {
		return nil
	}
	return cl.Close()
}

////////////////////////////////////////////////////////////////////////////////

// Client ...
type Client interface {

	// as:
	io.Closer
	Dispatcher

	Configuration() *Configuration
}

type clientImpl struct {
	context *ClientContext
	closer  io.Closer // ref to runtime
}

func (inst *clientImpl) Impl() (Dispatcher, Client) {
	return inst, inst
}

func (inst *clientImpl) Configuration() *Configuration {
	return inst.context.Config
}

func (inst *clientImpl) Tx(req *Request) error {

	session := inst.context.Current
	if session == nil {
		return fmt.Errorf("no session")
	}

	tc, err := inst.makeTransactionContext(req)
	if err != nil {
		return err
	}
	req.Context = tc

	tx := session.Filters.Tx
	return tx.Tx(req)
}

func (inst *clientImpl) makeTransactionContext(req *Request) (*TransactionContext, error) {

	tc := &TransactionContext{}
	now := time.Now()
	cc := inst.context
	sc := inst.context.Current

	// lock-unlock
	cc.Lock()
	defer cc.Unlock()

	// Transaction-id
	sc.TransactionIDCounter++
	tid := sc.TransactionIDCounter

	// set
	tc.Parent = sc
	tc.Request = req
	tc.RequestAt = now
	tc.Timeout = time.Second * 10
	tc.TransactionID = tid

	return tc, nil
}

func (inst *clientImpl) Close() error {
	cl := inst.closer
	inst.closer = nil
	if cl == nil {
		return nil
	}
	return cl.Close()
}

func (inst *clientImpl) start() error {

	conf := inst.context.Config
	port2 := conf.ServerPort
	host2 := conf.ServerHost + ":" + strconv.Itoa(port2)
	addr2, err := net.ResolveUDPAddr("udp", host2)
	if err != nil {
		return err
	}

	// client-context
	ctx1 := inst.context
	// session-context
	ctx2 := &SessionContext{
		Remote: addr2,
		Parent: ctx1,
	}

	rt := &clientRuntime{
		context: ctx2,
	}
	ctx1.Current = ctx2
	inst.closer = rt

	err = rt.start()
	if err != nil {
		return err
	}

	return rt.waitUntilStarted()
}

func Open(config *Configuration) (Client, error) {
	ctx := &ClientContext{
		Config: config,
	}
	client := &clientImpl{
		context: ctx,
	}
	err := client.start()
	if err != nil {
		return nil, err
	}
	return client, nil
}

////////////////////////////////////////////////////////////////////////////////
// EOF
