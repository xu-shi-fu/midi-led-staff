package com.github.xushifu.mls.network.mlscp.layers;

import java.util.List;

import com.github.xushifu.mls.network.mlscp.Block;
import com.github.xushifu.mls.network.mlscp.ByteArraySlice;
import com.github.xushifu.mls.network.mlscp.Decoder;
import com.github.xushifu.mls.network.mlscp.Encoder;
import com.github.xushifu.mls.network.mlscp.Layer;
import com.github.xushifu.mls.network.mlscp.Request;
import com.github.xushifu.mls.network.mlscp.Response;
import com.github.xushifu.mls.network.mlscp.RxFilterChain;
import com.github.xushifu.mls.network.mlscp.SumChecker;
import com.github.xushifu.mls.network.mlscp.TransactionContext;
import com.github.xushifu.mls.network.mlscp.TxFilterChain;

public class CodecLayer implements Layer {

    public CodecLayer() {
    }

    @Override
    public void receive(TransactionContext ctx, RxFilterChain next) throws Exception {
        Response resp = ctx.getResponse();
        ByteArraySlice payload = resp.getData();
        SumChecker.verify(payload);
        List<Block> blocks = Decoder.decode(payload);
        resp.setBlocks(blocks);
        next.receive(ctx);
    }

    @Override
    public void send(TransactionContext ctx, TxFilterChain next) throws Exception {
        Request req = ctx.getRequest();
        ByteArraySlice payload = Encoder.encode(req.getBlocks());
        SumChecker.make(payload);
        req.setData(payload);
        next.send(ctx);
    }

}
