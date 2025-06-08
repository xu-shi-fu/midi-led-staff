package com.github.xushifu.mls.network.mlscp.layers;

import com.github.xushifu.mls.network.mlscp.Handler;
import com.github.xushifu.mls.network.mlscp.Layer;
import com.github.xushifu.mls.network.mlscp.RxFilterChain;
import com.github.xushifu.mls.network.mlscp.TxFilterChain;
import com.github.xushifu.mls.network.mlscp.TransactionContext;

public class HandlerLayer implements Layer {

    public HandlerLayer() {
    }

    @Override
    public void receive(TransactionContext ctx, RxFilterChain next) throws Exception {
        Handler h = ctx.getHandler();
        if (h != null) {
            h.handle(ctx);
        }
        next.receive(ctx);
    }

    @Override
    public void send(TransactionContext ctx, TxFilterChain next) throws Exception {
        next.send(ctx);
    }

}
