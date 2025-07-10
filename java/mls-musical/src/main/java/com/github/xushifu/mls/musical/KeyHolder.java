package com.github.xushifu.mls.musical;

public interface KeyHolder {

    int getIndex();

    int getRevision();

    Key getKey();

    KeyState getState();

    void setState(KeyState state);

}
