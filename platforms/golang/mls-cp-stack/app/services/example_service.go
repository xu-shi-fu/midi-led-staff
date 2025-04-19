package services

import (
	"context"
)

// ExampleService ...
type ExampleService interface {
	DoSomething(ctx context.Context) error
}
