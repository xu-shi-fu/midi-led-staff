package mlscp

import "fmt"

type PackParserHandler interface {
	OnBegin(parser *PackParser) error
	OnBlock(parser *PackParser, entity *BlockEntity) error
	OnEnd(parser *PackParser) error
	OnError(parser *PackParser, err error)
}

type PackParser struct{}

func (inst *PackParser) Parse(raw []byte, h PackParserHandler) error {
	err := inst.innerParse1(raw, h)
	if err != nil {
		h.OnError(inst, err)
	}
	return err
}

func (inst *PackParser) innerParse1(raw []byte, h PackParserHandler) error {

	err := h.OnBegin(inst)
	if err != nil {
		return err
	}

	err = inst.innerParse2(raw, h)
	if err != nil {
		return err
	}

	return h.OnEnd(inst)
}

func (inst *PackParser) innerParse2(raw []byte, h PackParserHandler) error {

	pos := 0
	end := len(raw)

	for pos < end {
		head, err := inst.readHeadAt(pos, raw)
		if err != nil {
			return err
		}

		next := pos + int(head.Size)

		if next > end {
			return fmt.Errorf("mlscp.PackParser : end at bad position")
		}

		entity, err := inst.makeEntity(pos, raw, head)
		if err != nil {
			return err
		}

		err = h.OnBlock(inst, entity)
		if err != nil {
			return err
		}

		pos = next
	}
	return nil
}

func (inst *PackParser) readHeadAt(pos int, raw []byte) (*BlockHead, error) {
	return nil, fmt.Errorf("no impl")
}

func (inst *PackParser) makeEntity(pos int, raw []byte, head *BlockHead) (*BlockEntity, error) {
	return nil, fmt.Errorf("no impl")
}
