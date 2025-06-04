package com.github.xushifu.mls.network.mlscp;

public interface Dispatcher {

    void dispatch(TransactionContext ctx) throws Exception;

}
