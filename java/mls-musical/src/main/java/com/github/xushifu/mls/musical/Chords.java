package com.github.xushifu.mls.musical;

public final class Chords {

    ////////////////////////////////////////////////////////////////////////////
    /// chords

    /**
     * 大三和弦
     */
    public static Chord major(Tone root) {
        return Chord.create(root, patternMajor());
    }

    public static Chord minor(Tone root) {
        return Chord.create(root, patternMinor());
    }

    public static Chord aug(Tone root) {
        return Chord.create(root, patternAugmented());
    }

    public static Chord dim(Tone root) {
        return Chord.create(root, patternDiminished());
    }

    /**
     * 大7和弦
     */
    public static Chord major7(Tone root) {
        return Chord.create(root, patternMajor7th());
    }

    public static Chord dom7(Tone root) {
        return Chord.create(root, patternDominant7th());
    }

    public static Chord minor7(Tone root) {
        return Chord.create(root, patternMinor7th());
    }

    public static Chord minor7b5(Tone root) {
        return Chord.create(root, patternMinor7b5());
    }

    public static Chord dim7(Tone root) {
        return Chord.create(root, patternDiminished7th());
    }

    ////////////////////////////////////////////////////////////////////////////
    /// patterns

    /**
     * 大三和弦 (模式)
     */

    public static ChordPattern patternMajor() {
        ChordPattern.Builder b = new ChordPattern.Builder();
        b.setName("maj");
        b.addSteps(0, 4, 7);
        return b.build();
    }

    public static ChordPattern patternMinor() {
        ChordPattern.Builder b = new ChordPattern.Builder();
        b.setName("min");
        b.addSteps(0, 3, 7);
        return b.build();
    }

    public static ChordPattern patternAugmented() {
        ChordPattern.Builder b = new ChordPattern.Builder();
        b.setName("aug");
        b.addSteps(0, 4, 8);
        return b.build();
    }

    public static ChordPattern patternDiminished() {
        ChordPattern.Builder b = new ChordPattern.Builder();
        b.setName("dim");
        b.addSteps(0, 3, 6);
        return b.build();
    }

    /**
     * 大7和弦 (模式)
     */
    public static ChordPattern patternMajor7th() {
        ChordPattern.Builder b = new ChordPattern.Builder();
        b.setName("maj7");
        b.addSteps(0, 4, 7, 11);
        return b.build();
    }

    public static ChordPattern patternDominant7th() {
        ChordPattern.Builder b = new ChordPattern.Builder();
        b.setName("dom7");
        b.addSteps(0, 4, 7, 10);
        return b.build();
    }

    public static ChordPattern patternMinor7th() {
        ChordPattern.Builder b = new ChordPattern.Builder();
        b.setName("min7");
        b.addSteps(0, 3, 7, 10);
        return b.build();
    }

    public static ChordPattern patternMinor7b5() {
        ChordPattern.Builder b = new ChordPattern.Builder();
        b.setName("min7b5");
        b.addSteps(0, 3, 6, 10);
        return b.build();
    }

    public static ChordPattern patternDiminished7th() {
        ChordPattern.Builder b = new ChordPattern.Builder();
        b.setName("dim7");
        b.addSteps(0, 3, 6, 9);
        return b.build();
    }

    ////////////////////////////////////////////////////////////////////////////
    /// others

    private Chords() {
    }
}
