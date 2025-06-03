package com.github.xushifu.mls.network.mlscp;

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
import com.github.xushifu.mls.utils.Strings;

public final class BlockTypeAdapter {

    private BlockTypeAdapter() {
    }

    public static byte getInt8(BlockBody body) {
        if (body instanceof Uint8Body) {
            Uint8Body b2 = (Uint8Body) body;
            return b2.getValue();
        } else if (body instanceof Int8Body) {
            Int8Body b2 = (Int8Body) body;
            return b2.getValue();
        }
        return 0;
    }

    public static short getInt16(BlockBody body) {
        if (body instanceof Uint16Body) {
            Uint16Body b2 = (Uint16Body) body;
            return b2.getValue();
        } else if (body instanceof Int16Body) {
            Int16Body b2 = (Int16Body) body;
            return b2.getValue();
        }
        return 0;
    }

    public static int getInt32(BlockBody body) {
        if (body instanceof Uint32Body) {
            Uint32Body b2 = (Uint32Body) body;
            return b2.getValue();
        } else if (body instanceof Int32Body) {
            Int32Body b2 = (Int32Body) body;
            return b2.getValue();
        }
        return 0;
    }

    public static long getInt64(BlockBody body) {
        if (body instanceof Uint64Body) {
            Uint64Body b2 = (Uint64Body) body;
            return b2.getValue();
        } else if (body instanceof Int64Body) {
            Int64Body b2 = (Int64Body) body;
            return b2.getValue();
        }
        return 0;
    }

    public static String getString(BlockBody body) {
        String str = null;
        if (body instanceof StringBody) {
            StringBody b2 = (StringBody) body;
            str = b2.getValue();
        }
        return Strings.useEmpty(str);
    }

    public static boolean getBoolean(BlockBody body) {
        if (body instanceof BooleanBody) {
            BooleanBody b2 = (BooleanBody) body;
            return b2.isValue();
        }
        return false;
    }

    public static byte getByte(BlockBody body) {
        if (body instanceof ByteBody) {
            ByteBody b2 = (ByteBody) body;
            return b2.getValue();

        } else if (body instanceof Uint8Body) {
            Uint8Body b2 = (Uint8Body) body;
            return b2.getValue();

        } else if (body instanceof Int8Body) {
            Int8Body b2 = (Int8Body) body;
            return b2.getValue();
        }
        return 0;
    }

    public static byte[] getBytes(BlockBody body) {
        if (body instanceof ByteArrayBody) {
            ByteArrayBody b2 = (ByteArrayBody) body;
            return b2.getValue();
        }
        return new byte[0];
    }

    public static float getFloat32(BlockBody body) {
        if (body instanceof Float32Body) {
            Float32Body b2 = (Float32Body) body;
            return b2.getValue();
        }
        return 0;
    }

    public static double getFloat64(BlockBody body) {
        if (body instanceof Float64Body) {
            Float64Body b2 = (Float64Body) body;
            return b2.getValue();
        }
        return 0;
    }

}
