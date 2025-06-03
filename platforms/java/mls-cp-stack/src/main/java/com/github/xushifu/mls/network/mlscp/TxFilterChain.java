package com.github.xushifu.mls.network.mlscp;

public interface TxFilterChain {

    void send(TransactionContext ctx) throws Exception;

}
