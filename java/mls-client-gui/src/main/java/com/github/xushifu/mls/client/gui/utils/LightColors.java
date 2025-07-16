package com.github.xushifu.mls.client.gui.utils;

import com.github.xushifu.mls.musical.LightColor;

public final class LightColors {

    private LightColors() {
    }

    public static LightColor toLight(int c) {
        return LightColor.colorOf(c);
    }

    public static int toInt(LightColor lc) {
        if (lc == null) {
            return 0;
        }
        return lc.getValue();
    }
}
