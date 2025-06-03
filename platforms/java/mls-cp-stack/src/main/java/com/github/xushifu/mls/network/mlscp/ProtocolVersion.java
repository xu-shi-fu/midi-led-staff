package com.github.xushifu.mls.network.mlscp;

public class ProtocolVersion implements IntegerValue {

    int major; // :byte
    int minor; // :byte

    public ProtocolVersion() {
        this.major = 0;
        this.minor = 0;
    }

    public ProtocolVersion(int ver) {
        this.major = 0xff & (ver >> 8);
        this.minor = 0xff & (ver);
    }

    public ProtocolVersion(byte maj, byte min) {
        this.major = maj & 0x00ff;
        this.minor = min & 0x00ff;
    }

    @Override
    public int toInt() {
        return ((major << 8) & 0xff00) | (minor & 0x00ff);
    }

}
