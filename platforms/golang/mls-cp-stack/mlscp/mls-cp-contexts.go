package mlscp

import (
	"net"
	"sync"
)

type ClientContext struct {
	Client Client // facade

	Current *SessionContext
	Config  *Configuration
	Locker  sync.Mutex
}

type SessionContext struct {
	Session Session // facade

	Parent *ClientContext
	Conn   *net.UDPConn
	Remote *net.UDPAddr

	Filters RTX

	Started  bool
	Stopped  bool
	Starting bool
	Stopping bool
	Error    error
}

type TransactionContext struct {
	Parent   *SessionContext
	Request  *Request
	Response *Response
}
