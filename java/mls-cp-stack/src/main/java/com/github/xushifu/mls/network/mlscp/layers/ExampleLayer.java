package com.github.xushifu.mls.network.mlscp.layers;

import com.github.xushifu.mls.network.mlscp.Layer;
import com.github.xushifu.mls.network.mlscp.RxFilterChain;
import com.github.xushifu.mls.network.mlscp.TxFilterChain;
import com.github.xushifu.mls.network.mlscp.TransactionContext;

public class ExampleLayer implements Layer {

    public ExampleLayer() {
    }

    @Override
    public void receive(TransactionContext ctx, RxFilterChain next) throws Exception {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'receive'");
    }

    @Override
    public void send(TransactionContext ctx, TxFilterChain next) throws Exception {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'send'");
    }

}
