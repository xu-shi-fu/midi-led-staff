package com.github.xushifu.mls.network.mlscp.blocks;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

import com.github.xushifu.mls.network.mlscp.BlockBody;
import com.github.xushifu.mls.network.mlscp.BlockType;

public class Int32Body implements BlockBody {

    private int value;

    public Int32Body() {
    }

    @Override
    public BlockType type() {
        return BlockType.INT32;
    }

    @Override
    public int length() {
        return 4;
    }

    @Override
    public void encode(DataOutput dst) throws IOException {
        dst.writeInt(this.value);
    }

    @Override
    public void decode(DataInput src) throws IOException {
        this.value = src.readInt();
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

}
