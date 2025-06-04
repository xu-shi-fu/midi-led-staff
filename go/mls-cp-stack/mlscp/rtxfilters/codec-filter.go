package rtxfilters

import "github.com/xu-shi-fu/midi-led-staff/go/mls-cp-stack/mlscp"

type CodecFilter struct {
}

func (inst *CodecFilter) _impl() mlscp.RTXFilter {
	return inst
}

func (inst *CodecFilter) Rx(resp *mlscp.Response, chain mlscp.RxFilterChain) error {
	return chain.Rx(resp)
}

func (inst *CodecFilter) Tx(req *mlscp.Request, chain mlscp.TxFilterChain) error {

	encoder := &mlscp.Encoder{}
	data, err := encoder.EncodeRequest(req)
	if err != nil {
		return err
	}
	req.Data = data

	return chain.Tx(req)
}
