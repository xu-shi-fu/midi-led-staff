package com.github.xushifu.mls.network.mlscp;

public interface TxFilter {

    void send(TransactionContext ctx, TxFilterChain next) throws Exception;

}
