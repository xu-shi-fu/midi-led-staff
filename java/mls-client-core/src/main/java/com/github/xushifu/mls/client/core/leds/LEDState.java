package com.github.xushifu.mls.client.core.leds;

import com.github.xushifu.mls.network.mlscp.ARGB;

public final class LEDState {

    private ARGB rx; // 接收到的状态
    private ARGB mx; // 中间状态
    private ARGB tx; // 将要发送的状态

    private int index;

    public LEDState() {
        this.rx = ARGB.empty();
        this.mx = ARGB.empty();
        this.tx = ARGB.empty();
    }

    public ARGB getRx() {
        return rx;
    }

    public void setRx(ARGB c) {
        this.rx = ARGB.normalize(c);
    }

    public ARGB getTx() {
        return tx;
    }

    public void setTx(ARGB c) {
        this.tx = ARGB.normalize(c);
    }

    public ARGB getMx() {
        return mx;
    }

    public void setMx(ARGB c) {
        this.mx = ARGB.normalize(c);
    }

    public int getIndex() {
        return index;
    }

    public void setIndex(int index) {
        this.index = index;
    }

}
