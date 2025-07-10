package com.github.xushifu.mls.musical;

public class KeyboardRange {

    private int offset;
    private int count;

    // init default
    public KeyboardRange() {
    }

    // init with params
    public KeyboardRange(int off, int cnt) {
        this.offset = off;
        this.count = cnt;
    }

    // init as copy
    public KeyboardRange(KeyboardRange src) {
        if (src == null) {
            return;
        }
        this.offset = src.offset;
        this.count = src.count;
    }

    public int getOffset() {
        return offset;
    }

    public void setOffset(int offset) {
        this.offset = offset;
    }

    public int getCount() {
        return count;
    }

    public void setCount(int count) {
        this.count = count;
    }

}
