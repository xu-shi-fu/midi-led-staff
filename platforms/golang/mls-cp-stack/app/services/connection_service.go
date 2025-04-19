package services

import (
	"context"

	"github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/app/web/vo"
	"github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/mlscp"
)

// ConnectionService ...
type ConnectionService interface {
	Connect(ctx context.Context, param *vo.Connections) error

	Disconnect(ctx context.Context) error

	GetCurrent(ctx context.Context) (mlscp.Client, error)
}
