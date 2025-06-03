package com.github.xushifu.mls.utils;

public final class Strings {

    private Strings() {
    }

    public static boolean equal(String s1, String s2) {
        if (s1 == null || s2 == null) {
            return false;
        }
        return s1.equals(s2);
    }

    public static String useEmpty(String str) {
        if (str == null) {
            return "";
        }
        return str;
    }

    public static String useNull(String str) {
        if (str == null) {
            return null;
        }
        if (str.isEmpty()) {
            return null;
        }
        return str;
    }

}
