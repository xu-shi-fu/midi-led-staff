package com.github.xushifu.mls.network.mlscp;

public interface RxFilterChain {

    void receive(TransactionContext ctx) throws Exception;
}
