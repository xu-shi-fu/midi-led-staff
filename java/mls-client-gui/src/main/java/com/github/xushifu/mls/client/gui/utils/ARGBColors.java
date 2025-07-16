package com.github.xushifu.mls.client.gui.utils;

import com.github.xushifu.mls.network.mlscp.ARGB;

public class ARGBColors {

    public static ARGB toARGB(int n) {
        ARGB res = new ARGB();
        res.a = (byte) (0xff & (n >> 24));
        res.r = (byte) (0xff & (n >> 16));
        res.g = (byte) (0xff & (n >> 8));
        res.b = (byte) (0xff & (n >> 0));
        return res;
    }

    public static int toInt(ARGB argb) {
        int n = 0;
        n = (n << 8) | (0xff & argb.a);
        n = (n << 8) | (0xff & argb.r);
        n = (n << 8) | (0xff & argb.g);
        n = (n << 8) | (0xff & argb.b);
        return n;
    }

}
