package com.github.xushifu.mls.client;

import com.github.xushifu.mls.client.core.clients.ClientService;
import com.github.xushifu.mls.client.core.leds.LEDService;
import com.github.xushifu.mls.network.mlscp.UserAgent;

public final class MLSClientContext {

    private MLSClient client;
    private MLSClientConfig config;
    private UserAgent useragent;

    // services

    private MLSClientServices services;

    private LEDService ledService;
    private ClientService clientService;

    public MLSClientContext() {
    }

    public MLSClient getClient() {
        return client;
    }

    public void setClient(MLSClient client) {
        this.client = client;
    }

    public UserAgent getUseragent() {
        return useragent;
    }

    public void setUseragent(UserAgent useragent) {
        this.useragent = useragent;
    }

    public MLSClientConfig getConfig() {
        return config;
    }

    public void setConfig(MLSClientConfig config) {
        this.config = config;
    }

    public LEDService getLedService() {
        return ledService;
    }

    public void setLedService(LEDService ledService) {
        this.ledService = ledService;
    }

    public ClientService getClientService() {
        return clientService;
    }

    public void setClientService(ClientService clientService) {
        this.clientService = clientService;
    }

    public MLSClientServices getServices() {
        return services;
    }

    public void setServices(MLSClientServices services) {
        this.services = services;
    }

}
