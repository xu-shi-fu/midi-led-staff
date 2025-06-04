package com.github.xushifu.mls.network.mlscp;

public final class BlockType implements IntegerValue {

    public final static BlockType NONE = create(0);
    public final static BlockType ARGB = create(0x41);
    public final static BlockType ARGB_ARRAY = create(0x42);

    public final static BlockType UINT8 = create(0x01);
    public final static BlockType UINT16 = create(0x02);
    public final static BlockType UINT32 = create(0x03);
    public final static BlockType UINT64 = create(0x04);

    public final static BlockType INT8 = create(0x11);
    public final static BlockType INT16 = create(0x12);
    public final static BlockType INT32 = create(0x13);
    public final static BlockType INT64 = create(0x14);

    public final static BlockType FLOAT32 = create(0x21);
    public final static BlockType FLOAT64 = create(0x22);

    public final static BlockType BYTE = create(0x01);
    public final static BlockType BYTES = create(0x33);
    public final static BlockType STRING = create(0x32);
    public final static BlockType BOOL = create(0x31);

    private BlockType(int n) {
        this.value = n;
    }

    private final int value;

    public static BlockType create(int n) {
        return new BlockType(n);
    }

    public static BlockType get(int n) {
        return new BlockType(n);
    }

    public String toString() {
        return this.value + "";
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + value;
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (obj == null)
            return false;
        if (getClass() != obj.getClass())
            return false;
        BlockType other = (BlockType) obj;
        return (value == other.value);
    }

    @Override
    public int toInt() {
        return this.value;
    }

}
