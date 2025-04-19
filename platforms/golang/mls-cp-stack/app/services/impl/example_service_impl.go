package impl

import (
	"context"
	"fmt"

	"github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/app/services"
)

type ExampleServiceImpl struct {

	//starter:component
	_as func(services.ExampleService) //starter:as("#")

}

func (inst *ExampleServiceImpl) _impl() services.ExampleService {
	return inst
}

func (inst *ExampleServiceImpl) DoSomething(c context.Context) error {
	return fmt.Errorf("no impl")
}
