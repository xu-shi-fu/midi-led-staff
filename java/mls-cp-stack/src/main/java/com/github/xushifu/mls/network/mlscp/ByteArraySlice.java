package com.github.xushifu.mls.network.mlscp;

import java.util.Arrays;

public final class ByteArraySlice {

    private byte[] buffer;
    private int offset;
    private int length;

    public ByteArraySlice() {
        this.buffer = new byte[] {};
        this.offset = 0;
        this.length = 0;
    }

    public ByteArraySlice(byte[] d) {
        if (d == null) {
            d = new byte[0];
        }
        this.buffer = d;
        this.offset = 0;
        this.length = d.length;
    }

    public ByteArraySlice(byte[] d, int len) {
        this.buffer = d;
        this.offset = 0;
        this.length = len;
    }

    public ByteArraySlice(byte[] d, int off, int len) {
        this.buffer = d;
        this.offset = off;
        this.length = len;
    }

    public int getOffset() {
        return offset;
    }

    public void setOffset(int offset) {
        this.offset = offset;
    }

    public int getLength() {
        return length;
    }

    public void setLength(int length) {
        this.length = length;
    }

    public byte[] toBytes() {
        int from = this.offset;
        int to = this.offset + this.length;
        return Arrays.copyOfRange(this.buffer, from, to);
    }

    public byte[] getBuffer() {
        return buffer;
    }

    public void setBuffer(byte[] buffer) {
        this.buffer = buffer;
    }

}
