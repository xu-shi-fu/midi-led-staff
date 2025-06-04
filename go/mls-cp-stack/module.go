package mlscpstack

import (
	"embed"

	"github.com/starter-go/application"
	"github.com/starter-go/libgin/modules/libgin"
	"github.com/xu-shi-fu/midi-led-staff/go/mls-cp-stack/gen/main4mlscp"
)

const (
	theModuleName    = "github.com/xu-shi-fu/midi-led-staff/go/mls-cp-stack"
	theModuleVersion = "0.0.0"
	theModuleRev     = 0
)

////////////////////////////////////////////////////////////////////////////////

const (
	theModuleMainResPath = "src/main/resources"
	theModuleTestResPath = "src/test/resources"
)

//go:embed "src/main/resources"
var theModuleMainResFS embed.FS

//go:embed "src/test/resources"
var theModuleTestResFS embed.FS

////////////////////////////////////////////////////////////////////////////////

func ModuleMainBuilder() *application.ModuleBuilder {

	mb := &application.ModuleBuilder{}

	mb.Name(theModuleName + "#lib")
	mb.Version(theModuleVersion)
	mb.Revision(theModuleRev)

	mb.EmbedResources(theModuleMainResFS, theModuleMainResPath)
	mb.Components(main4mlscp.ExportComponents)

	mb.Depend(libgin.Module())

	return mb
}

func ModuleTestBuilder() *application.ModuleBuilder {

	mb := &application.ModuleBuilder{}

	mb.Name(theModuleName + "#test")
	mb.Version(theModuleVersion)
	mb.Revision(theModuleRev)

	mb.EmbedResources(theModuleTestResFS, theModuleTestResPath)

	// mb.Depend(libgin.Module())

	return mb
}
