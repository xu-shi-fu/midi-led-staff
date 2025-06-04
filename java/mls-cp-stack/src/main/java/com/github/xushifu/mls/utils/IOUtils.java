package com.github.xushifu.mls.utils;

import java.io.Closeable;

public final class IOUtils {

    public static void close(Closeable c) {
        if (c == null) {
            return;
        }
        try {
            c.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}
