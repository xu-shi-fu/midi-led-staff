package com.github.xushifu.mls.client;

public class MLSClientConfig {

    private String serverHost;
    private int serverPort;
    private int clientPort;
    private int timeout;

    public MLSClientConfig() {
        // 这里用一组默认参数初始化这个对象
        this.serverHost = "192.168.1.10";
        this.serverPort = 7923;
        this.clientPort = 7921;
        this.timeout = 10 * 1000;
    }

    public String getServerHost() {
        return serverHost;
    }

    public void setServerHost(String serverHost) {
        this.serverHost = serverHost;
    }

    public int getServerPort() {
        return serverPort;
    }

    public void setServerPort(int serverPort) {
        this.serverPort = serverPort;
    }

    public int getClientPort() {
        return clientPort;
    }

    public void setClientPort(int clientPort) {
        this.clientPort = clientPort;
    }

    public int getTimeout() {
        return timeout;
    }

    public void setTimeout(int timeout) {
        this.timeout = timeout;
    }

}
