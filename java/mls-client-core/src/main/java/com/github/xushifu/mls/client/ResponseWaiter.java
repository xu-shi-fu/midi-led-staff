package com.github.xushifu.mls.client;

import java.util.ArrayList;
import java.util.List;

import com.github.xushifu.mls.network.mlscp.Handler;
import com.github.xushifu.mls.network.mlscp.Response;
import com.github.xushifu.mls.network.mlscp.TransactionContext;
import com.github.xushifu.mls.utils.ErrorUtils;
import com.github.xushifu.mls.utils.TimeUtils;

public final class ResponseWaiter {

    private final List<Handler> handlers;
    private final RequestOptions options;

    private Response response;

    public ResponseWaiter(RequestOptions opt) {
        if (opt == null) {
            opt = new RequestOptions();
        }
        this.handlers = new ArrayList<>();
        this.options = opt;
    }

    public void tryWait() {
        this.doWait();
    }

    private void doWait() {

        long now = System.currentTimeMillis();
        int timeout = this.options.getTimeout();

        if (timeout < 1) {
            timeout = 10 * 1000;
        }

        final int step = 200;
        final long deadline = now + timeout;

        for (;;) {
            now = System.currentTimeMillis();
            if ((deadline < now) || (timeout < 0)) {
                throw new RuntimeException("timeout");
            }
            if (this.response != null) {
                break;
            }
            timeout -= step;
            TimeUtils.sleep(step);
        }
    }

    public void setupHandler(TransactionContext tc, Handler h) {
        addHandler(h);
        addHandler(options.getResponseHandler());
        tc.setHandler(new MainHandler());
    }

    private void addHandler(Handler h) {
        if (h == null) {
            return;
        }
        this.handlers.add(h);
    }

    private class MainHandler implements Handler {

        @Override
        public void handle(TransactionContext ctx) throws Exception {
            List<Handler> list = ResponseWaiter.this.handlers;
            for (Handler h : list) {
                this.invokeHandler(ctx, h);
            }
            ResponseWaiter.this.response = ctx.getResponse();
        }

        private void invokeHandler(TransactionContext ctx, Handler h) {
            if (h == null) {
                return;
            }
            try {
                h.handle(ctx);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    private static class DefaultErrorHandler implements ErrorHandler {
        @Override
        public void onError(Throwable err) throws Throwable {
            if (err == null) {
                return;
            }
            throw ErrorUtils.wrapWithRuntimeException(err);
        }
    };

    public void handleError(Throwable err) {
        ErrorHandler eh = null;
        if (options != null) {
            eh = options.getErrorHandler();
        }
        if (eh == null) {
            eh = new DefaultErrorHandler();
        }
        try {
            eh.onError(err);
        } catch (Throwable e) {
            throw ErrorUtils.wrapWithRuntimeException(e);
        }
    }
}
