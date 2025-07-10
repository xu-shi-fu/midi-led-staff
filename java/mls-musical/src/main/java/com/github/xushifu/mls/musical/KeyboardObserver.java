package com.github.xushifu.mls.musical;

public class KeyboardObserver {

    private KeyboardAdapter adapter;
    private Callback callback;
    private int revision;

    public KeyboardObserver(KeyboardAdapter adapter) {
    }

    public interface Callback {
        void onKeyboardStateChange(KeyboardAdapter adapter);
    }

    public static void observe(KeyboardObserver observer) {
        if (observer == null) {
            return;
        }
        observer.observe();
    }

    public void observe() {
        final KeyboardAdapter ada = this.adapter;
        final Callback cbk = this.callback;
        if (ada == null || cbk == null) {
            return;
        }
        final int rev = ada.getRevision();
        if (rev == this.revision) {
            return;
        }
        cbk.onKeyboardStateChange(ada);
        this.revision = rev;
    }

    public KeyboardAdapter getAdapter() {
        return adapter;
    }

    public void setAdapter(KeyboardAdapter adapter) {
        this.adapter = adapter;
    }

    public Callback getCallback() {
        return callback;
    }

    public void setCallback(Callback callback) {
        this.callback = callback;
    }

    public int getRevision() {
        return revision;
    }

    public void setRevision(int revision) {
        this.revision = revision;
    }

}
