package com.github.xushifu.mls.musical;

public final class Modes {

    ////////////////////////////////////////////////////////////////////////////
    /// modes

    public static Mode ionian(Tone main) {
        return Mode.create(main, ionianPattern());
    }

    public static Mode dorian(Tone main) {
        return Mode.create(main, dorianPattern());
    }

    public static Mode phrygian(Tone main) {
        return Mode.create(main, phrygianPattern());
    }

    public static Mode lydian(Tone main) {
        return Mode.create(main, lydianPattern());
    }

    public static Mode mixolydian(Tone main) {
        return Mode.create(main, mixolydianPattern());
    }

    public static Mode aeolian(Tone main) {
        return Mode.create(main, aeolianPattern());
    }

    public static Mode locrian(Tone main) {
        return Mode.create(main, locrianPattern());
    }

    ////////////////////////////////////////////////////////////////////////////
    /// patterns

    /***
     * 伊奥尼亚 (自然大调,全全半全全全半)
     */
    public static ModePattern ionianPattern() {
        ModePattern.Builder b = new ModePattern.Builder();
        b.setName("ionian");
        b.addStepLengths(F, F, H, F, F, F, H);
        return b.build();
    }

    /***
     * 多利亚 (小调色彩, 全半全全全半全)
     */
    public static ModePattern dorianPattern() {
        ModePattern.Builder b = new ModePattern.Builder();
        b.setName("dorian");
        b.addStepLengths(F, H, F, F, F, H, F);
        return b.build();
    }

    /***
     * 弗利吉亚 (小调色彩, 半全全全半全全)
     */
    public static ModePattern phrygianPattern() {
        ModePattern.Builder b = new ModePattern.Builder();
        b.setName("phrygian");
        b.addStepLengths(H, F, F, F, H, F, F);
        return b.build();
    }

    /***
     * 利底亚 (大调色彩, 全全全半全全半)
     */
    public static ModePattern lydianPattern() {
        ModePattern.Builder b = new ModePattern.Builder();
        b.setName("lydian");
        b.addStepLengths(F, F, F, H, F, F, H);
        return b.build();
    }

    /***
     * 混合利底亚 (大调色彩, 全全半全全半全)
     */
    public static ModePattern mixolydianPattern() {
        ModePattern.Builder b = new ModePattern.Builder();
        b.setName("mixolydian");
        b.addStepLengths(F, F, H, F, F, H, F);
        return b.build();
    }

    /***
     * 爱奥尼亚 (自然小调, 全半全全半全全)
     */
    public static ModePattern aeolianPattern() {
        ModePattern.Builder b = new ModePattern.Builder();
        b.setName("aeolian");
        b.addStepLengths(F, H, F, F, H, F, F);
        return b.build();
    }

    /***
     * 洛克利亚 (减和弦色彩, 半全全半全全全)
     */
    public static ModePattern locrianPattern() {
        ModePattern.Builder b = new ModePattern.Builder();
        b.setName("locrian");
        b.addStepLengths(H, F, F, H, F, F, F);
        return b.build();
    }

    ////////////////////////////////////////////////////////////////////////////
    /// others

    static final int H = 1; // half
    static final int F = 2; // full

    private Modes() {
    }
}
