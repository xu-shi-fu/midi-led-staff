package com.github.xushifu.mls.client.core.internal;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.github.xushifu.mls.client.MLSClientContext;
import com.github.xushifu.mls.client.ResponseWaiter;
import com.github.xushifu.mls.client.core.leds.DoGetLedsCodec;
import com.github.xushifu.mls.client.core.leds.DoPostLedsCodec;
import com.github.xushifu.mls.client.core.leds.LEDService;
import com.github.xushifu.mls.client.core.leds.LEDState;
import com.github.xushifu.mls.client.core.leds.LEDStateBuffer;
import com.github.xushifu.mls.network.mlscp.ARGB;
import com.github.xushifu.mls.network.mlscp.Request;
import com.github.xushifu.mls.network.mlscp.Response;
import com.github.xushifu.mls.network.mlscp.TransactionContext;
import com.github.xushifu.mls.network.mlscp.UserAgent;

public final class LEDServiceImpl implements LEDService {

    private final static Logger logger = LoggerFactory.getLogger(LEDServiceImpl.class);

    private final MLSClientContext context;
    private final LEDStateBuffer buffer;

    public LEDServiceImpl(MLSClientContext ctx) {
        this.context = ctx;
        this.buffer = new LEDStateBuffer();
    }

    @Override
    public LEDStateBuffer getStateBuffer() {
        return this.buffer;
    }

    @Override
    public void fetch(FetchOptions options) {

        if (options == null) {
            options = new FetchOptions();
        }

        final ResponseWaiter waiter = new ResponseWaiter(options);
        final DoGetLedsCodec codec = new DoGetLedsCodec();
        final DoGetLedsCodec.Params params = new DoGetLedsCodec.Params();
        final UserAgent agent = context.getUseragent();

        params.agent = agent;
        params.partPosition = options.partPosition;
        params.partSize = options.partSize;
        Request req = codec.encodeRequest(params);
        TransactionContext tc = req.getContext();

        waiter.setupHandler(tc, (tc2) -> {
            Response resp = tc2.getResponse();
            DoGetLedsCodec.Result res = codec.decodeResponse(resp);
            logger.debug("result = " + res);
            this.handleFetchResult(res);
        });

        try {
            agent.getDispatcher().dispatch(tc);
            waiter.tryWait();
        } catch (Exception e) {
            // throw new RuntimeException(e);
            waiter.handleError(e);
        }
    }

    private void handleFetchResult(DoGetLedsCodec.Result res) {
        final ARGB[] src = res.items;
        final LEDState[] dst = this.getStateBuffer().getDiodes();
        final int count = Math.min(src.length, dst.length);
        for (int i = 0; i < count; i++) {
            ARGB item1 = src[i];
            LEDState item2 = dst[i];
            if (item1 == null || item2 == null) {
                continue;
            }
            item2.setRx(item1);
        }
    }

    private void preparePushRequest(PushOptions src, DoPostLedsCodec.Params dst) {

        final LEDState[] arr2 = this.getStateBuffer().getDiodes();
        final boolean[] arr1 = src.leds;
        final ARGB[] arr3 = dst.items;

        // check length of arrays
        final int want_length = 128;
        final int[] lengths = { arr1.length, arr2.length, arr3.length };
        for (int len : lengths) {
            if (len != want_length) {
                throw new RuntimeException("bad array length, want:" + want_length);
            }
        }

        for (int i = 0; i < want_length; i++) {
            if (arr1[i]) {
                LEDState item = arr2[i];
                arr3[i] = item.getTx();
            }
        }

        dst.viewPosition = src.viewPosition;
        dst.viewSize = src.viewSize;
    }

    @Override
    public void push(PushOptions options) {

        if (options == null) {
            options = new PushOptions();
        }

        final ResponseWaiter waiter = new ResponseWaiter(options);
        final DoPostLedsCodec codec = new DoPostLedsCodec();
        final DoPostLedsCodec.Params params = new DoPostLedsCodec.Params();
        final UserAgent agent = context.getUseragent();

        params.agent = agent;
        this.preparePushRequest(options, params);
        Request req = codec.encodeRequest(params);
        TransactionContext tc = req.getContext();

        waiter.setupHandler(tc, (tc2) -> {
            Response resp = tc2.getResponse();
            DoPostLedsCodec.Result res = codec.decodeResponse(resp);
            logger.debug("result = " + res);
        });

        try {
            agent.getDispatcher().dispatch(tc);
            waiter.tryWait();
        } catch (Exception e) {
            // throw new RuntimeException(e);
            waiter.handleError(e);
        }
    }
}
