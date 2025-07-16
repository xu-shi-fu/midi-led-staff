package com.github.xushifu.mls.musical;

/***
 * 表示与平台无关的颜色值
 */
public class LightColor {

    private final int value;

    public LightColor() {
        this.value = 0;
    }

    public LightColor(int c) {
        this.value = c;
    }

    public static LightColor colorOf(int c) {
        return new LightColor(c);
    }

    public static LightColor notNull(LightColor c) {
        if (c == null) {
            c = new LightColor();
        }
        return c;
    }

    public int getValue() {
        return value;
    }

}
