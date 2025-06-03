package com.github.xushifu.mls.network.mlscp;

import java.net.SocketAddress;
import java.util.List;

public final class Request {

    public final TransactionContext context;

    private ProtocolVersion version;
    private Method method;
    private Location location;
    private SocketAddress remote;
    private ByteArraySlice data;
    private List<Block> blocks;

    public Request(TransactionContext ctx) {
        this.context = ctx;
    }

    public Method getMethod() {
        return method;
    }

    public void setMethod(Method method) {
        this.method = method;
    }

    public Location getLocation() {
        return location;
    }

    public void setLocation(Location location) {
        this.location = location;
    }

    public TransactionContext getContext() {
        return context;
    }

    public ProtocolVersion getVersion() {
        return version;
    }

    public void setVersion(ProtocolVersion version) {
        this.version = version;
    }

    public List<Block> getBlocks() {
        return blocks;
    }

    public void setBlocks(List<Block> blocks) {
        this.blocks = blocks;
    }

    public SocketAddress getRemote() {
        return remote;
    }

    public void setRemote(SocketAddress remote) {
        this.remote = remote;
    }

    public ByteArraySlice getData() {
        return data;
    }

    public void setData(ByteArraySlice data) {
        this.data = data;
    }

}
