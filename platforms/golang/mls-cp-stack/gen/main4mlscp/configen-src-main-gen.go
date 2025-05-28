package main4mlscp
import (
    pd1a916a20 "github.com/starter-go/libgin"
    p1e554a92e "github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/app/services"
    pb21ef5bbc "github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/app/services/impl"
    p9a99ad5d3 "github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/app/web/controllers"
     "github.com/starter-go/application"
)

// type pb21ef5bbc.ConnectionServiceImpl in package:github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/app/services/impl
//
// id:com-b21ef5bbc14262ce-impl-ConnectionServiceImpl
// class:
// alias:alias-1e554a92e02558d082d6cfb8b5a85f00-ConnectionService
// scope:singleton
//
type pb21ef5bbc1_impl_ConnectionServiceImpl struct {
}

func (inst* pb21ef5bbc1_impl_ConnectionServiceImpl) register(cr application.ComponentRegistry) error {
	r := cr.NewRegistration()
	r.ID = "com-b21ef5bbc14262ce-impl-ConnectionServiceImpl"
	r.Classes = ""
	r.Aliases = "alias-1e554a92e02558d082d6cfb8b5a85f00-ConnectionService"
	r.Scope = "singleton"
	r.NewFunc = inst.new
	r.InjectFunc = inst.inject
	return r.Commit()
}

func (inst* pb21ef5bbc1_impl_ConnectionServiceImpl) new() any {
    return &pb21ef5bbc.ConnectionServiceImpl{}
}

func (inst* pb21ef5bbc1_impl_ConnectionServiceImpl) inject(injext application.InjectionExt, instance any) error {
	ie := injext
	com := instance.(*pb21ef5bbc.ConnectionServiceImpl)
	nop(ie, com)

	


    return nil
}



// type pb21ef5bbc.ExampleServiceImpl in package:github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/app/services/impl
//
// id:com-b21ef5bbc14262ce-impl-ExampleServiceImpl
// class:
// alias:alias-1e554a92e02558d082d6cfb8b5a85f00-ExampleService
// scope:singleton
//
type pb21ef5bbc1_impl_ExampleServiceImpl struct {
}

func (inst* pb21ef5bbc1_impl_ExampleServiceImpl) register(cr application.ComponentRegistry) error {
	r := cr.NewRegistration()
	r.ID = "com-b21ef5bbc14262ce-impl-ExampleServiceImpl"
	r.Classes = ""
	r.Aliases = "alias-1e554a92e02558d082d6cfb8b5a85f00-ExampleService"
	r.Scope = "singleton"
	r.NewFunc = inst.new
	r.InjectFunc = inst.inject
	return r.Commit()
}

func (inst* pb21ef5bbc1_impl_ExampleServiceImpl) new() any {
    return &pb21ef5bbc.ExampleServiceImpl{}
}

func (inst* pb21ef5bbc1_impl_ExampleServiceImpl) inject(injext application.InjectionExt, instance any) error {
	ie := injext
	com := instance.(*pb21ef5bbc.ExampleServiceImpl)
	nop(ie, com)

	


    return nil
}



// type pb21ef5bbc.TestServiceImpl in package:github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/app/services/impl
//
// id:com-b21ef5bbc14262ce-impl-TestServiceImpl
// class:
// alias:alias-1e554a92e02558d082d6cfb8b5a85f00-TestService
// scope:singleton
//
type pb21ef5bbc1_impl_TestServiceImpl struct {
}

func (inst* pb21ef5bbc1_impl_TestServiceImpl) register(cr application.ComponentRegistry) error {
	r := cr.NewRegistration()
	r.ID = "com-b21ef5bbc14262ce-impl-TestServiceImpl"
	r.Classes = ""
	r.Aliases = "alias-1e554a92e02558d082d6cfb8b5a85f00-TestService"
	r.Scope = "singleton"
	r.NewFunc = inst.new
	r.InjectFunc = inst.inject
	return r.Commit()
}

func (inst* pb21ef5bbc1_impl_TestServiceImpl) new() any {
    return &pb21ef5bbc.TestServiceImpl{}
}

func (inst* pb21ef5bbc1_impl_TestServiceImpl) inject(injext application.InjectionExt, instance any) error {
	ie := injext
	com := instance.(*pb21ef5bbc.TestServiceImpl)
	nop(ie, com)

	
    com.ConnService = inst.getConnService(ie)


    return nil
}


func (inst*pb21ef5bbc1_impl_TestServiceImpl) getConnService(ie application.InjectionExt)p1e554a92e.ConnectionService{
    return ie.GetComponent("#alias-1e554a92e02558d082d6cfb8b5a85f00-ConnectionService").(p1e554a92e.ConnectionService)
}



// type p9a99ad5d3.ConnectionController in package:github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/app/web/controllers
//
// id:com-9a99ad5d3031ef6f-controllers-ConnectionController
// class:class-d1a916a203352fd5d33eabc36896b42e-Controller
// alias:
// scope:singleton
//
type p9a99ad5d30_controllers_ConnectionController struct {
}

