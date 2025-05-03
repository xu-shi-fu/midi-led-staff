package main

import (
	"os"

	"github.com/starter-go/starter"
	"github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/modules/mlscp"
)

func main() {

	args := os.Args
	m := mlscp.ModuleMain()

	i := starter.Init(args)
	i.MainModule(m)
	i.WithPanic(true).Run()

}
