package com.github.xushifu.mls.client.gui.utils;

import java.awt.Color;

import com.github.xushifu.mls.musical.LightColor;
import com.github.xushifu.mls.network.mlscp.ARGB;

public final class Colors {

    // 说明:
    // ARGB 用于网络通信;
    // awt.Color 用于UI显示;
    // LightColor 用于运行时数据;
    // 这里 : int(awt.Color) == int(LightColor)

    private Colors() {
    }

    public static ARGB toARGB(Color c) {
        if (c == null) {
            return new ARGB();
        }
        ARGB x = new ARGB();
        x.a = (byte) c.getAlpha();
        x.r = (byte) c.getRed();
        x.g = (byte) c.getGreen();
        x.b = (byte) c.getBlue();
        return x;
    }

    public static Color toAWT(ARGB argb) {
        if (argb == null) {
            return new Color(0);
        }
        int a = argb.a & 0xff;
        int r = argb.r & 0xff;
        int g = argb.g & 0xff;
        int b = argb.b & 0xff;
        return new Color(r, g, b, a);
    }

    public static Color toAWT(LightColor lc) {
        int n = LightColors.toInt(lc);
        return AWTColors.toColor(n);
    }

    public static LightColor toLight(Color c) {
        int n = AWTColors.toInt(c);
        return LightColor.colorOf(n);
    }

    public static LightColor toLight(ARGB argb) {
        // argb -> awt -> lc
        Color c1 = toAWT(argb);
        return toLight(c1);
    }

    public static ARGB toARGB(LightColor lc) {
        // lc -> awt -> argb
        Color c1 = toAWT(lc);
        return toARGB(c1);
    }

}
