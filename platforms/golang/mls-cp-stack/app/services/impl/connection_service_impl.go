package impl

import (
	"context"

	"github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/app/services"
	"github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/app/web/vo"
	"github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/mlscp"
)

type ConnectionServiceImpl struct {

	//starter:component
	_as func(services.ConnectionService) //starter:as("#")

	client *mlscp.Client
}

func (inst *ConnectionServiceImpl) _impl() services.ConnectionService {
	return inst
}

func (inst *ConnectionServiceImpl) Connect(ctx context.Context, param *vo.Connections) error {

	cfg := &mlscp.Configuration{}

	client, err := mlscp.Open(cfg)
	if err != nil {
		return err
	}

	inst.client = client
	return nil
}

func (inst *ConnectionServiceImpl) Disconnect(ctx context.Context) error {

	client := inst.client
	inst.client = nil

	if client == nil {
		return nil
	}
	return client.Close()
}
