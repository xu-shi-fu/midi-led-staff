package services

import (
	"context"
)

// TestService ...
type TestService interface {
	Ping(ctx context.Context) error
}
