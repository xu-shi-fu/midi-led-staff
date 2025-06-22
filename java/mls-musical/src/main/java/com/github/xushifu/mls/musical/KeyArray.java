package com.github.xushifu.mls.musical;

public final class KeyArray implements KeySet {

    @Override
    public Key getKey(int index) {
        return this.array[index];
    }

    public void setKey(int index, Key key) {
        this.setKey(index, key, false);
    }

    public void setKey(int index, Key key, boolean canBeNull) {
        if (key == null) {
            if (!canBeNull) {
                return;
            }
        }
        this.array[index] = key;
    }

    @Override
    public int getOffset() {
        return 0; // KeyArray 没有偏移量
    }

    @Override
    public int getCount() {
        return this.array.length;
    }

    public static KeyArray create(Key[] array) {
        return new KeyArray(array);
    }

    ////////////////////////////////////////////////////////////////////////////
    /// private

    private final Key[] array;

    private KeyArray(Key[] a) {
        if (a == null) {
            a = new Key[0]; // 确保不为 null
        }
        this.array = a;
    }

}
