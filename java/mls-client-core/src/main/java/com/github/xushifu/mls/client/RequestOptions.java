package com.github.xushifu.mls.client;

import com.github.xushifu.mls.network.mlscp.Handler;

public class RequestOptions {

    private boolean waitForResponse;
    private Handler responseHandler;
    private ErrorHandler errorHandler;
    private int timeout;

    public RequestOptions() {
        this.waitForResponse = true;
        this.timeout = 10000;
    }

    public boolean isWaitForResponse() {
        return waitForResponse;
    }

    public void setWaitForResponse(boolean waitForResponse) {
        this.waitForResponse = waitForResponse;
    }

    public int getTimeout() {
        return timeout;
    }

    public void setTimeout(int timeout) {
        this.timeout = timeout;
    }

    public ErrorHandler getErrorHandler() {
        return errorHandler;
    }

    public void setErrorHandler(ErrorHandler errorHandler) {
        this.errorHandler = errorHandler;
    }

    public Handler getResponseHandler() {
        return responseHandler;
    }

    public void setResponseHandler(Handler responseHandler) {
        this.responseHandler = responseHandler;
    }

}
