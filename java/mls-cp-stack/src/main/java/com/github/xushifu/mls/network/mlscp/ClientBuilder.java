package com.github.xushifu.mls.network.mlscp;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.util.ArrayList;
import java.util.List;

public abstract class ClientBuilder {

    private SocketAddress remote;
    private SocketAddress local;
    private List<Layer> layers;
    private int timeout;

    protected ClientBuilder() {

        this.local = InetSocketAddress.createUnresolved("0.0.0.0", 1001);
        this.remote = InetSocketAddress.createUnresolved("0.0.0.0", 1002);
        this.timeout = 30 * 1000; // 默认为 30s

    }

    public static ClientBuilder newInstance() {
        ClientBuilderFactory factory = new DefaultClientBuilderFactory();
        return factory.createBuilder();
    }

    public abstract Client open() throws IOException;

    public List<Layer> getLayers(boolean autoCreate) {
        List<Layer> list = this.layers;
        if (list == null) {
            list = new ArrayList<>();
            this.layers = list;
        }
        return list;
    }

    public ClientBuilder addLayer(Layer l) {
        if (l != null) {
            List<Layer> all = this.getLayers(true);
            all.add(l);
        }
        return this;
    }

    public ClientBuilder config(Configuration cfg) {
        this.local = InetSocketAddress.createUnresolved("0.0.0.0", cfg.localPort);
        this.remote = InetSocketAddress.createUnresolved(cfg.remoteHost, cfg.remotePort);
        return this;
    }

    public SocketAddress getRemote() {
        return remote;
    }

    public void setRemote(SocketAddress remote) {
        this.remote = remote;
    }

    public SocketAddress getLocal() {
        return local;
    }

    public void setLocal(SocketAddress local) {
        this.local = local;
    }

    public List<Layer> getLayers() {
        return layers;
    }

    public void setLayers(List<Layer> layers) {
        this.layers = layers;
    }

    public int getTimeout() {
        return timeout;
    }

    public void setTimeout(int timeout) {
        this.timeout = timeout;
    }

}
