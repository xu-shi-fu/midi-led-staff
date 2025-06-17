package com.github.xushifu.mls.client.core.internal;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.SocketAddress;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.github.xushifu.mls.client.MLSClient;
import com.github.xushifu.mls.client.MLSClientConfig;
import com.github.xushifu.mls.client.MLSClientContext;
import com.github.xushifu.mls.client.ResponseWaiter;
import com.github.xushifu.mls.client.core.clients.ClientService;
import com.github.xushifu.mls.client.core.clients.DoGetPingCodec;
import com.github.xushifu.mls.client.core.leds.LEDService.PushOptions;
import com.github.xushifu.mls.network.mlscp.Request;
import com.github.xushifu.mls.network.mlscp.TransactionContext;
import com.github.xushifu.mls.network.mlscp.UserAgent;
import com.github.xushifu.mls.network.mlscp.UserAgentBuilder;

public class ClientServiceImpl implements ClientService {

    private final static Logger logger = LoggerFactory.getLogger(ClientServiceImpl.class);

    private final MLSClientContext context;

    public ClientServiceImpl(MLSClientContext ctx) {
        this.context = ctx;
    }

    @Override
    public void connect() throws IOException {

        MLSClientConfig cfg = this.context.getConfig();
        UserAgentBuilder uab = UserAgentBuilder.newInstance();

        uab.setRemote(getRemoteAddress(cfg));
        uab.setLocal(getLocalAddress(cfg));

        UserAgent agent = uab.open();
        this.context.setUseragent(agent);
    }

    private static SocketAddress getRemoteAddress(MLSClientConfig cfg) {
        String host = cfg.getServerHost();
        int port = cfg.getServerPort();
        return new InetSocketAddress(host, port);
    }

    private static SocketAddress getLocalAddress(MLSClientConfig cfg) {
        String host = "0.0.0.0";
        int port = cfg.getClientPort();
        return new InetSocketAddress(host, port);
    }

    @Override
    public void disconnect() throws IOException {
        UserAgent ua = this.context.getUseragent();
        if (ua == null) {
            return;
        }
        ua.close();
    }

    @Override
    public MLSClient getClient() {
        return this.context.getClient();
    }

    @Override
    public MLSClientContext getClientContext() {
        return this.context;
    }

    @Override
    public UserAgent getUserAgent() {
        return this.context.getUseragent();
    }

    @Override
    public void ping(PingOptions options) throws IOException {

        if (options == null) {
            options = new PingOptions();
        }

        final ResponseWaiter waiter = new ResponseWaiter(options);
        final DoGetPingCodec codec = new DoGetPingCodec();
        final DoGetPingCodec.Params params = new DoGetPingCodec.Params();
        final UserAgent agent = context.getUseragent();

        params.agent = agent;
        Request req = codec.encodeRequest(params);
        TransactionContext tc = req.getContext();
        waiter.setupHandler(tc, (tc2) -> {
            DoGetPingCodec.Result res = codec.decodeResponse(tc2.getResponse());
            logger.debug("" + res);
        });

        try {
            agent.getDispatcher().dispatch(tc);
            waiter.tryWait();
        } catch (Exception e) {
            waiter.handleError(e);
            throw new RuntimeException(e);
        }
    }

    @Override
    public void keepAlive(KeepAliveOptions options) throws IOException {

        if (options == null) {
            options = new KeepAliveOptions();
        }

        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'keepAlive'");
    }

}
