package com.github.xushifu.mls.client;

import java.io.Closeable;
import java.io.IOException;
import java.net.SocketAddress;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.bitwormhole.starter4j.application.Module;
import com.github.xushifu.mls.client.core.clients.ClientService;

public final class MLSClient implements Closeable {

    private final static Logger logger = LoggerFactory.getLogger(MLSClient.class);

    private final MLSClientContext context;

    private MLSClient(MLSClientContext ctx) {
        this.context = ctx;
    }

    public static MLSClient open(MLSClientConfig cfg) throws IOException {
        return open(null, cfg);
    }

    public static MLSClient open(MLSClientContext ctx, MLSClientConfig cfg) throws IOException {

        if (ctx == null) {
            ctx = new MLSClientContext();
        }

        if (cfg == null) {
            cfg = new MLSClientConfig();
        }

        MLSClient client = ctx.getClient();
        if (client == null) {
            client = new MLSClient(ctx);
        }

        ClientService.PingOptions opt = new ClientService.PingOptions();
        opt.setWaitForResponse(true);
        opt.setTimeout(cfg.getTimeout());

        ctx.setClient(client);
        ctx.setConfig(cfg);

        client = MLSClientFactory.initClientContext(ctx);
        client.getServices().getClientService().ping(opt);

        SocketAddress remote = ctx.getClientService().getUserAgent().getRemote();
        logger.info("connected to " + remote);
        return client;
    }

    public MLSClientConfig getConfig() {
        return context.getConfig();
    }

    public MLSClientServices getServices() {
        return context.getServices();
    }

    @Override
    public void close() throws IOException {
        context.getClientService().disconnect();
    }

    public static Module module() {
        return ThisModule.module();
    }
}
