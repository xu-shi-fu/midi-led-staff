package controllers

import (
	"fmt"
	"net/http"
	"strconv"

	"github.com/gin-gonic/gin"
	"github.com/starter-go/libgin"
	"github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/app/services"
	"github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/app/web/vo"
)

////////////////////////////////////////////////////////////////////////////////
// controller

// TestController ...
type TestController struct {

	//starter:component
	_as func(libgin.Controller) //starter:as(".")

	Responder         libgin.Responder           //starter:inject("#")
	ConnectionService services.ConnectionService //starter:inject("#")
	TestService       services.TestService       //starter:inject("#")
}

func (inst *TestController) _impl() libgin.Controller {
	return inst
}

func (inst *TestController) Registration() *libgin.ControllerRegistration {
	r1 := &libgin.ControllerRegistration{
		Route: inst.route,
	}
	return r1
}

func (inst *TestController) route(rp libgin.RouterProxy) error {
	rp = rp.For("tests")

	rp.Handle(http.MethodGet, "", inst.handleGet)
	rp.Handle(http.MethodGet, ":id", inst.handleGet)
	rp.Handle(http.MethodGet, "connect", inst.handleGetConnect)
	rp.Handle(http.MethodGet, "disconnect", inst.handleGetDisconnect)
	rp.Handle(http.MethodGet, "ping", inst.handleGetPing)

	return nil
}

func (inst *TestController) handleGet(c *gin.Context) {
	req := &TestRequest{
		controller:      inst,
		context:         c,
		wantRequestID:   false,
		wantRequestBody: false,
	}
	req.execute(req.doGet)
}

func (inst *TestController) handleGetConnect(c *gin.Context) {
	req := &TestRequest{
		controller:      inst,
		context:         c,
		wantRequestID:   false,
		wantRequestBody: false,
	}
	req.execute(req.doGetConnect)
}

func (inst *TestController) handleGetDisconnect(c *gin.Context) {
	req := &TestRequest{
		controller:      inst,
		context:         c,
		wantRequestID:   false,
		wantRequestBody: false,
	}
	req.execute(req.doGetDisconnect)
}

func (inst *TestController) handleGetPing(c *gin.Context) {
	req := &TestRequest{
		controller:      inst,
		context:         c,
		wantRequestID:   false,
		wantRequestBody: false,
	}
	req.execute(req.doGetPing)
}

////////////////////////////////////////////////////////////////////////////////
// request

type TestRequest struct {
	controller *TestController
	context    *gin.Context

	wantRequestID   bool
	wantRequestBody bool

	id int

	body1 vo.Test
	body2 vo.Test
}

func (inst *TestRequest) execute(fn func() error) {
	err := inst.open()
	if err == nil {
		err = fn()
	}
	inst.send(err)
}

func (inst *TestRequest) open() error {

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

	return nil
}

func (inst *TestRequest) send(err error) {
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

func (inst *TestRequest) doGet() error {
	return fmt.Errorf("no impl")
}

func (inst *TestRequest) doGetConnect() error {

	ctx := inst.context
	ser := inst.controller.ConnectionService
	p := &vo.Connections{}

	strClientPort := ctx.Query("client.port")
	strServerPort := ctx.Query("server.port")
	strServerHost := ctx.Query("server.host")

	clientPort, _ := strconv.Atoi(strClientPort)
	serverPort, _ := strconv.Atoi(strServerPort)

	if strServerHost == "" || serverPort == 0 || clientPort == 0 {
		return fmt.Errorf("need query params: client.port & server.port & server.host")
	}

	p.ServerHost = strServerHost
	p.ServerPort = serverPort
	p.ClientPort = clientPort

	return ser.Connect(ctx, p)
}

func (inst *TestRequest) doGetDisconnect() error {
	ctx := inst.context
	ser := inst.controller.ConnectionService
	return ser.Disconnect(ctx)
}

func (inst *TestRequest) doGetPing() error {
	ctx := inst.context
	ser := inst.controller.TestService
	return ser.Ping(ctx)
}

////////////////////////////////////////////////////////////////////////////////
// EOF
