package com.github.xushifu.mls.musical;

public final class Chords {

    ////////////////////////////////////////////////////////////////////////////
    /// chords

    /**
     * 大三和弦
     */
    public static Chord chordMajor(Tone root) {
        return Chord.create(root, patternMajor());
    }

    /**
     * 大7和弦
     */
    public static Chord chordMajor7(Tone root) {
        return Chord.create(root, patternMajor7());
    }

    ////////////////////////////////////////////////////////////////////////////
    /// patterns

    /**
     * 大三和弦 (模式)
     */

    public static ChordPattern patternMajor() {
        ChordPattern.Builder b = new ChordPattern.Builder();
        b.setName("Major");
        b.addStepLengths(0, 4, 3);
        return b.build();
    }

    /**
     * 大7和弦 (模式)
     */
    public static ChordPattern patternMajor7() {
        ChordPattern.Builder b = new ChordPattern.Builder();
        b.setName("maj7");
        b.addStepLengths(0, 3, 3, 3);
        return b.build();
    }

    ////////////////////////////////////////////////////////////////////////////
    /// others

    private Chords() {
    }
}
