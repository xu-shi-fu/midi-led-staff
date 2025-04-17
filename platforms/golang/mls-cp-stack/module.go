package main

import (
	"embed"

	"github.com/starter-go/application"
	"github.com/starter-go/libgin/modules/libgin"
	"github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/gen/main4mlscp"
)

const (
	theModuleName    = "github.com/xu-shi-fu/midi-led-staff/x"
	theModuleVersion = "0.0.0"
	theModuleRev     = 0

	theModuleResPath = "src/main/resources"
)

//go:embed "src/main/resources"
var theModuleResFS embed.FS

func Module() application.Module {

	mb := &application.ModuleBuilder{}

	mb.Name(theModuleName)
	mb.Version(theModuleVersion)
	mb.Revision(theModuleRev)

	mb.EmbedResources(theModuleResFS, theModuleResPath)
	mb.Components(main4mlscp.ExportComponents)

	mb.Depend(libgin.Module())

	return mb.Create()
}
