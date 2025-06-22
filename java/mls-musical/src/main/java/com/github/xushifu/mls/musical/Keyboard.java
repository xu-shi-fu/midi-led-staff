package com.github.xushifu.mls.musical;

public final class Keyboard implements KeySet {

    @Override
    public int getOffset() {
        return this.slice.getOffset();
    }

    @Override
    public int getCount() {
        return this.slice.getCount();
    }

    @Override
    public Key getKey(int index) {
        return this.slice.getKey(index);
    }

    public static Keyboard create(int offset, int count) {
        KeyArray array = Midi128Keys.array();
        KeyArraySlice sl = KeyArraySlice.create(array, offset, count);
        return new Keyboard(sl);
    }

    ////////////////////////////////////////////////////////////////////////////
    /// private
    ///

    private final KeyArraySlice slice;

    private Keyboard(KeyArraySlice sl) {
        this.slice = sl;
    }

}
