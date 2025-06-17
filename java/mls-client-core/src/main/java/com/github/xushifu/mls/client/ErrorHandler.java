package com.github.xushifu.mls.client;

public interface ErrorHandler {

    void onError(Throwable err) throws Throwable;

}
