package com.github.xushifu.mls.network.mlscp.blocks;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

import com.github.xushifu.mls.network.mlscp.ARGB;
import com.github.xushifu.mls.network.mlscp.BlockBody;
import com.github.xushifu.mls.network.mlscp.BlockType;

public class ArgbArrayBody implements BlockBody {

    private ARGB[] value;

    public ArgbArrayBody() {
    }

    public ARGB[] getValue() {
        return value;
    }

    public void setValue(ARGB[] value) {
        this.value = value;
    }

    @Override
    public BlockType type() {
        return BlockType.ARGB_ARRAY;
    }

    private final int count() {
        final ARGB[] list = this.value;
        if (list == null) {
            return 0;
        }
        return list.length;
    }

    @Override
    public int length() {
        final int c = this.count();
        return c * 4;
    }

    public void setLength(int len) {
        int cnt = len / 4;
        if (cnt < 0) {
            cnt = 0;
        }
        this.value = new ARGB[cnt];
    }

    @Override
    public void encode(DataOutput dst) throws IOException {
        final ARGB[] list = this.value;
        if (list == null) {
            return;
        }
        final int c = list.length;
        final ArgbBody body = new ArgbBody();
        for (int i = 0; i < c; i++) {
            body.setValue(list[i]);
            body.encode(dst);
        }
    }

    @Override
    public void decode(DataInput src) throws IOException {
        final int c = this.count();
        final ARGB[] all = new ARGB[c];
        final ArgbBody body = new ArgbBody();
        for (int i = 0; i < c; i++) {
            body.decode(src);
            all[i] = body.getValue();
        }
        this.value = all;
    }

}
