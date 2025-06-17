package com.github.xushifu.mls.utils;

public final class ErrorUtils {

    public static RuntimeException wrapWithRuntimeException(Throwable err) {
        if (err == null) {
            return new RuntimeException("[err=null]");
        } else if (err instanceof RuntimeException) {
            return (RuntimeException) err;
        }
        return new RuntimeException(err);
    }

}
