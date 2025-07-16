package com.github.xushifu.mls.musical;

public class KeyboardEvent {

    private KeyboardAdapter adapter;
    private EventType type;
    private Object source;
    private Key key;

    public KeyboardEvent() {
    }

    public enum EventType {

        NOTE_ON,
        NOTE_OFF,

        STATE_CHANGE,

        LED_STATE_CHANGE,
        LED_PRESSED,
        LED_RELEASED,

        AVAILABLE_RANGE_CHANGE,
        ENABLED_RANGE_CHANGE,
        VIEWPORT_RANGE_CHANGE,
    }

    public KeyboardAdapter getAdapter() {
        return adapter;
    }

    public void setAdapter(KeyboardAdapter adapter) {
        this.adapter = adapter;
    }

    public EventType getType() {
        return type;
    }

    public void setType(EventType type) {
        this.type = type;
    }

    public Object getSource() {
        return source;
    }

    public void setSource(Object source) {
        this.source = source;
    }

    public Key getKey() {
        return key;
    }

    public void setKey(Key key) {
        this.key = key;
    }

}
