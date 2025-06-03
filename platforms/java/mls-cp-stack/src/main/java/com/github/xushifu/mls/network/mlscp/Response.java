package com.github.xushifu.mls.network.mlscp;

import java.net.SocketAddress;
import java.util.List;

public final class Response {

    public final TransactionContext context;

    private ProtocolVersion version;
    private Status status;
    private SocketAddress remote;
    private ByteArraySlice data;
    private List<Block> blocks;

    public Response(TransactionContext ctx) {
        this.context = ctx;
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

    public Status getStatus() {
        return status;
    }

    public void setStatus(Status status) {
        this.status = status;
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
