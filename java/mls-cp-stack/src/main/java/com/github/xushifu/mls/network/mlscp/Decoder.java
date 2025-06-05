package com.github.xushifu.mls.network.mlscp;

import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.github.xushifu.mls.network.mlscp.blocks.ArgbArrayBody;
import com.github.xushifu.mls.network.mlscp.blocks.ArgbBody;
import com.github.xushifu.mls.network.mlscp.blocks.BooleanBody;
import com.github.xushifu.mls.network.mlscp.blocks.ByteArrayBody;
import com.github.xushifu.mls.network.mlscp.blocks.ByteBody;
import com.github.xushifu.mls.network.mlscp.blocks.Float32Body;
import com.github.xushifu.mls.network.mlscp.blocks.Float64Body;
import com.github.xushifu.mls.network.mlscp.blocks.Int16Body;
import com.github.xushifu.mls.network.mlscp.blocks.Int32Body;
import com.github.xushifu.mls.network.mlscp.blocks.Int64Body;
import com.github.xushifu.mls.network.mlscp.blocks.Int8Body;
import com.github.xushifu.mls.network.mlscp.blocks.StringBody;
import com.github.xushifu.mls.network.mlscp.blocks.Uint16Body;
import com.github.xushifu.mls.network.mlscp.blocks.Uint32Body;
import com.github.xushifu.mls.network.mlscp.blocks.Uint64Body;
import com.github.xushifu.mls.network.mlscp.blocks.Uint8Body;
import com.github.xushifu.mls.utils.IOUtils;

public final class Decoder {

    public static List<Block> decode(ByteArraySlice src) throws IOException {
        Reader reader = new Reader(src);
        List<Block> dst = new ArrayList<>();
        for (; reader.hasMore();) {
            Block block = reader.readBlock();
            dst.add(block);
        }
        return dst;
    }

    private static class Reader {

        final byte[] buffer;
        final int begin;
        final int end;
        int current;

        private Reader(ByteArraySlice src) {
            final int off = src.getOffset();
            final int len = src.getLength();
            final byte[] buf = src.getBuffer();
            this.begin = off;
            this.end = off + len;
            this.current = off;
            this.buffer = buf;
        }

        boolean hasMore() {
            return (this.begin <= this.current) && (this.current < this.end);
        }

        Block readBlock() throws IOException {

            Block block = new Block();
            BlockHead head = block.getHead();

            // head
            final int nSize = this.readByte();
            final int nType = this.readByte();
            final int nGroup = this.readByte();
            final int nField = this.readByte();

            BlockGroup group = BlockGroup.get(nGroup);

            head.setSize(nSize);
            head.setType(BlockType.get(nType));
            head.setGroup(group);
            head.setField(BlockField.get(nGroup, nField));

            // body
            BlockTypeFactory factory = bt_mapper.findFactory(head);
            BlockBody body = factory.createNewBody(head);
            ByteArraySlice body_data = this.readBlockBodyData(head);
            DataInputStream in = null;
            try {
                in = wrapBodyData(body_data);
                body.decode(in);
                block.setBody(body);
            } finally {
                IOUtils.close(in);
            }
            return block;
        }

        private static DataInputStream wrapBodyData(ByteArraySlice data) {
            byte[] buf = data.getBuffer();
            int off = data.getOffset();
            int len = data.getLength();
            ByteArrayInputStream is = new ByteArrayInputStream(buf, off, len);
            return new DataInputStream(is);
        }

        ByteArraySlice readBlockBodyData(BlockHead head) throws IOException {
            final int block_size = head.getSize();
            final int head_size = 4;
            final int body_size = block_size - head_size;
            return this.readByteArray(body_size);
        }

        ByteArraySlice readByteArray(int size) throws IOException {
            ByteArraySlice slice = new ByteArraySlice();
            final int p0 = this.begin;
            final int p2 = this.end;
            final int p1 = this.current;
            final int p1n = p1 + size;
            final byte[] buf = this.buffer;

            if ((p0 <= p1) && (p1 <= p1n) && (p1n <= p2)) {
                slice.setBuffer(buf);
                slice.setOffset(p1);
                slice.setLength(size);
                this.current = p1n;
            } else {
                throw new IOException("read bytes overflow");
            }

            return slice;
        }

        int readByte() throws IOException {

            final int p0 = this.begin;
            final int p1 = this.current;
            final int p2 = this.end;
            final byte[] buf = this.buffer;

            if (p0 <= p1 && p1 < p2) {
                int b = buf[p1];
                this.current = p1 + 1;
                return b;
            }

            throw new IOException("read byte overflow");
        }
    }

    private interface BlockTypeFactory {
        BlockBody createNewBody(BlockHead head);
    }

    private final static class BlockTypeMapper {

        final Map<BlockType, BlockTypeFactory> table;

        BlockTypeMapper() {
            this.table = new HashMap<>();
        }

        BlockTypeFactory findFactory(BlockHead head) {
            if (table.isEmpty()) {
                this.initTable(table);
            }
            BlockType bt = head.getType();
            BlockTypeFactory factory = table.get(bt);
            if (factory == null) {
                throw new RuntimeException("no block-type of : " + bt);
            }
            return factory;
        }

        private void initTable(Map<BlockType, BlockTypeFactory> tab) {

            ArrayBodyFactory abf = new ArrayBodyFactory();

            tab.put(BlockType.INT8, (BlockHead head) -> new Int8Body());
            tab.put(BlockType.INT16, (BlockHead head) -> new Int16Body());
            tab.put(BlockType.INT32, (BlockHead head) -> new Int32Body());
            tab.put(BlockType.INT64, (BlockHead head) -> new Int64Body());

            tab.put(BlockType.UINT8, (BlockHead head) -> new Uint8Body());
            tab.put(BlockType.UINT16, (BlockHead head) -> new Uint16Body());
            tab.put(BlockType.UINT32, (BlockHead head) -> new Uint32Body());
            tab.put(BlockType.UINT64, (BlockHead head) -> new Uint64Body());

            tab.put(BlockType.FLOAT32, (BlockHead head) -> new Float32Body());
            tab.put(BlockType.FLOAT64, (BlockHead head) -> new Float64Body());

            tab.put(BlockType.BOOL, (BlockHead head) -> new BooleanBody());
            tab.put(BlockType.BYTE, (BlockHead head) -> new ByteBody());
            tab.put(BlockType.BYTES, (BlockHead head) -> abf.createByteArrayBody(head));
            tab.put(BlockType.STRING, (BlockHead head) -> abf.createStringBody(head));

            tab.put(BlockType.ARGB, (BlockHead head) -> new ArgbBody());
            tab.put(BlockType.ARGB_ARRAY, (BlockHead head) -> abf.createArgbArrayBody(head));

        }

    }

    private static class ArrayBodyFactory {

        static int computeBodySize(BlockHead head) {
            final int full_size = head.getSize();
            final int head_size = 4;
            return full_size - head_size;
        }

        BlockBody createStringBody(BlockHead head) {
            StringBody body = new StringBody();
            body.setLength(computeBodySize(head));
            return body;
        }

        BlockBody createByteArrayBody(BlockHead head) {
            ByteArrayBody body = new ByteArrayBody();
            body.setLength(computeBodySize(head));
            return body;
        }

        BlockBody createArgbArrayBody(BlockHead head) {
            ArgbArrayBody body = new ArgbArrayBody();
            body.setLength(computeBodySize(head));
            return body;
        }

    }

    private final static BlockTypeMapper bt_mapper = new BlockTypeMapper();
}
