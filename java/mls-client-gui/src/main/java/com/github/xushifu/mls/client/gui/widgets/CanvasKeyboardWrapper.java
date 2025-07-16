package com.github.xushifu.mls.client.gui.widgets;

import javax.swing.JComponent;

import com.bitwormhole.starter4j.swing.canvases.Canvas;
import com.bitwormhole.starter4j.swing.canvases.CanvasAdapter;
import com.github.xushifu.mls.musical.KeyboardAdapter;

public class CanvasKeyboardWrapper implements IKeyboardView {

    public CanvasKeyboardWrapper(IKeyboardView in) {
        this.mInner = in;
        this.tryOnCreate();
    }

    ///////////////////////////////////////////////////////
    /// protected

    protected void tryOnCreate() {
        if (!this.mHasOnCreateInvoked) {
            this.mHasOnCreateInvoked = true;
            this.onCreate();
        }
    }

    protected void onCreate() {
    }

    ///////////////////////////////////////////////////////
    /// private

    private final IKeyboardView mInner;
    private boolean mHasOnCreateInvoked = false;

    @Override
    public Canvas getCanvas() {
        return this.mInner.getCanvas();
    }

    @Override
    public CanvasAdapter getCanvasAdapter() {
        return this.mInner.getCanvasAdapter();
    }

    @Override
    public KeyboardAdapter getKeyboardAdapter() {
        return this.mInner.getKeyboardAdapter();
    }

    @Override
    public JComponent getComponent() {
        return this.mInner.getComponent();
    }

}
