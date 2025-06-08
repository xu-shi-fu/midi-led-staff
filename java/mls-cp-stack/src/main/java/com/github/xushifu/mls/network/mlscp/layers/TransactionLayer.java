package com.github.xushifu.mls.network.mlscp.layers;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

import com.github.xushifu.mls.network.mlscp.Layer;
import com.github.xushifu.mls.network.mlscp.Request;
import com.github.xushifu.mls.network.mlscp.Response;
import com.github.xushifu.mls.network.mlscp.ResponseResolver;
import com.github.xushifu.mls.network.mlscp.RxFilterChain;
import com.github.xushifu.mls.network.mlscp.TxFilterChain;
import com.github.xushifu.mls.network.mlscp.TransactionContext;
import com.github.xushifu.mls.network.mlscp.TransactionID;

/**
 * TransactionLayer
 * 这个协议层用于处理事务: 把属于同一事务的请求-响应相关联
 */
public class TransactionLayer implements Layer {

    private final Map<TransactionID, TransactionContext> table;

    public TransactionLayer() {
        Map<TransactionID, TransactionContext> tab = new HashMap<>();
        this.table = Collections.synchronizedMap(tab);
    }

    @Override
    public void send(TransactionContext ctx, TxFilterChain next) throws Exception {

        final TransactionID tid = prepareTransactionID(ctx);
        final Request req = ctx.getRequest();
        final long now = System.currentTimeMillis();

        int timeout = ctx.getTimeout();
        if (timeout < 1) {
            timeout = 1000 * 10; // default = 10 sec
        }

        ctx.setId(tid);
        ctx.setTimeout(timeout);
        req.setTimestamp(now);

        table.put(tid, ctx);
        next.send(ctx);
    }

    @Override
    public void receive(TransactionContext ctx, RxFilterChain next) throws Exception {

        final Response resp1 = ctx.getResponse();
        ResponseResolver.resolve(resp1);

        final TransactionID tid = ctx.getId();
        final TransactionContext origin = table.get(tid);

        if (origin == null) {
            return; // ignore the context
        }
        table.remove(tid);

        final Response resp2 = origin.getResponse();
        copyResponse(resp1, resp2);

        next.receive(origin);
    }

    private static void copyResponse(Response src, Response dst) {
        if (src == null || dst == null) {
            return;
        }
        dst.setBlocks(src.getBlocks());
        dst.setData(src.getData());
        dst.setRemote(src.getRemote());
        dst.setStatus(src.getStatus());
        dst.setTimestamp(src.getTimestamp());
        dst.setVersion(src.getVersion());
    }

    private static boolean isTransactionIDOK(TransactionID tid) {
        if (tid == null) {
            return false;
        }
        int n = tid.toInt();
        return (n != 0);
    }

    private static TransactionID prepareTransactionID(TransactionContext ctx) {
        TransactionID tid = ctx.getId();
        if (!isTransactionIDOK(tid)) {
            tid = TransactionID.next();

        }
        return tid;
    }

    private void trim() {
    }

}
