package com.github.xushifu.mls.network.mlscp;

public final class TransactionContext {

    private Request request;
    private Response response;
    private Stack stack;
    private TransactionID id;
    private Handler handler;
    private Throwable error;

    /**
     * in milliseconds
     **/
    private int timeout;

    public TransactionContext() {
    }

    public Request getRequest() {
        return request;
    }

    public void setRequest(Request request) {
        this.request = request;
    }

    public Response getResponse() {
        return response;
    }

    public void setResponse(Response response) {
        this.response = response;
    }

    public Stack getStack() {
        return stack;
    }

    public void setStack(Stack stack) {
        this.stack = stack;
    }

    public TransactionID getId() {
        return id;
    }

    public void setId(TransactionID id) {
        this.id = id;
    }

    public Handler getHandler() {
        return handler;
    }

    public void setHandler(Handler handler) {
        this.handler = handler;
    }

    public int getTimeout() {
        return timeout;
    }

    public void setTimeout(int timeout) {
        this.timeout = timeout;
    }

    public Throwable getError() {
        return error;
    }

    public void setError(Throwable error) {
        this.error = error;
    }

}
