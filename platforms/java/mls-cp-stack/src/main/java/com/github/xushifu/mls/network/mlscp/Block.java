package com.github.xushifu.mls.network.mlscp;

import com.github.xushifu.mls.network.mlscp.blocks.BooleanBody;

public final class Block {

    private final BlockHead head;
    private BlockBody body;

    public Block() {
        this.head = new BlockHead();
    }

    public BlockHead getHead() {
        return head;
    }

    public BlockBody getBody() {
        return body;
    }

    public void setBody(BlockBody body) {
        this.body = body;
    }

    public static Block create(BlockGroup g, BlockField f, BlockBody body) {

        if (g == null || f == null) {
            g = BlockGroup.COMMON;
            f = BlockField.COMMON_reserved;
        }
        if (body == null) {
            body = new BooleanBody();
        }

        final int head_size = 4;
        Block b = new Block();
        b.head.setSize(head_size + body.length());
        b.head.setType(body.type());
        b.head.setGroup(g);
        b.head.setField(f);
        b.body = body;
        return b;
    }

}
