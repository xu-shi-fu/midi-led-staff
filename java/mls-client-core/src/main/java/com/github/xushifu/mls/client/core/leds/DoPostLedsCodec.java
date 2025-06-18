package com.github.xushifu.mls.client.core.leds;

import java.util.ArrayList;
import java.util.List;

import com.github.xushifu.mls.network.mlscp.ARGB;
import com.github.xushifu.mls.network.mlscp.BlockField;
import com.github.xushifu.mls.network.mlscp.Location;
import com.github.xushifu.mls.network.mlscp.Method;
import com.github.xushifu.mls.network.mlscp.Request;
import com.github.xushifu.mls.network.mlscp.RequestBuilder;
import com.github.xushifu.mls.network.mlscp.Response;
import com.github.xushifu.mls.network.mlscp.UserAgent;

public final class DoPostLedsCodec {

    public DoPostLedsCodec() {
    }

    public static class Params {

        public UserAgent agent;

        /**
         * 如果没有更新数据, 对应的项为 null. range:[0,127]
         */
        public final ARGB[] items;

        public int viewPosition;
        public int viewSize;

        public Params() {
            this.items = new ARGB[128];
        }

    }

    public static class Result {
    }

    private static class Part {

        int pos;
        ARGB[] items;

        public int size() {
            ARGB[] array = this.items;
            if (array == null) {
                return 0;
            }
            return array.length;
        }
    }

    private static class PartArrayBuilder {

        final List<Part> result = new ArrayList<>();
        final List<ARGB> buffer = new ArrayList<>();
        int partSizeLimit;
        int offset;

        PartArrayBuilder() {
            this.partSizeLimit = 32; // 单个 part 最大 32 项
        }

        void add(ARGB item, int index) {
            if (item == null) {
                this.flush();
                return;
            }

            if (buffer.size() >= this.partSizeLimit) {
                this.flush();
            }

            if (buffer.size() == 0) {
                this.offset = index;
            }
            buffer.add(item);
        }

        void flush() {

            if (buffer.isEmpty()) {
                return;
            }

            Part p = new Part();
            p.pos = this.offset;
            p.items = buffer.toArray(new ARGB[0]);

            this.result.add(p);
            this.buffer.clear();
            this.offset = 0;
        }

        Part[] build() {
            this.flush();
            return this.result.toArray(new Part[0]);
        }
    }

    private static Part[] toParts(Params params) {
        PartArrayBuilder builder = new PartArrayBuilder();
        final ARGB[] src = params.items;
        final int count = src.length;
        for (int i = 0; i < count; i++) {
            ARGB item = src[i];
            builder.add(item, i);
        }
        return builder.build();
    }

    public Request encodeRequest(Params params) {

        Part[] parts = toParts(params);
        UserAgent agent = params.agent;
        RequestBuilder rb = new RequestBuilder(agent);

        rb.setMethod(Method.POST).setLocation(Location.LEDS);
        rb.addUint8(BlockField.LED_VIEW_POSITION, params.viewPosition);
        rb.addUint8(BlockField.LED_VIEW_SIZE, params.viewSize);
        rb.addNoValue(BlockField.COMMON_FLUSH);

        for (Part part : parts) {
            rb.addUint8(BlockField.LED_PART_POSITION, part.pos);
            rb.addUint8(BlockField.LED_PART_SIZE, part.size());
            rb.addArgbArray(BlockField.LED_PART_ITEMS, part.items);
            rb.addNoValue(BlockField.COMMON_FLUSH);
        }

        return rb.create();
    }

    public Result decodeResponse(Response resp) {

        // todo ...

        ResponseScanner scanner = new ResponseScanner();
        // scanner.scan(resp);
        return scanner.result();

    }

    private static class ResponseScanner {

        public Result result() {
            return new Result();
        }
    }
}
