package com.github.xushifu.mls.network.mlscp;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public final class BlockType implements IntegerValue {

    public final static BlockType NONE = create(0, "none");
    public final static BlockType ARGB = create(0x41, "argb");
    public final static BlockType ARGB_ARRAY = create(0x42, "argb[]");

    public final static BlockType UINT8 = create(0x01, "uint8");
    public final static BlockType UINT16 = create(0x02, "uint16");
    public final static BlockType UINT32 = create(0x03, "uint32");
    public final static BlockType UINT64 = create(0x04, "uint64");

    public final static BlockType INT8 = create(0x11, "int8");
    public final static BlockType INT16 = create(0x12, "int16");
    public final static BlockType INT32 = create(0x13, "int32");
    public final static BlockType INT64 = create(0x14, "int64");

    public final static BlockType FLOAT32 = create(0x21, "f32");
    public final static BlockType FLOAT64 = create(0x22, "f64");

    public final static BlockType BYTE = create(0x01, "byte");
    public final static BlockType BYTES = create(0x33, "byte[]");
    public final static BlockType STRING = create(0x32, "string");
    public final static BlockType BOOL = create(0x31, "bool");

    private static void list_all(List<BlockType> list) {
        list.add(NONE);
        list.add(ARGB);
        list.add(ARGB_ARRAY);

        list.add(INT8);
        list.add(INT16);
        list.add(INT32);
        list.add(INT64);

        list.add(UINT8);
        list.add(UINT16);
        list.add(UINT32);
        list.add(UINT64);

        list.add(FLOAT32);
        list.add(FLOAT64);

        list.add(BYTE);
        list.add(BYTES);
        list.add(STRING);
        list.add(BOOL);
    }

    private BlockType(int n, String t) {
        this.value = n;
        this.text = t;
    }

    private final int value;
    private final String text;

    private final static Table table = new Table();

    private static BlockType create(int n, String t) {
        return new BlockType(n, t);
    }

    public static BlockType get(int n) {
        BlockType bt = table.find(n);
        if (bt == null) {
            bt = create(n, "undefined");
        }
        return bt;
    }

    private final static class Table {

        final Map<Integer, BlockType> map;

        Table() {
            this.map = new HashMap<>();
        }

        synchronized BlockType find(int n) {
            Map<Integer, BlockType> all = get_all();
            return all.get(n);
        }

        void load_all(Map<Integer, BlockType> dst) {
            List<BlockType> src = new ArrayList<>();
            list_all(src);
            for (BlockType bt : src) {
                dst.put(bt.value, bt);
            }
        }

        Map<Integer, BlockType> get_all() {
            Map<Integer, BlockType> all = this.map;
            if (all.isEmpty()) {
                load_all(all);
            }
            return all;
        }
    }

    public String toString() {
        return this.text + "(" + this.value + ")";
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
