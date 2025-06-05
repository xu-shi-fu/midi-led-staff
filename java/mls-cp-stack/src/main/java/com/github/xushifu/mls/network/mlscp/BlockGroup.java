package com.github.xushifu.mls.network.mlscp;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public final class BlockGroup implements IntegerValue {

    public final static BlockGroup COMMON = create(0, "COMMON");
    public final static BlockGroup SYSTEM = create(1, "SYSTEM");
    public final static BlockGroup MIDI = create(2, "MIDI");
    public final static BlockGroup LED = create(3, "LED");
    public final static BlockGroup EXAMPLE = create(4, "EXAMPLE");
    public final static BlockGroup TEST = create(5, "TEST");

    private static void list_all(List<BlockGroup> dst) {

        dst.add(COMMON);
        dst.add(LED);
        dst.add(MIDI);
        dst.add(SYSTEM);

        dst.add(EXAMPLE);
        dst.add(TEST);
    }

    private BlockGroup(int n, String t) {
        this.value = n;
        this.text = t;
    }

    private final int value;
    private final String text;

    private final static Table table = new Table();

    private static BlockGroup create(int value, String text) {
        return new BlockGroup(value, text);
    }

    public static BlockGroup get(int n) {
        BlockGroup group = table.find(n);
        if (group == null) {
            group = create(n, "unknown");
        }
        return group;
    }

    private final static class Table {

        final Map<Integer, BlockGroup> map;

        private Table() {
            this.map = new HashMap<>();
        }

        synchronized BlockGroup find(int n) {
            Map<Integer, BlockGroup> all = get_all();
            return all.get(n);
        }

        Map<Integer, BlockGroup> get_all() {
            Map<Integer, BlockGroup> all = this.map;
            if (all.isEmpty()) {
                load_all(all);
            }
            return all;
        }

        void load_all(Map<Integer, BlockGroup> dst) {
            List<BlockGroup> src = new ArrayList<>();
            list_all(src);
            for (BlockGroup group : src) {
                dst.put(group.value, group);
            }
        }
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
        return this.text + "(" + this.value + ")";
    }

    @Override
    public int toInt() {
        return this.value;
    }
}
