package mlscp

import (
	"github.com/starter-go/application"
	"github.com/starter-go/units/modules/units"
	mlscpstack "github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack"
	"github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/gen/main4mlscp"
	"github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/gen/test4mlscp"
)

func ModuleMain() application.Module {

	mb := mlscpstack.ModuleMainBuilder()
	mb.Components(main4mlscp.ExportComponents)

	return mb.Create()
}

func ModuleTest() application.Module {

	mb := mlscpstack.ModuleTestBuilder()
	mb.Components(test4mlscp.ExportComponents)

	mb.Depend(ModuleMain())
	mb.Depend(units.Module())

	return mb.Create()
}
