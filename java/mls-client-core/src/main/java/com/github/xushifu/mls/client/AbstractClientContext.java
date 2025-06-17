package com.github.xushifu.mls.client;

import com.bitwormhole.starter4j.application.ApplicationContext;

public class AbstractClientContext implements ClientContext {

    private MLSClient client;
    private ApplicationContext applicationContext;
    private ClientContextHolder clientContextHolder;

    public AbstractClientContext() {
    }

    public MLSClient getClient() {
        return client;
    }

    public void setClient(MLSClient client) {
        this.client = client;
    }

    @Override
    public ApplicationContext getApplicationContext() {
        return applicationContext;
    }

    public void setApplicationContext(ApplicationContext applicationContext) {
        this.applicationContext = applicationContext;
    }

    @Override
    public ClientContextHolder getClientContextHolder() {
        return clientContextHolder;
    }

    public void setClientContextHolder(ClientContextHolder clientContextHolder) {
        this.clientContextHolder = clientContextHolder;
    }

}
