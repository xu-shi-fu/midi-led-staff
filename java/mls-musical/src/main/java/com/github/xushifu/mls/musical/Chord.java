package com.github.xushifu.mls.musical;

// 表示一个具体的和弦 (例如 C#m7)
public final class Chord {

    public static Chord create(Tone root, ChordPattern pattern) {
        Builder b = new Builder();
        b.root = root;
        b.pattern = pattern;
        return b.build();
    }

    /**
     * 取模式
     */
    public ChordPattern getPattern() {
        return pattern;
    }

    /**
     * 取根音
     */
    public Tone getRoot() {
        return root;
    }

    public static class Builder {

        public Tone root;
        public ChordPattern pattern;

        public Chord build() {

            return new Chord(this);
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    /// private

    private final Tone root;
    private final ChordPattern pattern;

    private Chord(Builder b) {
        this.pattern = b.pattern;
        this.root = b.root;
    }

}
