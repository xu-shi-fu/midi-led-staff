package controllers

import (
	"net/http"
	"strconv"

	"github.com/gin-gonic/gin"
	"github.com/starter-go/libgin"
	"github.com/xu-shi-fu/midi-led-staff/go/mls-cp-stack/app/services"
	"github.com/xu-shi-fu/midi-led-staff/go/mls-cp-stack/app/web/vo"
)

////////////////////////////////////////////////////////////////////////////////
// controller

// ConnectionController ...
type ConnectionController struct {

	//starter:component
	_as func(libgin.Controller) //starter:as(".")

	Responder libgin.Responder           //starter:inject("#")
	Service   services.ConnectionService //starter:inject("#")
}

func (inst *ConnectionController) _impl() libgin.Controller {
	return inst
}

func (inst *ConnectionController) Registration() *libgin.ControllerRegistration {
	r1 := &libgin.ControllerRegistration{
		Route: inst.route,
	}
	return r1
}

func (inst *ConnectionController) route(rp libgin.RouterProxy) error {
	rp = rp.For("connections")

	rp.Handle(http.MethodGet, "", inst.handleGet)
	rp.Handle(http.MethodGet, ":id", inst.handleGet)
	rp.Handle(http.MethodGet, "connect", inst.handleGetConnect)

	rp.Handle(http.MethodPost, "connect", inst.handlePostConnect)
	rp.Handle(http.MethodPost, "disconnect", inst.handlePostDisconnect)
	return nil
}

func (inst *ConnectionController) handleGet(c *gin.Context) {
	req := &ConnectionRequest{
		controller:      inst,
		context:         c,
		wantRequestID:   false,
		wantRequestBody: false,
	}
	req.execute(req.doGet)
}

func (inst *ConnectionController) handleGetConnect(c *gin.Context) {
	req := &ConnectionRequest{
		controller:       inst,
		context:          c,
		wantRequestID:    false,
		wantRequestBody:  false,
		wantRequestQuery: true,
	}
	req.execute(req.doConnect)
}

func (inst *ConnectionController) handlePostConnect(c *gin.Context) {
	req := &ConnectionRequest{
		controller:      inst,
		context:         c,
		wantRequestID:   false,
		wantRequestBody: false,
	}
	req.execute(req.doConnect)
}

func (inst *ConnectionController) handlePostDisconnect(c *gin.Context) {
	req := &ConnectionRequest{
		controller:      inst,
		context:         c,
		wantRequestID:   false,
		wantRequestBody: false,
	}
	req.execute(req.doDisconnect)
}

////////////////////////////////////////////////////////////////////////////////
// request

type ConnectionRequest struct {
	controller *ConnectionController
	context    *gin.Context

	wantRequestID    bool
	wantRequestBody  bool
	wantRequestQuery bool

	id int

	body1 vo.Connections
	body2 vo.Connections
}

func (inst *ConnectionRequest) execute(fn func() error) {
	err := inst.open()
	if err == nil {
		err = fn()
	}
	inst.send(err)
}

func (inst *ConnectionRequest) open() error {

	c := inst.context

	if inst.wantRequestID {
		str := c.Param("id")
		id, err := strconv.Atoi(str)
		if err != nil {
			return err
		}
		inst.id = id
	}

	if inst.wantRequestBody {
		err := c.BindJSON(&inst.body1)
		if err != nil {
			return err
		}
	}

	if inst.wantRequestQuery {
		err := inst.parseQuery()
		if err != nil {
			return err
		}
	}

	return nil
}

func (inst *ConnectionRequest) parseQuery() error {

	b1 := &inst.body1
	c := inst.context

	strServerHost := c.Query("server.host")
	strServerPort := c.Query("server.port")
	strClientPort := c.Query("client.port")

	clientPort, err := strconv.Atoi(strClientPort)
	if err != nil {
		return err
	}

	serverPort, err := strconv.Atoi(strServerPort)
	if err != nil {
		return err
	}

	b1.ClientPort = clientPort
	b1.ServerPort = serverPort
	b1.ServerHost = strServerHost
	return nil
}

func (inst *ConnectionRequest) send(err error) {
	c := inst.context
	d := &inst.body2
	s := d.Status
	r := ""
	resp := &libgin.Response{
		Context:   c,
		Data:      d,
		Error:     err,
		Responder: r,
		Status:    s,
	}
	inst.controller.Responder.Send(resp)
}

func (inst *ConnectionRequest) doGet() error {
	return nil
}

func (inst *ConnectionRequest) doConnect() error {
	p := &inst.body1
	ctx := inst.context
	ser := inst.controller.Service
	return ser.Connect(ctx, p)
}

func (inst *ConnectionRequest) doDisconnect() error {
	ctx := inst.context
	ser := inst.controller.Service
	return ser.Disconnect(ctx)
}

////////////////////////////////////////////////////////////////////////////////
// EOF
