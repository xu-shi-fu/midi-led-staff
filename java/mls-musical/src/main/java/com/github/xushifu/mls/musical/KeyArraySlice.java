package com.github.xushifu.mls.musical;

public final class KeyArraySlice implements KeySet {

    @Override
    public int getOffset() {
        return this.offset;
    }

    @Override
    public int getCount() {
        return this.count;
    }

    @Override
    public Key getKey(int index) {
        final int end = this.offset + this.count;
        if (offset <= index && index < end) {
            return this.array.getKey(index);
        }
        return null;
    }

    public static KeyArraySlice create(Key[] array, int offset, int count) {
        Builder b = new Builder();
        b.off = offset;
        b.cnt = count;
        b.arr = KeyArray.create(array);
        return b.build();
    }

    public static KeyArraySlice create(KeyArray array, int offset, int count) {
        Builder b = new Builder();
        b.off = offset;
        b.cnt = count;
        b.arr = array;
        return b.build();
    }

    ////////////////////////////////////////////////////////////////////////////
    /// private

    private final int offset;
    private final int count;
    private final KeyArray array;

    private KeyArraySlice(Builder b) {
        this.offset = b.off;
        this.count = b.cnt;
        this.array = b.arr;
    }

    private final static class Builder {

        int off;
        int cnt;
        KeyArray arr;

        KeyArraySlice build() {
            return new KeyArraySlice(this);
        }
    }

}
