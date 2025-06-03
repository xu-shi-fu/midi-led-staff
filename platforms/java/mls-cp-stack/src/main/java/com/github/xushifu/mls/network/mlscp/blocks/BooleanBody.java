package com.github.xushifu.mls.network.mlscp.blocks;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

import com.github.xushifu.mls.network.mlscp.BlockBody;
import com.github.xushifu.mls.network.mlscp.BlockType;

public class BooleanBody implements BlockBody {

    private boolean value;

    public BooleanBody() {
    }

    public boolean isValue() {
        return value;
    }

    public void setValue(boolean value) {
        this.value = value;
    }

    @Override
    public BlockType type() {
        return BlockType.BOOL;
    }

    @Override
    public int length() {
        return 1;
    }

    @Override
    public void encode(DataOutput dst) throws IOException {
        dst.writeBoolean(value);
    }

    @Override
    public void decode(DataInput src) throws IOException {
        value = src.readBoolean();
    }

}
