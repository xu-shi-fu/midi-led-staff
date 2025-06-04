package com.github.xushifu.mls.network.mlscp.blocks;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

import com.github.xushifu.mls.network.mlscp.BlockBody;
import com.github.xushifu.mls.network.mlscp.BlockType;

public class ByteBody implements BlockBody {

    private byte value;

    public ByteBody() {
    }

    public byte getValue() {
        return value;
    }

    public void setValue(byte value) {
        this.value = value;
    }

    @Override
    public BlockType type() {
        return BlockType.BYTE;
    }

    @Override
    public int length() {
        return 1;
    }

    @Override
    public void encode(DataOutput dst) throws IOException {
        dst.writeByte(value);
    }

    @Override
    public void decode(DataInput src) throws IOException {
        this.value = src.readByte();
    }

}
