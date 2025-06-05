package com.github.xushifu.mls.network.mlscp;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public final class BlockField implements IntegerValue {

    public final static BlockField COMMON_EOP = createCommon(0, "eop");
    public final static BlockField COMMON_EOG = createCommon(9, "eog");
    public final static BlockField COMMON_METHOD = createCommon(1, "method");
    public final static BlockField COMMON_LOCATION = createCommon(2, "location");
    public final static BlockField COMMON_VERSION = createCommon(3, "version");
    public final static BlockField COMMON_STATUS_CODE = createCommon(4, "status_code");
    public final static BlockField COMMON_STATUS_MESSAGE = createCommon(5, "status_message");
    public final static BlockField COMMON_TRANSACTION_ID = createCommon(6, "transaction");
    public final static BlockField COMMON_reserved = createCommon(7, "reserved");
    public final static BlockField COMMON_TIMESTAMP = createCommon(8, "timestamp");

    public final static BlockField FOO2 = createSystem(0, "sys...todo");

    public final static BlockField LED_POSITION = createLED(1, "led_at_pos");
    public final static BlockField LED_COUNT = createLED(2, "led_count");
    public final static BlockField LED_ITEMS = createLED(3, "led_argb_items");

    public final static BlockField FOO4 = createMIDI(0, "midi...todo");

    private static void list_all(List<BlockField> list) {

        list.add(COMMON_EOP);
        list.add(COMMON_EOG);

        list.add(COMMON_METHOD);
        list.add(COMMON_LOCATION);
        list.add(COMMON_VERSION);
        list.add(COMMON_STATUS_CODE);
        list.add(COMMON_STATUS_MESSAGE);
        list.add(COMMON_TRANSACTION_ID);
        list.add(COMMON_reserved);
        list.add(COMMON_TIMESTAMP);

        list.add(FOO2);

        list.add(LED_POSITION);
        list.add(LED_COUNT);
        list.add(LED_ITEMS);

        list.add(FOO4);
    }

    private final int gid;
    private final int fid;
    private final String text;

    private final static Table table = new Table();

    private BlockField(int g, int f, String t) {
        this.gid = g;
        this.fid = f;
        this.text = t;
    }

    private static String keyOf(int gid, int fid) {
        return gid + ":" + fid;
    }

    private static BlockField create(int gid, int fid, String txt) {
        return new BlockField(gid, fid, txt);
    }

    private final static class Table {

        final Map<String, BlockField> map;

        Table() {
            this.map = new HashMap<>();
        }

        private synchronized BlockField find(int gid, int fid) {
            Map<String, BlockField> all = get_all();
            String key = keyOf(gid, fid);
            return all.get(key);
        }

        Map<String, BlockField> get_all() {
            Map<String, BlockField> all = this.map;
            if (all.isEmpty()) {
                load_all(all);
            }
            return all;
        }

        void load_all(Map<String, BlockField> dst) {
            List<BlockField> src = new ArrayList<>();
            list_all(src);
            for (BlockField field : src) {
                String key = keyOf(field.gid, field.fid);
                dst.put(key, field);
            }
        }
    }

    @Override
    public String toString() {
        return this.gid + ":" + this.fid + "(" + this.text + ")";
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + gid;
        result = prime * result + fid;
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
        if (gid != other.gid)
            return false;
        if (fid != other.fid)
            return false;
        return true;
    }

    public static BlockField get(int gid, int fid) {
        BlockField field = table.find(gid, fid);
        if (field == null) {
            field = create(gid, fid, "undefined");
        }
        return field;
    }

    private static BlockField createCommon(int fid, String txt) {
        final int gid = BlockGroup.COMMON.toInt();
        return create(gid, fid, txt);
    }

    private static BlockField createSystem(int fid, String txt) {
        final int gid = BlockGroup.SYSTEM.toInt();
        return create(gid, fid, txt);
    }

    private static BlockField createMIDI(int fid, String txt) {
        final int gid = BlockGroup.MIDI.toInt();
        return create(gid, fid, txt);
    }

    private static BlockField createLED(int fid, String txt) {
        final int gid = BlockGroup.LED.toInt();
        return create(gid, fid, txt);
    }

    public BlockGroup getOwnerGroup() {
        return BlockGroup.get(this.gid);
    }

    @Override
    public int toInt() {
        return this.fid;
    }
}
