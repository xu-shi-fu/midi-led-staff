package com.github.xushifu.mls.client.core.leds;

import com.github.xushifu.mls.client.RequestOptions;

public interface LEDService {

    LEDStateBuffer getStateBuffer();

    void fetch(FetchOptions options);

    void push(PushOptions options);

    static class FetchOptions extends RequestOptions {
        public int partSize;
        public int partPosition;
    }

    static class PushOptions extends RequestOptions {
    }

}
