package com.github.xushifu.mls.network.mlscp.blocks;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

import com.github.xushifu.mls.network.mlscp.ARGB;
import com.github.xushifu.mls.network.mlscp.BlockBody;
import com.github.xushifu.mls.network.mlscp.BlockType;

public class ArgbBody implements BlockBody {

    private ARGB value;

    public ArgbBody() {
    }

    public ARGB getValue() {
        return value;
    }

    public void setValue(ARGB value) {
        this.value = value;
    }

    @Override
    public BlockType type() {
        return BlockType.ARGB;
    }

    @Override
    public int length() {
        return 4;
    }

    @Override
    public void encode(DataOutput dst) throws IOException {
        ARGB v = this.value;
        if (v == null) {
            v = new ARGB();
        }
        byte[] buffer = new byte[] { v.a, v.r, v.g, v.b };
        dst.write(buffer, 0, buffer.length);
    }

    @Override
    public void decode(DataInput src) throws IOException {
        byte[] buffer = new byte[4];
        ARGB v = new ARGB();
        src.readFully(buffer);
        v.a = buffer[0];
        v.r = buffer[1];
        v.g = buffer[2];
        v.b = buffer[3];
        this.value = v;
    }

}
