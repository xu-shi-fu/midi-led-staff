package com.github.xushifu.mls.musical;

/**
 * 表示一个具体的调式 (例如: F-major)
 */
public final class Mode {

    public static Mode create(Tone main, ModePattern pattern) {
        Builder b = new Builder();
        b.main = main;
        b.pattern = pattern;
        b.name = null; // as default
        return b.build();
    }

    public Tone[] getTones() {
        return this.pattern.getTones(this.main);
    }

    public ToneStep[] getSteps() {
        return this.pattern.getSteps(this.main);
    }

    public Tone getMain() {
        return main;
    }

    public String getName() {
        return name;
    }

    public ModePattern getPattern() {
        return pattern;
    }

    @Override
    public String toString() {
        return "[Mode " + this.name + "]";
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + ((main == null) ? 0 : main.hashCode());
        result = prime * result + ((pattern == null) ? 0 : pattern.hashCode());
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (obj == null)
            return false;
        if (getClass() != obj.getClass())
            return false;
        Mode other = (Mode) obj;
        if (main == null) {
            if (other.main != null)
                return false;
        } else if (!main.equals(other.main))
            return false;
        if (pattern == null) {
            if (other.pattern != null)
                return false;
        } else if (!pattern.equals(other.pattern))
            return false;
        return true;
    }

    public static class Builder {

        String name;
        ModePattern pattern;
        Tone main;

        public Mode build() {

            if (this.main == null) {
                this.main = Tone.C; // 默认 C 调
            }

            if (this.pattern == null) {
                this.pattern = Modes.ionianPattern(); // 默认自然大调
            }

            if (this.name == null) {
                this.name = makeName(this);
            }

            return new Mode(this);
        }
    }

    //////////////////////////////////////////////////////////////////////
    /// private
    ///

    private final Tone main; // 主音
    private final ModePattern pattern;
    private final String name;

    private Mode(Builder b) {
        this.name = b.name;
        this.main = b.main;
        this.pattern = b.pattern;
    }

    private static String makeName(Builder b) {
        String s1 = b.main.getName();
        String s2 = b.pattern.getName();
        return s1 + '-' + s2;
    }

}
