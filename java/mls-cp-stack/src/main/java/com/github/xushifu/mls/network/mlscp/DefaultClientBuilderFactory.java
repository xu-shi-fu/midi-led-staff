package com.github.xushifu.mls.network.mlscp;

import java.io.IOException;
import java.net.SocketAddress;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import com.github.xushifu.mls.network.mlscp.layers.CodecLayer;
import com.github.xushifu.mls.network.mlscp.layers.DatagramLayer;
import com.github.xushifu.mls.network.mlscp.layers.MessageLayer;
import com.github.xushifu.mls.network.mlscp.layers.MonitorLayer;
import com.github.xushifu.mls.network.mlscp.layers.TransactionLayer;

public class DefaultClientBuilderFactory implements ClientBuilderFactory {

    DefaultClientBuilderFactory() {
    }

    @Override
    public ClientBuilder createBuilder() {
        MyBuilder builder = new MyBuilder();

        builder.addLayer(new MonitorLayer());
        builder.addLayer(new MessageLayer());
        builder.addLayer(new TransactionLayer());
        builder.addLayer(new CodecLayer());
        builder.addLayer(new DatagramLayer());

        return builder;
    }

    private static class MyDispatcher implements Dispatcher {

        private final Stack stack;

        public MyDispatcher(Stack s) {
            this.stack = s;
        }

        @Override
        public void dispatch(TransactionContext ctx) throws Exception {
            this.stack.tx.send(ctx);
        }
    }

    private static class MyBuilder extends ClientBuilder {

        @Override
        public Client open() throws IOException {

            Stack stack = new Stack();
            MyClient client = new MyClient(stack);
            List<Layer> layers = this.getLayers(true);

            stack.rx = this.createRxFilterChain(layers);
            stack.tx = this.createTxFilterChain(layers);
            stack.dispatcher = new MyDispatcher(stack);
            stack.layers = layers;
            stack.client = client;
            stack.local = this.getLocal();
            stack.remote = this.getRemote();
            stack.timeout = this.getTimeout();

            client.open();
            return client;
        }

        private static List<Layer> reverse(List<Layer> layers) {
            List<Layer> list2 = new ArrayList<>(layers);
            Collections.reverse(list2);
            return list2;
        }

        private RxFilterChain createRxFilterChain(List<Layer> layers) {
            // layers = reverse(layers);
            RxFilterChainBuilder builder = new RxFilterChainBuilder();
            for (Layer l : layers) {
                builder.add(l);
            }
            return builder.create();
        }

        private TxFilterChain createTxFilterChain(List<Layer> layers) {
            layers = reverse(layers);
            TxFilterChainBuilder builder = new TxFilterChainBuilder();
            for (Layer l : layers) {
                builder.add(l);
            }
            return builder.create();
        }
    }

    private static class MyClient implements Client {

        private final Stack stack;

        public MyClient(Stack s) {
            this.stack = s;
        }

        void open() {
            StackRuntime rt = new StackRuntime(this.stack);
            stack.runtime = rt;
            rt.start();
            rt.waitUntilStarted(this.stack.timeout);
        }

        @Override
        public void close() throws IOException {
            StackRuntime rt = this.stack.runtime;
            if (rt == null) {
                return;
            }
            rt.stop();
        }

        @Override
        public Dispatcher getDispatcher() {
            return this.stack.dispatcher;
        }

        @Override
        public void join() throws InterruptedException {
            StackRuntime rt = this.stack.runtime;
            if (rt == null) {
                return;
            }
            rt.join();
        }

        @Override
        public Request createNewRequest() {

            TransactionContext tc = new TransactionContext();

            Request req = new Request(tc);
            Response resp = new Response(tc);

            tc.setRequest(req);
            tc.setResponse(resp);
            tc.setTimeout(10 * 1000);
            tc.setStack(this.stack);
            tc.setId(TransactionID.next());
            tc.setHandler(null);

            return req;
        }

        @Override
        public SocketAddress getLocal() {
            return this.stack.local;
        }

        @Override
        public SocketAddress getRemote() {
            return this.stack.remote;
        }
    }
}
