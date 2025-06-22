package com.github.xushifu.mls.musical;

// 表示某个类型的调式(例如: 大调,小调, Dorian, Lydian 等)
public class ModePattern {

    public String getName() {
        return inner.getName();
    }

    public Tone[] getTones(Tone main) {
        return this.inner.getTones(main);
    }

    public ToneStep[] getSteps(Tone main) {
        return this.inner.getSteps(main);
    }

    public static class Builder {

        private final TonePattern.Builder inner;

        public Builder() {
            this.inner = new TonePattern.Builder();
            this.inner.type = TonePattern.Type.MODE;
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

        public ModePattern build() {
            TonePattern tp = this.inner.build();
            return new ModePattern(tp);
        }
    }

    //////////////////////////////////////////////////////////////////////////////
    /// private

    private final TonePattern inner;

    private ModePattern(TonePattern in) {
        this.inner = in;
    }

}
