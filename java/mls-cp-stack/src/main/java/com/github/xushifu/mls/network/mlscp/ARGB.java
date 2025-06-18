package com.github.xushifu.mls.network.mlscp;

public final class ARGB {

    public byte a;
    public byte r;
    public byte g;
    public byte b;

    private final static ARGB theEmpty = new ARGB();

    public ARGB() {
    }

    public ARGB(ARGB src) {
        if (src == null) {
            return;
        }
        this.a = src.a;
        this.r = src.r;
        this.g = src.g;
        this.b = src.b;
    }

    public static ARGB empty() {
        return theEmpty;
    }

    public static ARGB normalize(ARGB color) {
        if (color == null) {
            color = empty();
        }
        return color;
    }

}
