package com.github.xushifu.mls.network.mlscp;

import java.io.ByteArrayOutputStream;
import java.io.Closeable;
import java.io.DataOutputStream;
import java.io.DataOutput;
import java.io.IOException;
import java.util.List;

import com.github.xushifu.mls.utils.IOUtils;

public final class Encoder {

    public static ByteArraySlice encode(List<Block> blocks) throws IOException {
        if (blocks == null) {
            return new ByteArraySlice();
        }
        final Writer w = new Writer();
        try {
            w.open();
            for (Block block : blocks) {
                w.writeBlock(block);
            }
            w.flush();
            return w.result();
        } finally {
            IOUtils.close(w);
        }
    }

    private final static class Writer implements Closeable {

        ByteArrayOutputStream buffer;
        DataOutputStream out;

        Writer() {
        }

        public void writeBlock(Block block) throws IOException {

            BlockHead head = block.getHead();
            BlockBody body = block.getBody();

            final int head_len = 4;
            final int body_len = body.length();
            final int size = head_len + body_len;

            head.setSize(size);
            head.setType(body.type());

            this.writeBlockHead(head);
            body.encode(out);
        }

        static int intValueOf(IntegerValue iv) {
            if (iv == null) {
                return 0;
            }
            return iv.toInt();
        }

        private void writeBlockHead(BlockHead head) throws IOException {
            DataOutput o = this.out;
            int s = head.getSize();
            int t = intValueOf(head.getType());
            int g = intValueOf(head.getGroup());
            int f = intValueOf(head.getField());
            // 注意: 这里的顺序必须是 "s -> t -> g -> f"
            o.writeByte(s);
            o.writeByte(t);
            o.writeByte(g);
            o.writeByte(f);
        }

        public ByteArraySlice result() {
            byte[] array = buffer.toByteArray();
            return new ByteArraySlice(array);
        }

        void open() {
            buffer = new ByteArrayOutputStream();
            out = new DataOutputStream(buffer);
        }

        void flush() throws IOException {
            this.out.flush();
        }

        public void close() {
            IOUtils.close(buffer);
            IOUtils.close(out);
        }
    }
}
