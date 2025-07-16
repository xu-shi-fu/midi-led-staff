package com.github.xushifu.mls.client.gui.utils;

import java.awt.Color;

public class AWTColors {

    public static Color toColor(int n) {
        return new Color(n);
    }

    public static int toInt(Color c) {
        if (c == null) {
            return 0;
        }
        return c.getRGB();
    }

}
