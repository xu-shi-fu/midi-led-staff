package com.github.xushifu.mls.network.mlscp.blocks;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

import com.github.xushifu.mls.network.mlscp.BlockBody;
import com.github.xushifu.mls.network.mlscp.BlockType;

public class Int64Body implements BlockBody {

    private long value;

    public Int64Body() {
    }

    @Override
    public BlockType type() {
        return BlockType.INT64;
    }

    @Override
    public int length() {
        return 8;
    }

    @Override
    public void encode(DataOutput dst) throws IOException {
        dst.writeLong(this.value);
    }

    @Override
    public void decode(DataInput src) throws IOException {
        this.value = src.readLong();
    }

    public long getValue() {
        return value;
    }

    public void setValue(long value) {
        this.value = value;
    }

}
