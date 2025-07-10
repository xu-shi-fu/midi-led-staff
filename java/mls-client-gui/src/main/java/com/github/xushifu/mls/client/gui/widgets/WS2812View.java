package com.github.xushifu.mls.client.gui.widgets;

public class WS2812View extends LedView {

    public static WS2812View create() {
        WS2812View led = new WS2812View();
        led.onCreate();
        return led;
    }

    /////////////////////////////////////////////////////////////////////////
    /// private

    private WS2812View() {
    }

    @Override
    protected void onCreate() {
        super.onCreate();
    }
}