func (inst* p9a99ad5d30_controllers_ConnectionController) register(cr application.ComponentRegistry) error {
	r := cr.NewRegistration()
	r.ID = "com-9a99ad5d3031ef6f-controllers-ConnectionController"
	r.Classes = "class-d1a916a203352fd5d33eabc36896b42e-Controller"
	r.Aliases = ""
	r.Scope = "singleton"
	r.NewFunc = inst.new
	r.InjectFunc = inst.inject
	return r.Commit()
}

func (inst* p9a99ad5d30_controllers_ConnectionController) new() any {
    return &p9a99ad5d3.ConnectionController{}
}

func (inst* p9a99ad5d30_controllers_ConnectionController) inject(injext application.InjectionExt, instance any) error {
	ie := injext
	com := instance.(*p9a99ad5d3.ConnectionController)
	nop(ie, com)

	
    com.Responder = inst.getResponder(ie)
    com.Service = inst.getService(ie)


    return nil
}


func (inst*p9a99ad5d30_controllers_ConnectionController) getResponder(ie application.InjectionExt)pd1a916a20.Responder{
    return ie.GetComponent("#alias-d1a916a203352fd5d33eabc36896b42e-Responder").(pd1a916a20.Responder)
}


func (inst*p9a99ad5d30_controllers_ConnectionController) getService(ie application.InjectionExt)p1e554a92e.ConnectionService{
    return ie.GetComponent("#alias-1e554a92e02558d082d6cfb8b5a85f00-ConnectionService").(p1e554a92e.ConnectionService)
}



// type p9a99ad5d3.ExampleController in package:github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/app/web/controllers
//
// id:com-9a99ad5d3031ef6f-controllers-ExampleController
// class:class-d1a916a203352fd5d33eabc36896b42e-Controller
// alias:
// scope:singleton
//
type p9a99ad5d30_controllers_ExampleController struct {
}

func (inst* p9a99ad5d30_controllers_ExampleController) register(cr application.ComponentRegistry) error {
	r := cr.NewRegistration()
	r.ID = "com-9a99ad5d3031ef6f-controllers-ExampleController"
	r.Classes = "class-d1a916a203352fd5d33eabc36896b42e-Controller"
	r.Aliases = ""
	r.Scope = "singleton"
	r.NewFunc = inst.new
	r.InjectFunc = inst.inject
	return r.Commit()
}

func (inst* p9a99ad5d30_controllers_ExampleController) new() any {
    return &p9a99ad5d3.ExampleController{}
}

func (inst* p9a99ad5d30_controllers_ExampleController) inject(injext application.InjectionExt, instance any) error {
	ie := injext
	com := instance.(*p9a99ad5d3.ExampleController)
	nop(ie, com)

	
    com.Responder = inst.getResponder(ie)


    return nil
}


func (inst*p9a99ad5d30_controllers_ExampleController) getResponder(ie application.InjectionExt)pd1a916a20.Responder{
    return ie.GetComponent("#alias-d1a916a203352fd5d33eabc36896b42e-Responder").(pd1a916a20.Responder)
}



// type p9a99ad5d3.SimpleTestController in package:github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/app/web/controllers
//
// id:com-9a99ad5d3031ef6f-controllers-SimpleTestController
// class:class-d1a916a203352fd5d33eabc36896b42e-Controller
// alias:
// scope:singleton
//
type p9a99ad5d30_controllers_SimpleTestController struct {
}

func (inst* p9a99ad5d30_controllers_SimpleTestController) register(cr application.ComponentRegistry) error {
	r := cr.NewRegistration()
	r.ID = "com-9a99ad5d3031ef6f-controllers-SimpleTestController"
	r.Classes = "class-d1a916a203352fd5d33eabc36896b42e-Controller"
	r.Aliases = ""
	r.Scope = "singleton"
	r.NewFunc = inst.new
	r.InjectFunc = inst.inject
	return r.Commit()
}

func (inst* p9a99ad5d30_controllers_SimpleTestController) new() any {
    return &p9a99ad5d3.SimpleTestController{}
}

func (inst* p9a99ad5d30_controllers_SimpleTestController) inject(injext application.InjectionExt, instance any) error {
	ie := injext
	com := instance.(*p9a99ad5d3.SimpleTestController)
	nop(ie, com)

	
    com.Responder = inst.getResponder(ie)
    com.TestService = inst.getTestService(ie)


    return nil
}


func (inst*p9a99ad5d30_controllers_SimpleTestController) getResponder(ie application.InjectionExt)pd1a916a20.Responder{
    return ie.GetComponent("#alias-d1a916a203352fd5d33eabc36896b42e-Responder").(pd1a916a20.Responder)
}


func (inst*p9a99ad5d30_controllers_SimpleTestController) getTestService(ie application.InjectionExt)p1e554a92e.TestService{
    return ie.GetComponent("#alias-1e554a92e02558d082d6cfb8b5a85f00-TestService").(p1e554a92e.TestService)
}


