package com.github.xushifu.mls.utils;

public final class TimeUtils {

    public static void sleep(long ms) {
        try {
            Thread.sleep(ms);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

}
