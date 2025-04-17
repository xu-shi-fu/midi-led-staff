package mlscp

import (
	"fmt"
	"io"
	"net"
	"strconv"
	"sync"
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

type clientRuntime struct {
	client *Client
	conn   *net.UDPConn
	remote *net.UDPAddr
	// handler Handler // use ResponseListener
	closer  io.Closer // ref to conn
	filters RTX

	started  bool
	stopped  bool
	starting bool
	stopping bool
}

func (inst *clientRuntime) run() {

	defer func() {
		inst.stopped = true
	}()

	inst.starting = true

	err := inst.run2()
	handleError(err)
}

func (inst *clientRuntime) run2() error {

	const network = "udp"
	conf := inst.client.config

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

	inst.closer = conn
	inst.conn = conn
	inst.started = true

	return inst.run3()
}

func (inst *clientRuntime) run3() error {

	// rx-loop

	const bufferSize = 1024 * 2 // 实际上每个 UDP 包的大小不应超过大约 1.5K
	conn := inst.conn
	buffer := make([]byte, bufferSize)

	for {
		cb, addr, err := conn.ReadFromUDP(buffer)
		if err != nil {
			return err
		}
		data := buffer[0:cb]
		err = inst.handleRx(data, addr)
		handleError(err)
	}
}

func (inst *clientRuntime) handleRx(data []byte, addr *net.UDPAddr) error {
	h := inst.filters.Rx
	cl := inst.client
	resp := &Response{
		Data:   data,
		Client: cl,
		Remote: addr,
	}
	return h.Rx(resp)
}

func (inst *clientRuntime) start() error {
	if inst.starting {
		return fmt.Errorf("re-call start()")
	}
	inst.starting = true
	go func() {
		inst.run()
	}()
	return nil
}

func (inst *clientRuntime) waitUntilStarted() error {
	if !inst.starting {
		return fmt.Errorf("this runtime is not starting")
	}
	for {
		if inst.started {
			return nil
		}
		if inst.stopped {
			return fmt.Errorf("this runtime is stopped")
		}
	}
}

func (inst *clientRuntime) send(data []byte) error {

	addr := inst.remote
	conn := inst.conn
	if addr == nil {
		return fmt.Errorf("remote address is nil")
	}
	if conn == nil {
		return fmt.Errorf("UDP connection is nil")
	}

	mtx := &inst.client.mutex
	mtx.Lock()
	defer mtx.Unlock()

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

	if inst.stopping {
		return fmt.Errorf("re-call Close()")
	}

	cl := inst.closer
	inst.closer = nil
	inst.stopping = true

	if cl == nil {
		return nil
	}
	return cl.Close()
}

////////////////////////////////////////////////////////////////////////////////

// Client ...
type Client struct {
	mutex   sync.Mutex
	config  *Configuration
	runtime *clientRuntime
	closer  io.Closer // ref to runtime
}

func (inst *Client) _impl() Dispatcher {
	return inst
}

func (inst *Client) Tx(req *Request) error {
	data := req.Data
	rt := inst.runtime
	if rt == nil {
		return fmt.Errorf("no runtime")
	}
	if data == nil {
		return nil
	}
	return rt.send(data)
}

func (inst *Client) Close() error {
	cl := inst.closer
	inst.closer = nil
	if cl == nil {
		return nil
	}
	return cl.Close()
}

func (inst *Client) start() error {

	conf := inst.config
	port2 := conf.ServerPort
	host2 := conf.ServerHost + ":" + strconv.Itoa(port2)
	addr2, err := net.ResolveUDPAddr("udp", host2)
	if err != nil {
		return err
	}

	rt := &clientRuntime{
		client: inst,
		remote: addr2,
	}
	inst.runtime = rt
	inst.closer = rt

	err = rt.start()
	if err != nil {
		return err
	}
	return rt.waitUntilStarted()
}

func Open(config *Configuration) (*Client, error) {
	client := &Client{
		config: config,
	}
	err := client.start()
	if err != nil {
		return nil, err
	}
	return client, nil
}

////////////////////////////////////////////////////////////////////////////////
// EOF
