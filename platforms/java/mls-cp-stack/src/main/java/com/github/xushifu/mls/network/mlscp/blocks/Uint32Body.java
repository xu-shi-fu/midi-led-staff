package com.github.xushifu.mls.network.mlscp.blocks;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

import com.github.xushifu.mls.network.mlscp.BlockBody;
import com.github.xushifu.mls.network.mlscp.BlockType;

public class Uint32Body implements BlockBody {

    private int value;

    public Uint32Body() {
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    @Override
    public BlockType type() {
        return BlockType.UINT32;
    }

    @Override
    public int length() {
        return 4;
    }

    @Override
    public void encode(DataOutput dst) throws IOException {
        dst.writeInt(value);
    }

    @Override
    public void decode(DataInput src) throws IOException {
        value = src.readInt();
    }

}
