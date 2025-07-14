package com.github.xushifu.mls.musical;

public class EmptyKeyHolder implements KeyHolder {

    private Key mKey;
    private KeyState mState;

    public EmptyKeyHolder() {
        this.mKey = Key.NONE;
        this.mState = new KeyState();
    }

    @Override
    public int getIndex() {
        return this.mKey.getIndex();
    }

    @Override
    public int getRevision() {
        return 0;
    }

    @Override
    public Key getKey() {
        return this.mKey;
    }

    @Override
    public KeyState getState() {
        return this.mState;
    }

    @Override
    public void setState(KeyState state) {
    }

}
