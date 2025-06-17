package com.github.xushifu.mls.client.core.leds;

import com.github.xushifu.mls.network.mlscp.ARGB;

public class LEDState {

    private ARGB rx; // 接收到的状态
    private ARGB tx; // 将要发送的状态

    public LEDState() {
    }

    public ARGB getRx() {
        return rx;
    }

    public void setRx(ARGB rx) {
        this.rx = rx;
    }

    public ARGB getTx() {
        return tx;
    }

    public void setTx(ARGB tx) {
        this.tx = tx;
    }

}
