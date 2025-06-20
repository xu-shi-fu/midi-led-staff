package com.github.xushifu.mls.musical;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public final class KeyboardCore implements Keyboard {

    private final Key[] keys;

    private KeyboardCore(Key[] array) {
        this.keys = array;
    }

    @Override
    public Key getKey(int index) {
        return keys[index];
    }

    @Override
    public int getKeyCount() {
        return keys.length;
    }

    public static class Builder {

        final Map<String, Key> table;

        Builder() {
            this.table = new HashMap<>();
        }

        public Builder addKey(Key key) {
            if (key != null) {
                String id = String.valueOf(key);
                table.put(id, key);
            }
            return this;
        }

        public KeyboardCore create() {
            List<Key> list = new ArrayList<>(table.values());
            list.sort((a, b) -> compareKeys(a, b));
            Key[] array = list.toArray(new Key[0]);
            return new KeyboardCore(array);
        }

    }

    private static int compareKeys(Key a, Key b) {
        if (a == null) {
            return -1;
        }
        if (b == null) {
            return 1;
        }
        int diff = a.getIndex() - b.getIndex();
        if (diff == 0) {
            return 0; // 相等
        }
        return (diff < 0) ? -1 : 1;
    }

}
