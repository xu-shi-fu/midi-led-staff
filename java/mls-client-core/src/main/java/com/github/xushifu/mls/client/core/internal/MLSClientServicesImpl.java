package com.github.xushifu.mls.client.core.internal;

import com.github.xushifu.mls.client.MLSClientContext;
import com.github.xushifu.mls.client.MLSClientServices;
import com.github.xushifu.mls.client.core.clients.ClientService;
import com.github.xushifu.mls.client.core.leds.LEDService;

public class MLSClientServicesImpl implements MLSClientServices {

    private final MLSClientContext context;

    public MLSClientServicesImpl(MLSClientContext ctx) {
        this.context = ctx;
    }

    @Override
    public ClientService getClientService() {
        return context.getClientService();
    }

    @Override
    public LEDService getLEDService() {
        return context.getLedService();
    }
}
