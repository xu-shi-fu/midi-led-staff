package com.github.xushifu.mls.network.mlscp;

import java.util.ArrayList;
import java.util.List;

public final class RxFilterChainBuilder {

    private final List<RxFilter> filters;

    public RxFilterChainBuilder() {
        this.filters = new ArrayList<>();
    }

    public RxFilterChainBuilder add(RxFilter f) {
        if (f != null) {
            this.filters.add(f);
        }
        return this;
    }

    public RxFilterChain create() {
        RxFilterChain chain = new Ending();
        List<RxFilter> list = this.filters;
        for (RxFilter item : list) {
            Node node = new Node();
            node.filter = item;
            node.next = chain;
            chain = node;
        }
        return chain;
    }

    private static class Node implements RxFilterChain {

        private RxFilter filter;
        private RxFilterChain next;

        @Override
        public void receive(TransactionContext ctx) throws Exception {
            this.filter.receive(ctx, this.next);
        }
    }

    private static class Ending implements RxFilterChain {
        @Override
        public void receive(TransactionContext ctx) throws Exception {
            // NOP
        }
    }
}
