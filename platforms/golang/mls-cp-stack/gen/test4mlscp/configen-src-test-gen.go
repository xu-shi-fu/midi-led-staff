package test4mlscp
import (
    pd1a916a20 "github.com/starter-go/libgin"
    p1e554a92e "github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/app/services"
    p3be6aaa1d "github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/src/test/golang/t"
     "github.com/starter-go/application"
)

// type p3be6aaa1d.TestController in package:github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/src/test/golang/t
//
// id:com-3be6aaa1d92e2877-t-TestController
// class:class-d1a916a203352fd5d33eabc36896b42e-Controller
// alias:
// scope:singleton
//
type p3be6aaa1d9_t_TestController struct {
}

func (inst* p3be6aaa1d9_t_TestController) register(cr application.ComponentRegistry) error {
	r := cr.NewRegistration()
	r.ID = "com-3be6aaa1d92e2877-t-TestController"
	r.Classes = "class-d1a916a203352fd5d33eabc36896b42e-Controller"
	r.Aliases = ""
	r.Scope = "singleton"
	r.NewFunc = inst.new
	r.InjectFunc = inst.inject
	return r.Commit()
}

func (inst* p3be6aaa1d9_t_TestController) new() any {
    return &p3be6aaa1d.TestController{}
}

func (inst* p3be6aaa1d9_t_TestController) inject(injext application.InjectionExt, instance any) error {
	ie := injext
	com := instance.(*p3be6aaa1d.TestController)
	nop(ie, com)

	
    com.Responder = inst.getResponder(ie)
    com.ConnectionService = inst.getConnectionService(ie)
    com.TestService = inst.getTestService(ie)


    return nil
}


func (inst*p3be6aaa1d9_t_TestController) getResponder(ie application.InjectionExt)pd1a916a20.Responder{
    return ie.GetComponent("#alias-d1a916a203352fd5d33eabc36896b42e-Responder").(pd1a916a20.Responder)
}


func (inst*p3be6aaa1d9_t_TestController) getConnectionService(ie application.InjectionExt)p1e554a92e.ConnectionService{
    return ie.GetComponent("#alias-1e554a92e02558d082d6cfb8b5a85f00-ConnectionService").(p1e554a92e.ConnectionService)
}


func (inst*p3be6aaa1d9_t_TestController) getTestService(ie application.InjectionExt)p1e554a92e.TestService{
    return ie.GetComponent("#alias-1e554a92e02558d082d6cfb8b5a85f00-TestService").(p1e554a92e.TestService)
}



// type p3be6aaa1d.TestClientUnit in package:github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/src/test/golang/t
//
// id:com-3be6aaa1d92e2877-t-TestClientUnit
// class:class-0dc072ed44b3563882bff4e657a52e62-Units
// alias:
// scope:singleton
//
type p3be6aaa1d9_t_TestClientUnit struct {
}

func (inst* p3be6aaa1d9_t_TestClientUnit) register(cr application.ComponentRegistry) error {
	r := cr.NewRegistration()
	r.ID = "com-3be6aaa1d92e2877-t-TestClientUnit"
	r.Classes = "class-0dc072ed44b3563882bff4e657a52e62-Units"
	r.Aliases = ""
	r.Scope = "singleton"
	r.NewFunc = inst.new
	r.InjectFunc = inst.inject
	return r.Commit()
}

func (inst* p3be6aaa1d9_t_TestClientUnit) new() any {
    return &p3be6aaa1d.TestClientUnit{}
}

func (inst* p3be6aaa1d9_t_TestClientUnit) inject(injext application.InjectionExt, instance any) error {
	ie := injext
	com := instance.(*p3be6aaa1d.TestClientUnit)
	nop(ie, com)

	
    com.ConnectionService = inst.getConnectionService(ie)


    return nil
}


func (inst*p3be6aaa1d9_t_TestClientUnit) getConnectionService(ie application.InjectionExt)p1e554a92e.ConnectionService{
    return ie.GetComponent("#alias-1e554a92e02558d082d6cfb8b5a85f00-ConnectionService").(p1e554a92e.ConnectionService)
}



// type p3be6aaa1d.TestExampleController in package:github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/src/test/golang/t
//
// id:com-3be6aaa1d92e2877-t-TestExampleController
// class:class-d1a916a203352fd5d33eabc36896b42e-Controller
// alias:
// scope:singleton
//
type p3be6aaa1d9_t_TestExampleController struct {
}

func (inst* p3be6aaa1d9_t_TestExampleController) register(cr application.ComponentRegistry) error {
	r := cr.NewRegistration()
	r.ID = "com-3be6aaa1d92e2877-t-TestExampleController"
	r.Classes = "class-d1a916a203352fd5d33eabc36896b42e-Controller"
	r.Aliases = ""
	r.Scope = "singleton"
	r.NewFunc = inst.new
	r.InjectFunc = inst.inject
	return r.Commit()
}

func (inst* p3be6aaa1d9_t_TestExampleController) new() any {
    return &p3be6aaa1d.TestExampleController{}
}

func (inst* p3be6aaa1d9_t_TestExampleController) inject(injext application.InjectionExt, instance any) error {
	ie := injext
	com := instance.(*p3be6aaa1d.TestExampleController)
	nop(ie, com)

	
    com.Responder = inst.getResponder(ie)


    return nil
}


func (inst*p3be6aaa1d9_t_TestExampleController) getResponder(ie application.InjectionExt)pd1a916a20.Responder{
    return ie.GetComponent("#alias-d1a916a203352fd5d33eabc36896b42e-Responder").(pd1a916a20.Responder)
}


