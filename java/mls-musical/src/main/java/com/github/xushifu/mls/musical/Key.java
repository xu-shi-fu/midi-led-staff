package com.github.xushifu.mls.musical;

/*****
 * Key 表示一个有具体音高的琴键
 */
public final class Key {

    public final static class Builder {

        public int index;
        public Group group;
        public Tone tone;
        public float frequency;

        public Key build() {
            return new Key(this);
        }
    }

    public int getIndex() {
        return index;
    }

    public Group getGroup() {
        return group;
    }

    public Tone getTone() {
        return tone;
    }

    public float getFrequency() {
        return frequency;
    }

    @Override
    public String toString() {
        return this.name;
    }

    // public static Key[] all() {
    // Key[] src = the128Keys;
    // return Arrays.copyOf(src, src.length);
    // }

    ////////////////////////////////////////////////////////////////////////////
    /// private

    // fields of instance

    private final int index;
    private final Group group;
    private final Tone tone;
    private final float frequency;
    private final String name;

    // static fields of class

    private Key(Builder b) {
        this.group = b.group;
        this.index = b.index;
        this.tone = b.tone;
        this.frequency = b.frequency;
        this.name = b.tone + "" + b.group.getNumber();
    }

}
