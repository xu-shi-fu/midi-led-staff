package com.github.xushifu.mls.network.mlscp.blocks;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

import com.github.xushifu.mls.network.mlscp.BlockBody;
import com.github.xushifu.mls.network.mlscp.BlockType;

public class Float32Body implements BlockBody {

    private float value;

    public Float32Body() {
    }

    public float getValue() {
        return value;
    }

    public void setValue(float value) {
        this.value = value;
    }

    @Override
    public BlockType type() {
        return BlockType.FLOAT32;
    }

    @Override
    public int length() {
        return 4;
    }

    @Override
    public void encode(DataOutput dst) throws IOException {
        dst.writeFloat(value);
    }

    @Override
    public void decode(DataInput src) throws IOException {
        value = src.readFloat();
    }

}
