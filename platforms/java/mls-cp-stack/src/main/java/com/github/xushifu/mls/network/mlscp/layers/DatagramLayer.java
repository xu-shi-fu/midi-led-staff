package com.github.xushifu.mls.network.mlscp.layers;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketAddress;

import com.github.xushifu.mls.network.mlscp.ByteArraySlice;
import com.github.xushifu.mls.network.mlscp.Client;
import com.github.xushifu.mls.network.mlscp.Layer;
import com.github.xushifu.mls.network.mlscp.Request;
import com.github.xushifu.mls.network.mlscp.RxFilterChain;
import com.github.xushifu.mls.network.mlscp.Stack;
import com.github.xushifu.mls.network.mlscp.StackRuntime;
import com.github.xushifu.mls.network.mlscp.TransactionContext;
import com.github.xushifu.mls.network.mlscp.TxFilterChain;

public class DatagramLayer implements Layer {

    public DatagramLayer() {
    }

    @Override
    public void receive(TransactionContext ctx, RxFilterChain next) throws Exception {
        // NOP
        next.receive(ctx);
    }

    @Override
    public void send(TransactionContext ctx, TxFilterChain next) throws Exception {

        Request req = ctx.getRequest();
        ByteArraySlice data = req.getData();
        SocketAddress addr = req.getRemote();

        if (addr == null) {
            addr = this.getDefaultRemoteAddress(ctx);
        }

        Stack stack = ctx.getStack();
        StackRuntime rt = stack.runtime;
        DatagramSocket sock = rt.getSocket();
        DatagramPacket pack = new DatagramPacket(data.getBuffer(), data.getOffset(), data.getLength(), addr);

        sock.send(pack);
        next.send(ctx);
    }

    private SocketAddress getDefaultRemoteAddress(TransactionContext ctx) {
        Stack stack = ctx.getStack();
        Client client = stack.client;
        return client.getRemote();
    }

}
