package com.github.xushifu.mls.network.mlscp.blocks;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

import com.github.xushifu.mls.network.mlscp.BlockBody;
import com.github.xushifu.mls.network.mlscp.BlockType;

public class Uint16Body implements BlockBody {

    private short value;

    public Uint16Body() {
    }

    @Override
    public BlockType type() {
        return BlockType.UINT16;
    }

    @Override
    public int length() {
        return 2;
    }

    @Override
    public void encode(DataOutput dst) throws IOException {
        dst.writeShort(value);
    }

    @Override
    public void decode(DataInput src) throws IOException {
        value = src.readShort();
    }

    public short getValue() {
        return value;
    }

    public void setValue(short value) {
        this.value = value;
    }

}
