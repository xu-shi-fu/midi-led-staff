package mlscp

import (
	"net"
	"sync"
	"time"
)

// TransactionID  表示一个事务的 ID , 它用于关联请求和响应
type TransactionID uint32

////////////////////////////////////////////////////////////////////////////////

type ClientContext struct {
	Client Client // facade

	Current *SessionContext
	Config  *Configuration

	components []any
	locker     sync.Mutex
}

func (inst *ClientContext) RunWithLock(fn func()) {
	inst.Lock()
	defer inst.Unlock()
	fn()
}

func (inst *ClientContext) Lock() {
	inst.locker.Lock()
}

func (inst *ClientContext) Unlock() {
	inst.locker.Unlock()
}

func (inst *ClientContext) AddComponent(com any) {
	inst.components = append(inst.components, com)
}

////////////////////////////////////////////////////////////////////////////////

type SessionContext struct {
	Session Session // facade

	Parent *ClientContext
	Conn   *net.UDPConn
	Remote *net.UDPAddr

	Filters RTX

	TransactionIDCounter TransactionID

	Started  bool
	Stopped  bool
	Starting bool
	Stopping bool
	Error    error
}

////////////////////////////////////////////////////////////////////////////////

type TransactionContext struct {
	TransactionID TransactionID

	Parent   *SessionContext
	Request  *Request
	Response *Response

	RequestAt  time.Time
	ResponseAt time.Time
	Timeout    time.Duration
}

////////////////////////////////////////////////////////////////////////////////
