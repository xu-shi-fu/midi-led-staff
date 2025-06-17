package com.github.xushifu.mls.client.core.clients;

import com.github.xushifu.mls.network.mlscp.Location;
import com.github.xushifu.mls.network.mlscp.Method;
import com.github.xushifu.mls.network.mlscp.Request;
import com.github.xushifu.mls.network.mlscp.RequestBuilder;
import com.github.xushifu.mls.network.mlscp.Response;
import com.github.xushifu.mls.network.mlscp.Status;
import com.github.xushifu.mls.network.mlscp.UserAgent;

public final class DoGetPingCodec {

    public static class Params {
        public long timestamp;
        public UserAgent agent;
    }

    public static class Result {
        public long timestamp;
        public int code;
        public String message;
    }

    public DoGetPingCodec() {
    }

    public Request encodeRequest(Params params) {
        long now = System.currentTimeMillis();
        RequestBuilder builder = new RequestBuilder(params.agent);
        builder.setMethod(Method.GET).setLocation(Location.PING);
        Request req = builder.create();
        req.setTimestamp(now);
        params.timestamp = now;
        return req;
    }

    public Result decodeResponse(Response resp) {
        Status status = resp.getStatus();
        Result res = new Result();

        if (status != null) {
            res.code = status.getCode();
            res.message = status.getMessage();
            res.timestamp = resp.getTimestamp();
        }

        return res;
    }

}
