package com.github.xushifu.mls.musical;

// 表示某个类型的和弦 (例如: 大三, 增三, 小大七, 等)
public final class ChordPattern {

    public String getName() {
        return inner.getName();
    }

    public static class Builder {

        private final TonePattern.Builder inner;

        public Builder() {
            this.inner = new TonePattern.Builder();
            this.inner.type = TonePattern.Type.CHORD;
        }

        public Builder addStep(int step) {
            this.inner.addStep(step);
            return this;
        }

        public Builder addSteps(int... steps) {
            this.inner.addSteps(steps);
            return this;
        }

        public Builder addStepLengths(int... lengths) {
            this.inner.addStepLengths(lengths);
            return this;
        }

        public Builder setName(String name) {
            this.inner.name = name;
            return this;
        }

        public ChordPattern build() {
            TonePattern tp = this.inner.build();
            return new ChordPattern(tp);
        }

    }

    //////////////////////////////////////////////////////////////////////////////
    /// private

    private final TonePattern inner;

    private ChordPattern(TonePattern in) {
        this.inner = in;
    }
}
