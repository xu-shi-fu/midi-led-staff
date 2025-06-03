package com.github.xushifu.mls.network.mlscp;

import java.util.ArrayList;
import java.util.List;

public final class TxFilterChainBuilder {

    private final List<TxFilter> filters;

    public TxFilterChainBuilder() {
        this.filters = new ArrayList<>();
    }

    public TxFilterChainBuilder add(TxFilter f) {
        if (f != null) {
            this.filters.add(f);
        }
        return this;
    }

    public TxFilterChain create() {
        TxFilterChain chain = new Ending();
        List<TxFilter> list = this.filters;
        for (TxFilter item : list) {
            Node node = new Node();
            node.filter = item;
            node.next = chain;
            chain = node;
        }
        return chain;
    }

    private static class Node implements TxFilterChain {

        private TxFilter filter;
        private TxFilterChain next;

        @Override
        public void send(TransactionContext ctx) throws Exception {
            this.filter.send(ctx, this.next);
        }
    }

    private static class Ending implements TxFilterChain {
        @Override
        public void send(TransactionContext ctx) throws Exception {
            // NOP
        }
    }
}
