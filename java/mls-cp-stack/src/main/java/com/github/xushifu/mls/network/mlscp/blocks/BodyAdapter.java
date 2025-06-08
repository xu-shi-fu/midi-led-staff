package com.github.xushifu.mls.network.mlscp.blocks;

import com.github.xushifu.mls.network.mlscp.BlockBody;
import com.github.xushifu.mls.network.mlscp.BlockType;

public final class BodyAdapter {

    private BodyAdapter() {
    }

    public static byte getInt8(BlockBody body) {
        if (body instanceof Int8Body) {
            Int8Body b2 = (Int8Body) body;
            return b2.getValue();
        } else if (body instanceof Uint8Body) {
            Uint8Body b2 = (Uint8Body) body;
            return b2.getValue();
        }
        return 0;
    }

    public static short getInt16(BlockBody body) {
        if (body instanceof Int16Body) {
            Int16Body b2 = (Int16Body) body;
            return b2.getValue();
        } else if (body instanceof Uint16Body) {
            Uint16Body b2 = (Uint16Body) body;
            return b2.getValue();
        }
        return 0;
    }

    public static int getInt32(BlockBody body) {
        if (body instanceof Int32Body) {
            Int32Body b2 = (Int32Body) body;
            return b2.getValue();
        } else if (body instanceof Uint32Body) {
            Uint32Body b2 = (Uint32Body) body;
            return b2.getValue();
        }
        return 0;
    }

    public static long getInt64(BlockBody body) {
        if (body instanceof Int64Body) {
            Int64Body b2 = (Int64Body) body;
            return b2.getValue();
        } else if (body instanceof Uint64Body) {
            Uint64Body b2 = (Uint64Body) body;
            return b2.getValue();
        }
        return 0;
    }

    public static byte getByte(BlockBody body) {
        return (byte) getLong(body);
    }

    public static short getShort(BlockBody body) {
        return (short) getLong(body);
    }

    public static int getInt(BlockBody body) {
        return (int) getLong(body);
    }

    public static long getLong(BlockBody body) {
        if (body == null) {
            return 0;
        }
        final BlockType bt = body.type();
        if (BlockType.INT8.equals(bt) || BlockType.UINT8.equals(bt)) {
            return getInt8(body);
        } else if (BlockType.INT16.equals(bt) || BlockType.UINT16.equals(bt)) {
            return getInt16(body);
        } else if (BlockType.INT32.equals(bt) || BlockType.UINT32.equals(bt)) {
            return getInt32(body);
        } else if (BlockType.INT64.equals(bt) || BlockType.UINT64.equals(bt)) {
            return getInt64(body);
        }
        return 0;
    }

    public static String getString(BlockBody body) {
        if (body instanceof StringBody) {
            StringBody b2 = (StringBody) body;
            return b2.getValue();
        }
        return "";
    }

}
