package services

import (
	"context"

	"github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/app/web/vo"
)

type ConnectionService interface {
	Connect(ctx context.Context, param *vo.Connections) error
	Disconnect(ctx context.Context) error
}
