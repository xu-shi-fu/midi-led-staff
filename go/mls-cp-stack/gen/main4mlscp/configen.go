package main4mlscp

import "github.com/starter-go/application"

//starter:configen(version="4")

// ExportComponents ...
func ExportComponents(cr application.ComponentRegistry) error {

	return registerComponents(cr)
}
