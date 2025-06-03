package com.github.xushifu.mls.network.mlscp;

public final class SumChecker {

    private SumChecker() {
    }

    private static byte compute(ByteArraySlice data) {
        if (data == null) {
            return -1;
        }
        final byte[] buf = data.getBuffer();
        final int off = data.getOffset();
        final int len = data.getLength();
        final int end = off + len;
        int n = 0;
        for (int i = off; i < end; ++i) {
            n = n ^ buf[i];
        }
        return (byte) n;
    }

    private static boolean hasEOP(ByteArraySlice data) {

        // |size|type|group|field|value|
        // |5 | i8_u8 |0 |0 |n |

        if (data == null) {
            return false;
        }

        final int eop_size = 5;
        final int off = data.getOffset();
        final int len = data.getLength();
        final int end = off + len;
        final byte[] buf = data.getBuffer();

        if ((0 <= off) && (eop_size <= len) && (end <= buf.length)) {
            final int bt_u8 = BlockType.UINT8.toInt();
            final int bt_i8 = BlockType.INT8.toInt();
            final int p0 = end - eop_size;
            byte b_size = buf[p0];
            byte b_type = buf[p0 + 1];
            byte b_group = buf[p0 + 2];
            byte b_field = buf[p0 + 3];
            return ((b_size == eop_size) && (b_type == bt_i8 || b_type == bt_u8) && (b_group == 0) && (b_field == 0));
        }
        return false;
    }

    public static void make(ByteArraySlice data) {
        if (hasEOP(data)) {
            byte sum = compute(data);
            int off = data.getOffset();
            int len = data.getLength();
            byte[] buf = data.getBuffer();
            buf[off + len - 1] = sum;
            byte sum2 = compute(data);
            if (sum2 != 0) {
                throw new RuntimeException("SumChecker.make(): bad sum2");
            }
        }
    }

    public static void verify(ByteArraySlice data) {
        if (hasEOP(data)) {
            byte sum = compute(data);
            if (sum == 0) {
                return; // OK
            }
        }
        throw new RuntimeException("SumChecker.verify(): bad sum");
    }

}
