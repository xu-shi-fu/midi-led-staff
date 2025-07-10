package com.github.xushifu.mls.musical;

import java.util.ArrayList;
import java.util.List;

public class DefaultKeyboardAdapter implements KeyboardAdapter {

    private final MyItem[] items;
    private final List<KeyboardAdapter.Listener> listeners;

    private KeyboardRange viewport;
    private KeyboardRange available;
    private int revision;
    private int revision_sync; // 跟随 revision 的值

    public DefaultKeyboardAdapter() {
        final int count = 128;
        this.items = initItems(count);
        this.listeners = new ArrayList<>();
        this.available = new KeyboardRange(0, count);
        this.viewport = new KeyboardRange(0, 12 * 5);
    }

    private class MyItem {

        final int index;
        final KeyState state;
        final Key key;
        KeyHolder holder;
        int revision; // state.revision = this.revision;

        MyItem(int i, Key k) {
            this.state = new KeyState();
            this.index = i;
            this.key = k;
        }

        void onCreate() {
            this.holder = new MyKeyHolder(this);
            this.state.setAvailable(true);
        }

        void update() {
            DefaultKeyboardAdapter.this.revision++;
            this.revision++;
            this.state.setRevision(this.revision);
        }
    }

    private class Updating {

        boolean force;
        boolean inc_rev;
    }

    private class MyKeyHolder implements KeyHolder {

        final MyItem item;

        MyKeyHolder(MyItem it) {
            this.item = it;
        }

        @Override
        public int getIndex() {
            return this.item.index;
        }

        @Override
        public int getRevision() {
            return this.item.revision;
        }

        @Override
        public Key getKey() {
            return this.item.key;
        }

        @Override
        public KeyState getState() {
            return this.item.state;
        }

        @Override
        public void setState(KeyState state) {
            this.item.state.set(state);
            this.item.update();
        }
    }

    private MyItem[] initItems(int count) {
        MyItem[] array = new MyItem[count];
        for (int i = 0; i < count; i++) {
            Key k = Key.getKeyAt(i);
            MyItem item = new MyItem(i, k);
            item.onCreate();
            array[i] = item;
        }
        return array;
    }

    private static KeyboardRange normalize(KeyboardRange kr) {
        if (kr == null) {
            kr = new KeyboardRange();
        }
        return kr;
    }

    @Override
    public KeyboardRange getViewportRange() {
        return normalize(this.viewport);
    }

    @Override
    public KeyboardRange setViewportRange(KeyboardRange range) {
        range = normalize(range);
        Updating up = new Updating();
        up.inc_rev = true;
        this.viewport = range;
        this.innerUpdate(up);
        return range;
    }

    @Override
    public KeyboardRange getAvailableRange() {
        return normalize(this.available);
    }

    @Override
    public KeyboardRange setAvailableRange(KeyboardRange range) {
        range = normalize(range);
        Updating up = new Updating();
        up.inc_rev = true;
        this.available = range;
        this.innerUpdate(up);
        return range;
    }

    @Override
    public KeyHolder getKeyAt(int index) {
        MyItem[] all = this.items;
        if ((0 <= index) && (index < all.length)) {
            MyItem item = all[index];
            return item.holder;
        }
        return null;
    }

    @Override
    public int getKeyCount() {
        return this.items.length;
    }

    @Override
    public void addListener(Listener l) {
        if (l == null) {
            return;
        }
        if (listeners.contains(l)) {
            return;
        }
        this.listeners.add(l);
    }

    @Override
    public void removeListener(Listener l) {
        this.listeners.remove(l);
    }

    @Override
    public void update(boolean force) {
        Updating up = new Updating();
        if (force) {
            up.force = true;
            up.inc_rev = true;
        }
        this.innerUpdate(up);
    }

    private void innerUpdate(Updating up) {

        if (up == null) {
            return;
        }

        if (up.inc_rev) {
            this.revision++;
        }

        if (!up.force) {
            if (this.revision == this.revision_sync) {
                return;
            }
        }

        this.revision_sync = this.revision;
        this.listeners.forEach((item) -> {
            item.onKeyboardUpdate(DefaultKeyboardAdapter.this);
        });
    }

    @Override
    public int getRevision() {
        return this.revision;
    }

}
