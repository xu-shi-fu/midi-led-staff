package com.github.xushifu.mls.network.mlscp;

public enum Method {

    GET, POST, PUT, DELETE,

    ;

    public static int toInt(Method m) {
        if (m == null) {
            return 0;
        } else if (m == GET) {
            return 1;
        } else if (m == POST) {
            return 2;
        } else if (m == PUT) {
            return 3;
        } else if (m == DELETE) {
            return 4;
        }
        return 0;
    }

}
