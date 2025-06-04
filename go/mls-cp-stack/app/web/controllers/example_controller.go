package controllers

import (
	"net/http"
	"strconv"

	"github.com/gin-gonic/gin"
	"github.com/starter-go/libgin"
	"github.com/xu-shi-fu/midi-led-staff/go/mls-cp-stack/app/web/vo"
)

////////////////////////////////////////////////////////////////////////////////
// controller

// ExampleController ...
type ExampleController struct {

	//starter:component
	_as func(libgin.Controller) //starter:as(".")

	Responder libgin.Responder //starter:inject("#")
}

func (inst *ExampleController) _impl() libgin.Controller {
	return inst
}

func (inst *ExampleController) Registration() *libgin.ControllerRegistration {
	r1 := &libgin.ControllerRegistration{
		Route: inst.route,
	}
	return r1
}

func (inst *ExampleController) route(rp libgin.RouterProxy) error {
	rp = rp.For("example")
	rp.Handle(http.MethodGet, "", inst.handleGet)
	rp.Handle(http.MethodGet, ":id", inst.handleGet)
	return nil
}

func (inst *ExampleController) handleGet(c *gin.Context) {
	req := &ExampleRequest{
		controller:      inst,
		context:         c,
		wantRequestID:   false,
		wantRequestBody: false,
	}
	req.execute(req.doGet)
}

////////////////////////////////////////////////////////////////////////////////
// request

type ExampleRequest struct {
	controller *ExampleController
	context    *gin.Context

	wantRequestID   bool
	wantRequestBody bool

	id int

	body1 vo.Example
	body2 vo.Example
}

func (inst *ExampleRequest) execute(fn func() error) {
	err := inst.open()
	if err == nil {
		err = fn()
	}
	inst.send(err)
}

func (inst *ExampleRequest) open() error {

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

func (inst *ExampleRequest) send(err error) {
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

func (inst *ExampleRequest) doGet() error {

	return nil
}

////////////////////////////////////////////////////////////////////////////////
// EOF
