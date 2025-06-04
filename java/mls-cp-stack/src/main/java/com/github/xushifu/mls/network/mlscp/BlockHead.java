package com.github.xushifu.mls.network.mlscp;

public final class BlockHead {

    /**
     * block_size = sizeof(head) + sizeof(body)
     **/
    private int size;

    private BlockType type;
    private BlockGroup group;
    private BlockField field;

    public BlockHead() {
    }

    public int getSize() {
        return size;
    }

    public void setSize(int size) {
        this.size = size;
    }

    public BlockType getType() {
        return type;
    }

    public void setType(BlockType type) {
        this.type = type;
    }

    public BlockGroup getGroup() {
        return group;
    }

    public void setGroup(BlockGroup group) {
        this.group = group;
    }

    public BlockField getField() {
        return field;
    }

    public void setField(BlockField field) {
        this.field = field;
    }

}
