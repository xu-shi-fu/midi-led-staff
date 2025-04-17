package main

import (
	"os"

	"github.com/starter-go/starter"
)

func main() {

	args := os.Args
	m := Module()

	i := starter.Init(args)
	i.MainModule(m)
	i.WithPanic(true).Run()
}
