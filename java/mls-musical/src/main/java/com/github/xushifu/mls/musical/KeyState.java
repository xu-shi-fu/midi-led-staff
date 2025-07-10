package com.github.xushifu.mls.musical;

/***
 * 表示琴键的状态
 */
public class KeyState {

    private boolean pressed;
    private boolean available;
    private byte velocity;
    private int revision;
    private int color;

    public KeyState() {
    }

    public boolean isPressed() {
        return pressed;
    }

    public void setPressed(boolean pressed) {
        this.pressed = pressed;
    }

    public boolean isAvailable() {
        return available;
    }

    public void setAvailable(boolean available) {
        this.available = available;
    }

    public byte getVelocity() {
        return velocity;
    }

    public void setVelocity(byte velocity) {
        this.velocity = velocity;
    }

    public int getRevision() {
        return revision;
    }

    public void setRevision(int revision) {
        this.revision = revision;
    }

    public int getColor() {
        return color;
    }

    public void setColor(int color) {
        this.color = color;
    }

    public void set(KeyState src) {
        if (src == null) {
            return;
        }
        this.available = src.available;
        this.color = src.color;
        this.pressed = src.pressed;
        this.revision = src.revision;
        this.velocity = src.velocity;
    }

}
