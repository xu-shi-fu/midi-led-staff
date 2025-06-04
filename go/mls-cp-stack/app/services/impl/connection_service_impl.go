package impl

import (
	"context"
	"fmt"

	"github.com/xu-shi-fu/midi-led-staff/go/mls-cp-stack/app/services"
	"github.com/xu-shi-fu/midi-led-staff/go/mls-cp-stack/app/web/vo"
	"github.com/xu-shi-fu/midi-led-staff/go/mls-cp-stack/mlscp"
	"github.com/xu-shi-fu/midi-led-staff/go/mls-cp-stack/mlscp/rtxfilters"
)

type ConnectionServiceImpl struct {

	//starter:component
	_as func(services.ConnectionService) //starter:as("#")

	client mlscp.Client
}

func (inst *ConnectionServiceImpl) _impl() (services.ConnectionService, mlscp.RTXFilterConfig) {
	return inst, inst
}

func (inst *ConnectionServiceImpl) GetFilters() []mlscp.RTXFilter {
	list := make([]mlscp.RTXFilter, 0)

	list = append(list, &rtxfilters.MonitorFilter{})
	list = append(list, &rtxfilters.RespondingFilter{})
	list = append(list, &rtxfilters.CodecFilter{})
	list = append(list, &rtxfilters.DatagramFilter{})

	// list = append(list, &rtxfilters.EchoFilter{})

	return list
}

func (inst *ConnectionServiceImpl) Connect(ctx context.Context, param *vo.Connections) error {

	cfg := &mlscp.Configuration{}
	cfg.ClientPort = param.ClientPort
	cfg.ServerPort = param.ServerPort
	cfg.ServerHost = param.ServerHost
	cfg.Filters = inst

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

func (inst *ConnectionServiceImpl) GetCurrent(ctx context.Context) (mlscp.Client, error) {
	client := inst.client
	if client == nil {
		return nil, fmt.Errorf("no connected connection")
	}
	return client, nil
}
