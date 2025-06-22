package com.github.xushifu.mls.musical;

import java.util.ArrayList;
import java.util.List;

public final class TonePattern {

    public enum Type {
        MODE, CHORD
    }

    /**
     * 根据指定的基础音, 返回对应的音阶
     */
    public ToneStep[] getSteps(Tone base) {
        final int[] src = this.steps;
        final ToneStep[] dst = new ToneStep[src.length];
        final int pos0 = base.getPosition();
        for (int i = 0; i < src.length; i++) {
            final int step = src[i];
            Tone t = Tone.getInstance(pos0 + step);
            ToneStep ts = new ToneStep();
            ts.setTone(t);
            ts.setStep(step);
            dst[i] = ts;
        }
        return dst;
    }

    public Tone[] getTones(Tone base) {
        ToneStep[] src = this.getSteps(base);
        Tone[] dst = new Tone[src.length];
        for (int i = 0; i < src.length; i++) {
            dst[i] = src[i].getTone();
        }
        return dst;
    }

    public Type getType() {
        return type;
    }

    public String getName() {
        return name;
    }

    public static class Builder {

        public String name;
        public Type type;
        public final List<Integer> steps;

        public Builder() {
            this.steps = new ArrayList<>();
        }

        public Builder addStepLengths(int... lengths) {
            int step = 0;
            for (int len : lengths) {
                this.steps.add(step);
                step += len;
            }
            return this;
        }

        public Builder addSteps(int... step_array) {
            for (int step : step_array) {
                this.steps.add(step);
            }
            return this;
        }

        public Builder addStep(int step) {
            this.steps.add(step);
            return this;
        }

        public TonePattern build() {

            if (name == null) {
                name = "unnamed";
            }
            if (type == null) {
                type = Type.MODE;
            }

            return new TonePattern(this);
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    /// private

    private final int[] steps; // 表示相对于基础音高的半音阶 ; 0=主音(对于mode),或根音(对于chord)
    private final String name;
    private final Type type;

    private TonePattern(Builder b) {
        this.name = b.name;
        this.type = b.type;
        this.steps = stepsToArray(b);
    }

    private static int[] stepsToArray(Builder b) {
        List<Integer> src = b.steps;
        int[] dst = new int[src.size()];
        for (int i = 0; i < dst.length; i++) {
            dst[i] = src.get(i);
        }
        return dst;
    }

}
