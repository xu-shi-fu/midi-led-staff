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

// SimpleTestController ...
type SimpleTestController struct {

	//starter:component
	_as func(libgin.Controller) //starter:as(".")

	Responder libgin.Responder //starter:inject("#")

	TestService services.TestService //starter:inject("#")
}

func (inst *SimpleTestController) _impl() libgin.Controller {
	return inst
}

func (inst *SimpleTestController) Registration() *libgin.ControllerRegistration {
	r1 := &libgin.ControllerRegistration{
		Route: inst.route,
	}
	return r1
}

func (inst *SimpleTestController) route(rp libgin.RouterProxy) error {
	rp = rp.For("simple-tests")
	rp.Handle(http.MethodGet, "", inst.handleGet)
	rp.Handle(http.MethodGet, ":id", inst.handleGet)
	rp.Handle(http.MethodGet, "ping", inst.handleGetPing)
	return nil
}

func (inst *SimpleTestController) handleGet(c *gin.Context) {
	req := &SimpleTestRequest{
		controller:      inst,
		context:         c,
		wantRequestID:   false,
		wantRequestBody: false,
	}
	req.execute(req.doGet)
}

func (inst *SimpleTestController) handleGetPing(c *gin.Context) {
	req := &SimpleTestRequest{
		controller:      inst,
		context:         c,
		wantRequestID:   false,
		wantRequestBody: false,
	}
	req.execute(req.doGetPing)
}

////////////////////////////////////////////////////////////////////////////////
// request

type SimpleTestRequest struct {
	controller *SimpleTestController
	context    *gin.Context

	wantRequestID   bool
	wantRequestBody bool

	id int

	body1 vo.SimpleTest
	body2 vo.SimpleTest
}

func (inst *SimpleTestRequest) execute(fn func() error) {
	err := inst.open()
	if err == nil {
		err = fn()
	}
	inst.send(err)
}

func (inst *SimpleTestRequest) open() error {

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

func (inst *SimpleTestRequest) send(err error) {
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

func (inst *SimpleTestRequest) doGet() error {
	return nil
}

func (inst *SimpleTestRequest) doGetPing() error {
	ctx := inst.context
	ser := inst.controller.TestService
	return ser.Ping(ctx)
}

////////////////////////////////////////////////////////////////////////////////
// EOF
