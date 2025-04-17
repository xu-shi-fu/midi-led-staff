package mlscp

type RTXFilter interface {
	RxFilter
	TxFilter
}

type RTX struct {
	Rx RxFilterChain
	Tx TxFilterChain
}

type RTXFilterConfig interface {
	GetFilters() []RTXFilter
}

////////////////////////////////////////////////////////////////////////////////

type RTXFilterList struct {
	items []RTXFilter
}

func (inst *RTXFilterList) _impl() RTXFilterConfig {
	return inst
}

func (inst *RTXFilterList) Add(f RTXFilter) {
	if f == nil {
		return
	}
	inst.items = append(inst.items, f)
}

func (inst *RTXFilterList) GetFilters() []RTXFilter {
	return inst.items
}

////////////////////////////////////////////////////////////////////////////////

type RTXBuilder struct {
	filters []RTXFilter
}

func (inst *RTXBuilder) Add(f RTXFilter) {
	if f == nil {
		return
	}
	inst.filters = append(inst.filters, f)
}

func (inst *RTXBuilder) Build() *RTX {

	rxb := &RxFilterChainBuilder{}
	txb := &TxFilterChainBuilder{}
	all := inst.filters

	for _, item := range all {
		txb.Add(item)
	}

	for i := len(all) - 1; i >= 0; i-- {
		item := all[i]
		rxb.Add(item)
	}

	result := &RTX{}
	result.Rx = rxb.Build()
	result.Tx = txb.Build()
	return result
}

////////////////////////////////////////////////////////////////////////////////
