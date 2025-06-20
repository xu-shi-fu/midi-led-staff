package com.github.xushifu.mls.musical;

public class KeyboardWrapper implements Keyboard {

    private final Keyboard inner;

    protected KeyboardWrapper(Keyboard in) {
        this.inner = in;
    }

    @Override
    public Key getKey(int index) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'getKey'");
    }

    @Override
    public int getKeyCount() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'getKeyCount'");
    }

}
