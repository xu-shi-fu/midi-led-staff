package com.github.xushifu.mls.client;

import java.io.IOException;

final class MLSClient4test {

    public static MLSClient openClient() throws IOException {
        MLSClientConfig cfg = new MLSClientConfig();
        cfg.setServerHost("192.168.0.101");
        cfg.setServerPort(7923);
        return MLSClient.open(cfg);
    }

}
