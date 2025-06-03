package com.github.xushifu.mls.network.mlscp;

public interface RxFilter {

    void receive(TransactionContext ctx, RxFilterChain next) throws Exception;

}
