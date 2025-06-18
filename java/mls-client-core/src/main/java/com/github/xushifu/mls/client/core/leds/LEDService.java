package com.github.xushifu.mls.client.core.leds;

import com.github.xushifu.mls.client.RequestOptions;

public interface LEDService {

    LEDStateBuffer getStateBuffer();

    void fetch(FetchOptions options);

    void push(PushOptions options);

    public static class FetchOptions extends RequestOptions {
        public int partSize;
        public int partPosition;
    }

    public static class PushOptions extends RequestOptions {
        public int viewSize;
        public int viewPosition;

        /**
         * 把需要发送的 led 设置为 'true'
         */
        public final boolean[] leds;

        public PushOptions() {
            this.leds = new boolean[128];
        }

        public PushOptions addPart(int pos, int count) {
            final int max = this.leds.length;
            for (int i = 0; i < count; i++) {
                final int index = pos + i;
                if ((0 <= index) && (index < max)) {
                    this.leds[index] = true;
                } else {
                    break;
                }
            }
            return this;
        }

    }
}
