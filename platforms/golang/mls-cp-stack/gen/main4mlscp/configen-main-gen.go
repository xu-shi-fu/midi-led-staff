package main4mlscp

import "github.com/starter-go/application"

func nop(a ... any) {    
}

func registerComponents(cr application.ComponentRegistry) error {
    ac:=&autoRegistrar{}
    ac.init(cr)
    return ac.addAll()
}

type comFactory interface {
    register(cr application.ComponentRegistry) error
}

type autoRegistrar struct {
    cr application.ComponentRegistry
}

func (inst *autoRegistrar) init(cr application.ComponentRegistry) {
	inst.cr = cr
}

func (inst *autoRegistrar) register(factory comFactory) error {
	return factory.register(inst.cr)
}

func (inst*autoRegistrar) addAll() error {

    
    inst.register(&p9a99ad5d30_controllers_ConnectionController{})
    inst.register(&p9a99ad5d30_controllers_ExampleController{})
    inst.register(&p9a99ad5d30_controllers_TestController{})
    inst.register(&pb21ef5bbc1_impl_ConnectionServiceImpl{})


    return nil
}
