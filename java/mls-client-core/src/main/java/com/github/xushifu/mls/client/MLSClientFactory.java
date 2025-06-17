package com.github.xushifu.mls.client;

import java.io.IOException;

import com.github.xushifu.mls.client.core.internal.ClientServiceImpl;
import com.github.xushifu.mls.client.core.internal.LEDServiceImpl;
import com.github.xushifu.mls.client.core.internal.MLSClientServicesImpl;

final class MLSClientFactory {

    public static MLSClient initClientContext(MLSClientContext ctx) throws IOException {

        MLSClient client = ctx.getClient();

        // todo ...

        ctx.setLedService(new LEDServiceImpl(ctx));
        ctx.setClientService(new ClientServiceImpl(ctx));

        ctx.setServices(new MLSClientServicesImpl(ctx));

        // connect
        ctx.getClientService().connect();

        return client;
    }

}
