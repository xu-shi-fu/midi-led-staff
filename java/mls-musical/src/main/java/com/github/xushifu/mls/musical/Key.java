package com.github.xushifu.mls.musical;

/*****
 * Key 表示一个有具体音高的琴键
 */
public final class Key {

    public int getIndex() {
        return index;
    }

    public Group getGroup() {
        return group;
    }

    public Tone getTone() {
        return tone;
    }

    public int getMidiNumber() {
        return this.index;
    }

    public float getFrequency() {
        return frequency;
    }

    public String getName() {
        return name;
    }

    @Override
    public String toString() {
        StringBuilder b = new StringBuilder();
        b.append("[Key");
        b.append(" index:").append(this.index);
        b.append(" group:").append(this.group);
        b.append(" tone:").append(this.tone);
        b.append(" name:").append(this.name);
        b.append(" freq:").append(this.frequency);
        b.append(']');
        return b.toString();
    }

    public static Key[] all() {
        return Midi128Keys.allKeys();
    }

    public final static class Builder {

        public int index;
        public Group group;
        public Tone tone;
        public float frequency;

        public Key build() {
            return new Key(this);
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    /// private

    private final int index; // aka. MIDI number, 0-127
    private final Group group;
    private final Tone tone;
    private final float frequency;
    private final String name;

    private Key(Builder b) {
        this.group = b.group;
        this.index = b.index;
        this.tone = b.tone;
        this.frequency = b.frequency;
        this.name = b.tone.getName() + b.group.getNumber();
    }

}
