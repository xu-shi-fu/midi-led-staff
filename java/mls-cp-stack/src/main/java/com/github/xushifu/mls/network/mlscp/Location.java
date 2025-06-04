package com.github.xushifu.mls.network.mlscp;

public final class Location {

    private final String path;

    private Location(String aPath) {
        this.path = aPath;
    }

    @Override
    public String toString() {
        return this.path;
    }

    public final static Location PING = new Location("/ping");
    public final static Location EXAMPLE = new Location("/example");
}
