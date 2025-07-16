package com.github.xushifu.mls.client.gui.widgets;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Point;

import com.bitwormhole.starter4j.swing.boxes.CLabel;
import com.bitwormhole.starter4j.swing.canvases.BoxStyle;
import com.bitwormhole.starter4j.swing.canvases.LineStyle;
import com.bitwormhole.starter4j.swing.canvases.RenderContext;
import com.github.xushifu.mls.musical.DefaultKeyboardAdapter;
import com.github.xushifu.mls.musical.KeyboardAdapter;

/***
 * CanvasKeyboardOverview 实现一个键盘的概览视图
 */
public class CanvasKeyboardOverview extends CanvasKeyboardWrapper {

    ////////////////////////////////////////////////////////////////////////////
    // public

    public static CanvasKeyboardOverview create() {
        MyBuilder builder = new MyBuilder();
        builder.init();
        return builder.create();
    }

    public static CanvasKeyboardOverview create(KeyboardAdapter ka) {
        MyBuilder builder = new MyBuilder();
        builder.init(ka);
        return builder.create();
    }

    public static CanvasKeyboardOverview create(IKeyboardView in) {
        MyBuilder builder = new MyBuilder();
        builder.init(in);
        return builder.create();
    }

    ////////////////////////////////////////////////////////////////////////////
    // private

    private CanvasKeyboardOverview(IKeyboardView in) {
        super(in);
    }

    private static class MyBuilder {

        private IKeyboardView inner;

        void init() {

            KeyboardAdapter ka = new DefaultKeyboardAdapter();

            CanvasKeyboardView.Builder ckv_builder = CanvasKeyboardView.newBuilder();
            ckv_builder.setKeyboard(ka);
            ckv_builder.setScrollable(false);
            this.inner = ckv_builder.create();
        }

        void init(KeyboardAdapter ka) {

            CanvasKeyboardView.Builder ckv_builder = CanvasKeyboardView.newBuilder();
            ckv_builder.setKeyboard(ka);
            ckv_builder.setScrollable(false);
            this.inner = ckv_builder.create();

        }

        void init(IKeyboardView in) {
            this.inner = in;
        }

        BoxStyle useVRBoxStyle(BoxStyle style) {

            if (style == null) {
                style = new BoxStyle();
            }

            style.setBorderColor(Color.RED);
            style.setBorderWidth(15);
            style.setBorderStyle(LineStyle.SOLID);
            style.setForegroundColor(Color.RED);

            return style;
        }

        CanvasKeyboardOverview create() {

            MyViewportRangeBox vrbox = new MyViewportRangeBox();
            BoxStyle style = vrbox.getStyle();
            vrbox.setText("viewport");
            vrbox.setStyle(this.useVRBoxStyle(style));

            vrbox.setWantSize(new Dimension());
            vrbox.setSize(new Dimension());
            vrbox.setPositionAtCanvas(new Point());

            IKeyboardView in = this.inner;
            in.getCanvas().add(vrbox);

            return new CanvasKeyboardOverview(in);
        }
    }

    private static class MyViewportRangeBox extends CLabel {

        @Override
        protected void onPaintBackground(RenderContext rc) {
            // super.onPaintBackground(rc);
        }

    }

}
