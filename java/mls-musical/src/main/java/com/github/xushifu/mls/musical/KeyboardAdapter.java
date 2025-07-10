package com.github.xushifu.mls.musical;

public interface KeyboardAdapter {

    public interface Listener {
        void onKeyboardUpdate(KeyboardAdapter adapter);
    }

    void addListener(Listener l);

    void removeListener(Listener l);

    KeyboardRange getViewportRange();

    KeyboardRange setViewportRange(KeyboardRange range);

    KeyboardRange getAvailableRange();

    KeyboardRange setAvailableRange(KeyboardRange range);

    KeyHolder getKeyAt(int index);

    int getKeyCount();

    int getRevision();

    void update(boolean force);

}
