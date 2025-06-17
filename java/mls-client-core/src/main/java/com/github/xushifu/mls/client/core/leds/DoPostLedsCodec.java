package com.github.xushifu.mls.client.core.leds;

import com.github.xushifu.mls.network.mlscp.Request;
import com.github.xushifu.mls.network.mlscp.Response;
import com.github.xushifu.mls.network.mlscp.UserAgent;

public final class DoPostLedsCodec {

    public DoPostLedsCodec() {
    }

    public static class Params {
        public UserAgent agent;
    }

    public static class Result {
    }

    public Request encodeRequest(Params params) {

        return null;
    }

    public Result decodeResponse(Response resp) {
        return null;
    }

}
