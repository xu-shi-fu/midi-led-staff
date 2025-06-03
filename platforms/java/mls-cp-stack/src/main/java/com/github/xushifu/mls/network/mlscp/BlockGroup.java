package com.github.xushifu.mls.network.mlscp;

public final class BlockGroup implements IntegerValue {

    public final static BlockGroup COMMON = create(0);
    public final static BlockGroup SYSTEM = create(1);
    public final static BlockGroup MIDI = create(2);
    public final static BlockGroup LED = create(3);
    public final static BlockGroup EXAMPLE = create(4);
    public final static BlockGroup TEST = create(5);

    private final int value;

    private BlockGroup(int n) {
        this.value = n;
    }

    public static BlockGroup create(int n) {
        return new BlockGroup(n);
    }

    public static BlockGroup get(int n) {
        return new BlockGroup(n);
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
        BlockGroup other = (BlockGroup) obj;
        if (value != other.value)
            return false;
        return true;
    }

    @Override
    public String toString() {
        return this.value + "";
    }

    @Override
    public int toInt() {
        return this.value;
    }

}
