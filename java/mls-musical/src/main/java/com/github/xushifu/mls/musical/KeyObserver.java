package com.github.xushifu.mls.musical;

public class KeyObserver {

    private KeyHolder holder;
    private int revision;
    private Callback callback;

    public KeyObserver(KeyHolder kh) {
        this.holder = kh;
    }

    public interface Callback {

        void onKeyStateChange(KeyHolder h);

    }

    public static void observe(KeyObserver observer) {
        if (observer == null) {
            return;
        }
        observer.observe();
    }

    public void observe() {
        final KeyHolder h = this.holder;
        final Callback cbk = this.callback;
        if (h == null || cbk == null) {
            return;
        }
        int r1 = h.getRevision();
        int r2 = this.revision;
        if (r1 == r2) {
            return;
        }
        cbk.onKeyStateChange(h);
        this.revision = r1;
    }

    public KeyHolder getHolder() {
        return holder;
    }

    public void setHolder(KeyHolder holder) {
        this.holder = holder;
    }

    public int getRevision() {
        return revision;
    }

    public void setRevision(int revision) {
        this.revision = revision;
    }

    public Callback getCallback() {
        return callback;
    }

    public void setCallback(Callback callback) {
        this.callback = callback;
    }

}
