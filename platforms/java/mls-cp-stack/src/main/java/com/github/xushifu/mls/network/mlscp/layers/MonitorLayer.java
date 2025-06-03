package com.github.xushifu.mls.network.mlscp.layers;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.github.xushifu.mls.network.mlscp.ByteArraySlice;
import com.github.xushifu.mls.network.mlscp.Layer;
import com.github.xushifu.mls.network.mlscp.Request;
import com.github.xushifu.mls.network.mlscp.Response;
import com.github.xushifu.mls.network.mlscp.RxFilterChain;
import com.github.xushifu.mls.network.mlscp.TransactionContext;
import com.github.xushifu.mls.network.mlscp.TxFilterChain;

public class MonitorLayer implements Layer {

    private final static Logger logger = LoggerFactory.getLogger(MonitorLayer.class);

    public MonitorLayer() {
    }

    @Override
    public void receive(TransactionContext ctx, RxFilterChain next) throws Exception {

        Response resp = ctx.getResponse();
        log("rx", resp.getData());

        next.receive(ctx);
    }

    @Override
    public void send(TransactionContext ctx, TxFilterChain next) throws Exception {

        next.send(ctx);

        Request req = ctx.getRequest();
        log("tx", req.getData());
    }

    private void log(String tag, ByteArraySlice payload) {

        if (tag == null || payload == null) {
            logger.warn(this + ".log(): tag|payload is nil");
            return;
        }

        final StringBuilder builder = new StringBuilder();
        final byte[] buf = payload.getBuffer();
        final int begin, end, len;
        len = payload.getLength();
        begin = payload.getOffset();
        end = begin + len;

        builder.append(tag).append(':');
        builder.append("[payload");
        builder.append(" size:").append(len);
        builder.append(" data:");

        for (int i = begin; i < end; i++) {
            int b = buf[i] & 0xff;
            builder.append(' ').append(b).append(',');
        }

        builder.append(']');
        logger.info(builder.toString());
    }

}
