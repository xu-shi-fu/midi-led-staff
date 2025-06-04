package com.github.xushifu.mls.network.mlscp;

public final class BlockField implements IntegerValue {

    public final static BlockField COMMON_EOP = createCommon(0);
    public final static BlockField COMMON_METHOD = createCommon(1);
    public final static BlockField COMMON_LOCATION = createCommon(2);
    public final static BlockField COMMON_VERSION = createCommon(3);
    public final static BlockField COMMON_STATUS_CODE = createCommon(4);
    public final static BlockField COMMON_STATUS_MESSAGE = createCommon(5);
    public final static BlockField COMMON_TRANSACTION_ID = createCommon(6);
    public final static BlockField COMMON_reserved = createCommon(7);
    public final static BlockField COMMON_TIMESTAMP = createCommon(8);

    public final static BlockField FOO2 = createSystem(0);

    public final static BlockField FOO3 = createLED(0);

    public final static BlockField FOO4 = createMIDI(0);

    private BlockField(BlockGroup g, int n) {
        this.group = g;
        this.value = n;
    }

    private final BlockGroup group;
    private final int value;

    @Override
    public String toString() {
        return this.group + ":" + this.value;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + ((group == null) ? 0 : group.hashCode());
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
        BlockField other = (BlockField) obj;
        if (group == null) {
            if (other.group != null)
                return false;
        } else if (!group.equals(other.group))
            return false;
        if (value != other.value)
            return false;
        return true;
    }

    public static BlockField create(BlockGroup g, int n) {
        return new BlockField(g, n);
    }

    public static BlockField get(BlockGroup g, int n) {
        return new BlockField(g, n);
    }

    private static BlockField createCommon(int n) {
        BlockGroup g = BlockGroup.COMMON;
        return new BlockField(g, n);
    }

    private static BlockField createSystem(int n) {
        BlockGroup g = BlockGroup.SYSTEM;
        return new BlockField(g, n);
    }

    private static BlockField createMIDI(int n) {
        BlockGroup g = BlockGroup.MIDI;
        return new BlockField(g, n);
    }

    private static BlockField createLED(int n) {
        BlockGroup g = BlockGroup.LED;
        return new BlockField(g, n);
    }

    @Override
    public int toInt() {
        return this.value;
    }

}
