package com.github.xushifu.mls.client.core.leds;

public class LEDStateBuffer {

    private final LEDState[] diodes;

    private int total;
    private int viewPosition;
    private int viewSize;
    private long revision;

    public LEDStateBuffer() {
        final int size = 128;
        this.diodes = new LEDState[size];
        this.total = size;
        for (int i = 0; i < size; i++) {
            this.diodes[i] = new LEDState();
        }
    }

    public LEDState[] getDiodes() {
        return diodes;
    }

    public int getTotal() {
        return total;
    }

    public void setTotal(int total) {
        this.total = total;
    }

    public int getViewPosition() {
        return viewPosition;
    }

    public void setViewPosition(int viewPosition) {
        this.viewPosition = viewPosition;
    }

    public int getViewSize() {
        return viewSize;
    }

    public void setViewSize(int viewSize) {
        this.viewSize = viewSize;
    }

    public long getRevision() {
        return revision;
    }

    public void setRevision(long revision) {
        this.revision = revision;
    }

}
