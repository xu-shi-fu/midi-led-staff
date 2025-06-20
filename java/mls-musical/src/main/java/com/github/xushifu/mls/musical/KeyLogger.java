package com.github.xushifu.mls.musical;

public final class KeyLogger {

    private KeyLogger() {
    }

    public static String stringify(Key key) {

        StringBuilder sb = new StringBuilder();

        sb.append("[musical.Key");
        sb.append(" index:").append(key.getIndex());
        sb.append(" group:").append(key.getGroup());
        sb.append(" tone:").append(key.getTone());
        sb.append(" freq:").append(key.getFrequency());
        sb.append(" text:").append(key.toString());
        sb.append("]");

        return sb.toString();
    }

}
