package com.github.xushifu.mls.network.mlscp.blocks;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

import com.github.xushifu.mls.network.mlscp.BlockBody;
import com.github.xushifu.mls.network.mlscp.BlockType;

public class ByteArrayBody implements BlockBody {

    private byte[] value;

    public ByteArrayBody() {
    }

    public byte[] getValue() {
        return value;
    }

    public void setValue(byte[] value) {
        this.value = value;
    }

    @Override
    public BlockType type() {
        return BlockType.BYTES;
    }

    @Override
    public int length() {
        byte[] array = this.value;
        if (array == null) {
            return 0;
        }
        return array.length;
    }

    public void setLength(int len) {
        if (len < 0) {
            len = 0;
        }
        this.value = new byte[len];
    }

    @Override
    public void encode(DataOutput dst) throws IOException {
        byte[] array = this.value;
        if (array == null) {
            return;
        }
        dst.write(array);
    }

    @Override
    public void decode(DataInput src) throws IOException {
        byte[] array = this.value;
        if (array == null) {
            return;
        }
        src.readFully(array);
    }

}
