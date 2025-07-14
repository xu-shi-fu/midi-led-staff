package com.github.xushifu.mls.client.gui.utils;

import java.awt.Color;

import com.github.xushifu.mls.network.mlscp.ARGB;

public final class Colors {

    private Colors() {
    }

    public static Color toColor(int n) {
        return new Color(n);
    }

    public static ARGB toARGB(int n) {
        ARGB res = new ARGB();
        res.a = (byte) (0xff & (n >> 24));
        res.r = (byte) (0xff & (n >> 16));
        res.g = (byte) (0xff & (n >> 8));
        res.b = (byte) (0xff & (n >> 0));
        return res;
    }

    public static int toInt(Color c) {
        if (c == null) {
            return 0;
        }
        return c.getRGB();
    }

    public static int toInt(ARGB argb) {
        int n = 0;
        n = (n << 8) | (0xff & argb.a);
        n = (n << 8) | (0xff & argb.r);
        n = (n << 8) | (0xff & argb.g);
        n = (n << 8) | (0xff & argb.b);
        return n;
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

    public static Color toColor(ARGB argb) {
        if (argb == null) {
            return new Color(0);
        }
        int a = argb.a & 0xff;
        int r = argb.r & 0xff;
        int g = argb.g & 0xff;
        int b = argb.b & 0xff;
        return new Color(r, g, b, a);
    }

}
