package com.github.xushifu.mls.client.core.clients;

import java.io.IOException;

import com.github.xushifu.mls.client.MLSClient;
import com.github.xushifu.mls.client.MLSClientContext;
import com.github.xushifu.mls.client.RequestOptions;
import com.github.xushifu.mls.network.mlscp.UserAgent;

public interface ClientService {

    void connect() throws IOException;

    void disconnect() throws IOException;

    void ping(PingOptions options) throws IOException;

    void keepAlive(KeepAliveOptions options) throws IOException;

    MLSClient getClient();

    MLSClientContext getClientContext();

    UserAgent getUserAgent();

    static class PingOptions extends RequestOptions {
    }

    static class KeepAliveOptions extends RequestOptions {
    }

}
