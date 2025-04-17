package test4mlscp
import (
    pd1a916a20 "github.com/starter-go/libgin"
    p3be6aaa1d "github.com/xu-shi-fu/midi-led-staff/platforms/golang/mls-cp-stack/src/test/golang/t"
     "github.com/starter-go/application"
)

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


