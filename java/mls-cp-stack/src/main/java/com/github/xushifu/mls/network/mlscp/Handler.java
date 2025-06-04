package com.github.xushifu.mls.network.mlscp;

public interface Handler {

    void handle(TransactionContext ctx) throws Exception;

}
