package com.github.xushifu.mls.musical;

public class ToneStep {

    private int step;
    private Tone tone;

    public ToneStep() {
    }

    public int getStep() {
        return step;
    }

    public void setStep(int step) {
        this.step = step;
    }

    public Tone getTone() {
        return tone;
    }

    public void setTone(Tone tone) {
        this.tone = tone;
    }

    @Override
    public String toString() {
        return "[ToneStep step:" + step + ", tone:" + tone + "]";
    }

}
