package main

import (
	"os"
	"testing"

	"github.com/starter-go/units"
	"github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/modules/mlscp"
)

func TestStack(t *testing.T) {

	p := make(map[string]string)

	m := mlscp.ModuleTest()

	cfg := &units.Config{
		Args:       os.Args,
		Cases:      "mls",
		Module:     m,
		Properties: p,
		T:          t,
		UsePanic:   true,
	}

	units.Run(cfg)
}
