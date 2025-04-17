package t

import (
	"net/http"
	"strconv"

	"github.com/gin-gonic/gin"
	"github.com/starter-go/libgin"
	"github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/app/web/vo"
)

////////////////////////////////////////////////////////////////////////////////
// controller

// TestExampleController ...
type TestExampleController struct {

	//starter:component
	_as func(libgin.Controller) //starter:as(".")

	Responder libgin.Responder //starter:inject("#")
}

func (inst *TestExampleController) _impl() libgin.Controller {
	return inst
}

func (inst *TestExampleController) Registration() *libgin.ControllerRegistration {
	r1 := &libgin.ControllerRegistration{
		Route: inst.route,
	}
	return r1
}

func (inst *TestExampleController) route(rp libgin.RouterProxy) error {
	rp = rp.For("TestExample")
	rp.Handle(http.MethodGet, "", inst.handleGet)
	rp.Handle(http.MethodGet, ":id", inst.handleGet)
	return nil
}

func (inst *TestExampleController) handleGet(c *gin.Context) {
	req := &TestExampleRequest{
		controller:      inst,
		context:         c,
		wantRequestID:   false,
		wantRequestBody: false,
	}
	req.execute(req.doGet)
}

////////////////////////////////////////////////////////////////////////////////
// request

type TestExampleRequest struct {
	controller *TestExampleController
	context    *gin.Context

	wantRequestID   bool
	wantRequestBody bool

	id int

	body1 vo.Test
	body2 vo.Test
}

func (inst *TestExampleRequest) execute(fn func() error) {
	err := inst.open()
	if err == nil {
		err = fn()
	}
	inst.send(err)
}

func (inst *TestExampleRequest) open() error {

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

func (inst *TestExampleRequest) send(err error) {
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

func (inst *TestExampleRequest) doGet() error {

	return nil
}

////////////////////////////////////////////////////////////////////////////////
// EOF
