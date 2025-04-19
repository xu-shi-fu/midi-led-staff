package impl

import (
	"context"

	"github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/app/services"
	"github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/mlscp"
)

type TestServiceImpl struct {

	//starter:component
	_as func(services.TestService) //starter:as("#")

	ConnService services.ConnectionService //starter:inject("#")
}

func (inst *TestServiceImpl) _impl() services.TestService {
	return inst
}

func (inst *TestServiceImpl) Ping(ctx context.Context) error {

	client, err := inst.ConnService.GetCurrent(ctx)
	if err != nil {
		return err
	}

	req := &mlscp.Request{}
	err = client.Tx(req)
	return err
}
