package com.github.xushifu.mls.client.gui.widgets;

import java.awt.BorderLayout;

import javax.swing.JPanel;

import com.github.xushifu.mls.musical.KeyboardAdapter;

/***
 * CanvasKeyboardOverview 实现一个键盘的概览视图
 */
public class CanvasKeyboardOverview extends JPanel {

    ////////////////////////////////////////////////////////////////////////////
    // public

    public final static class Builder {

        private KeyboardAdapter keyboard;
        private CanvasKeyboardTheme theme;

        public CanvasKeyboardOverview create() {
            CanvasKeyboardOverview view = new CanvasKeyboardOverview(this);
            view.onCreate();
            return view;
        }

        public KeyboardAdapter getKeyboard() {
            return keyboard;
        }

        public void setKeyboard(KeyboardAdapter keyboard) {
            this.keyboard = keyboard;
        }

    }

    public static Builder newBuilder() {

        return new Builder();
    }

    ////////////////////////////////////////////////////////////////////////////
    // private

    private CanvasKeyboardView mInnerView;
    private CanvasKeyboardView.Builder mInnerViewBuilder;

    private CanvasKeyboardOverview(Builder b) {

        CanvasKeyboardView.Builder ckv_builder = CanvasKeyboardView.newBuilder();
        ckv_builder.setKeyboard(b.keyboard);
        ckv_builder.setScrollable(false);
        this.mInnerViewBuilder = ckv_builder;

    }

    private void onCreate() {
        CanvasKeyboardView.Builder ckv_builder = this.mInnerViewBuilder;
        CanvasKeyboardView inner = ckv_builder.create();

        this.mInnerView = inner;
        this.setLayout(new BorderLayout());
        this.add(inner, BorderLayout.CENTER);

    }

}
