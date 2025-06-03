package com.github.xushifu.mls.network.mlscp.layers;

import com.github.xushifu.mls.network.mlscp.Layer;
import com.github.xushifu.mls.network.mlscp.RxFilterChain;
import com.github.xushifu.mls.network.mlscp.TxFilterChain;
import com.github.xushifu.mls.network.mlscp.TransactionContext;

public class TransactionLayer implements Layer {

    public TransactionLayer() {
    }

    @Override
    public void receive(TransactionContext ctx, RxFilterChain next) throws Exception {

        // TODO Auto-generated method stub
        next.receive(ctx);
    }

    @Override
    public void send(TransactionContext ctx, TxFilterChain next) throws Exception {
        // TODO Auto-generated method stub
        next.send(ctx);
    }

}
