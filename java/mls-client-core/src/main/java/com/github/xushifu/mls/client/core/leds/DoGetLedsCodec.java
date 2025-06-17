package com.github.xushifu.mls.client.core.leds;

import java.util.List;

import com.github.xushifu.mls.network.mlscp.ARGB;
import com.github.xushifu.mls.network.mlscp.Block;
import com.github.xushifu.mls.network.mlscp.BlockField;
import com.github.xushifu.mls.network.mlscp.BlockTypeAdapter;
import com.github.xushifu.mls.network.mlscp.Location;
import com.github.xushifu.mls.network.mlscp.Method;
import com.github.xushifu.mls.network.mlscp.Request;
import com.github.xushifu.mls.network.mlscp.RequestBuilder;
import com.github.xushifu.mls.network.mlscp.Response;
import com.github.xushifu.mls.network.mlscp.UserAgent;

public final class DoGetLedsCodec {

    public DoGetLedsCodec() {
    }

    public static class Params {
        public UserAgent agent;
        public int partSize;
        public int partPosition;
        public int viewSize;
        public int viewPosition;
    }

    public static class Result {

        public Integer viewSize;
        public Integer viewPosition;

        public final ARGB[] items; // 如果没有更新数据, 对应的项为 null

        public Result() {
            this.items = new ARGB[128];
        }
    }

    public Request encodeRequest(Params params) {

        // TransactionContext ctx = req.getContext();
        UserAgent agent = params.agent;
        RequestBuilder rb = new RequestBuilder(agent);

        rb.setMethod(Method.GET).setLocation(Location.LEDS);
        rb.addUint8(BlockField.LED_VIEW_POSITION, params.viewPosition);
        rb.addUint8(BlockField.LED_VIEW_SIZE, params.viewSize);
        rb.addNoValue(BlockField.COMMON_FLUSH);

        rb.addUint8(BlockField.LED_PART_POSITION, params.partPosition);
        rb.addUint8(BlockField.LED_PART_SIZE, params.partSize);
        rb.addArgbArray(BlockField.LED_PART_ITEMS, new ARGB[0]);
        rb.addNoValue(BlockField.COMMON_FLUSH);

        return rb.create();
    }

    public Result decodeResponse(Response resp) {
        ResponseScanner scanner = new ResponseScanner();
        scanner.scan(resp);
        return scanner.result();
    }

    private final static class ResponseScanner {

        private Block b_view_pos;
        private Block b_view_size;
        private Block b_part_items;
        private Block b_part_pos;
        private Block b_part_size;

        private Result res;

        void scan(Response resp) {
            this.res = new Result();
            List<Block> items = resp.getBlocks();
            for (Block item : items) {
                this.onBlock(item);
            }
        }

        private void flush() {

            if ((b_part_items != null) && (b_part_pos != null) && (b_part_size != null)) {
                final int part_pos = BlockTypeAdapter.getInt(b_part_pos.getBody());
                final int part_size = BlockTypeAdapter.getInt(b_part_size.getBody());
                final ARGB[] part_items = BlockTypeAdapter.getArgbArray(b_part_items.getBody());
                this.onPartItems(part_items, part_pos, part_size);
            }

            if (b_view_pos != null) {
                int view_pos = BlockTypeAdapter.getInt(b_view_pos.getBody());
                this.onViewPosition(view_pos);
            }

            if (b_view_size != null) {
                int view_size = BlockTypeAdapter.getInt(b_view_size.getBody());
                this.onViewSize(view_size);
            }

            this.b_part_items = null;
            this.b_part_pos = null;
            this.b_part_size = null;
            this.b_view_pos = null;
            this.b_view_size = null;
        }

        private void onViewSize(int size) {
            this.res.viewSize = size;
        }

        private void onViewPosition(int pos) {
            this.res.viewPosition = pos;
        }

        private void onPartItems(ARGB[] src, int pos, int count) {
            ARGB[] dst = this.res.items;
            for (int i = 0; i < count; i++) {
                final int i1 = i; // to src
                final int i2 = i + pos; // to dst
                dst[i2] = src[i1];
            }
        }

        private void onBlock(Block item) {

            final BlockField field = item.getHead().getField();

            if (field.equals(BlockField.COMMON_FLUSH)) {
                this.flush();
            } else if (field.equals(BlockField.COMMON_EOG)) {
                this.flush();

            } else if (field.equals(BlockField.LED_VIEW_POSITION)) {
                this.b_view_pos = item;

            } else if (field.equals(BlockField.LED_VIEW_SIZE)) {
                this.b_view_size = item;

            } else if (field.equals(BlockField.LED_PART_ITEMS)) {
                this.b_part_items = item;

            } else if (field.equals(BlockField.LED_PART_POSITION)) {
                this.b_part_pos = item;

            } else if (field.equals(BlockField.LED_PART_SIZE)) {
                this.b_part_size = item;
            }
        }

        Result result() {
            return this.res;
        }
    }
}
