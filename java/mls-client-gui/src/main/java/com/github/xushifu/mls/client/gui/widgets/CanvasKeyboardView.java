package com.github.xushifu.mls.client.gui.widgets;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JPanel;
import javax.swing.JScrollPane;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.bitwormhole.starter4j.swing.boxes.CGroup;
import com.bitwormhole.starter4j.swing.boxes.CLabel;
import com.bitwormhole.starter4j.swing.boxes.CSpace;
import com.bitwormhole.starter4j.swing.canvases.Box;
import com.bitwormhole.starter4j.swing.canvases.BoxContainer;
import com.bitwormhole.starter4j.swing.canvases.BoxStyle;
import com.bitwormhole.starter4j.swing.canvases.Canvas;
import com.bitwormhole.starter4j.swing.canvases.CanvasAdapter;
import com.bitwormhole.starter4j.swing.canvases.Getters;
import com.bitwormhole.starter4j.swing.canvases.ILayout;
import com.bitwormhole.starter4j.swing.canvases.LayoutContext;
import com.bitwormhole.starter4j.swing.canvases.LineStyle;
import com.bitwormhole.starter4j.swing.canvases.MouseEventContext;
import com.bitwormhole.starter4j.swing.canvases.RenderContext;
import com.bitwormhole.starter4j.swing.canvases.MouseEventContext.MouseEvent;
import com.bitwormhole.starter4j.swing.layouts.LinearLayout;
import com.github.xushifu.mls.musical.Key;
import com.github.xushifu.mls.musical.Tone;

public class CanvasKeyboardView extends JPanel {

    static final Logger logger = LoggerFactory.getLogger(CanvasKeyboardView.class);

    // public static CanvasKeyboardView create() {
    // CanvasKeyboardView view = new CanvasKeyboardView();
    // view.onCreate();
    // return view;
    // }

    public double getScale() {
        return scale;
    }

    public void setScale(double scale) {
        this.scale = scale;
    }

    public static class Builder {

        private boolean scrollable;

        public Builder() {
        }

        public boolean isScrollable() {
            return scrollable;
        }

        public void setScrollable(boolean scrollable) {
            this.scrollable = scrollable;
        }

        public CanvasKeyboardView create() {
            CanvasKeyboardView view = new CanvasKeyboardView(this);
            view.onCreate();
            return view;
        }
    }

    public static Builder newBuilder() {
        return new Builder();
    }

    ////////////////////////////////////////////////////////////////////////////
    /// private

    private double scale; // [0.01,1]; 1 = 显示 100% 全部按键; <1, 表示放大

    private final InnerContext mContext;

    private CanvasKeyboardView(Builder b) {

        InnerContext ctx = new InnerContext();
        ctx.scrollable = b.scrollable;

        this.scale = 1;
        this.mContext = ctx;
    }

    private void onCreate() {

        // mAdapter.setPreferredSize(new Dimension(1024, 100));

        this.onCreateKeys();
        this.onCreateLayout();

        logger.info(this + ".onCreate() : done");
    }

    private void onCreateLayout() {

        final InnerContext ctx = this.mContext;
        final Canvas canvas = ctx.canvas;
        final CanvasAdapter adapter = ctx.adapter;
        final InnerSmallKeyBar smallKeyBar = new InnerSmallKeyBar(ctx);
        final InnerBigKeyBar bigKeyBar = new InnerBigKeyBar(ctx);
        final InnerKeyBarLayout keyBarLayout = new InnerKeyBarLayout(bigKeyBar, smallKeyBar);

        // canvas
        canvas.setLayout(keyBarLayout);
        canvas.add(bigKeyBar);
        canvas.add(smallKeyBar);

        // adapter
        adapter.setSize(new Dimension(1024, 100));

        // scroll-view
        ctx.scroller.setViewportView(adapter);
        ctx.scroller.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        ctx.scroller.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_NEVER);

        // this
        this.setLayout(new BorderLayout());
        this.add(ctx.scroller, BorderLayout.CENTER);

        // invoke onCreate
        ctx.bigKeyBar = bigKeyBar;
        ctx.smallKeyBar = smallKeyBar;
        smallKeyBar.onCreate();
        bigKeyBar.onCreate();
    }

    private void onCreateKeys() {
        InnerContext ctx = this.mContext;
        InnerKeyInfo[] all = ctx.keys;
        for (int i = 0; i < all.length; i++) {
            InnerKeyInfo info = new InnerKeyInfo(i);
            all[i] = info;
        }
    }

    static boolean isWhite(InnerSmallKey sk) {
        boolean sharp = sk.info.tone.isSharp();
        return !sharp;
    }

    static boolean isWhite(InnerKeyInfo info) {
        boolean sharp = info.tone.isSharp();
        return !sharp;
    }

    static boolean isBlack(InnerSmallKey sk) {
        boolean sharp = sk.info.tone.isSharp();
        return sharp;
    }

    private static class InnerContext {

        final Canvas canvas;
        final CanvasAdapter adapter;
        final JScrollPane scroller;
        final InnerKeyInfo[] keys; // 12(keys) x 11(group) = 132(keys)

        InnerSmallKeyBar smallKeyBar;
        InnerBigKeyBar bigKeyBar;
        boolean scrollable;

        InnerContext() {

            CanvasAdapter ada = new CanvasAdapter();

            this.keys = new InnerKeyInfo[12 * 11];
            this.canvas = ada.getCanvas();
            this.adapter = ada;
            this.scroller = new JScrollPane();
        }

    }

    private static class InnerView extends CGroup {

        final InnerContext context;

        InnerView(InnerContext ctx) {
            this.context = ctx;
        }

        // @Override
        void onCreate() {
        }

    }

    private static class InnerKey extends InnerView {

        final InnerKeyInfo info;

        InnerKey(InnerContext ctx, InnerKeyInfo ki) {
            super(ctx);
            this.info = ki;
        }

        @Override
        void onCreate() {

            this.setSize(null);
            this.setWantSize(null);
            this.setWeight(1);

            this.onCreateKey();
        }

        // @Override
        void onCreateKey() {

            BoxStyle st = this.getStyle();
            st = Getters.notNull(st);

            st.setBorderLeftColor(Color.red);
            st.setBorderLeftStyle(LineStyle.SOLID);
            st.setBorderLeftWidth(1);

            st.setBackgroundColor(Color.gray);

            this.setStyle(st);
            this.setWeight(1);

            // this.setWantSize(new Dimension());
            // this.setSize(new Dimension());
        }

        boolean isBlackKey() {
            return this.info.tone.isSharp();
        }

        @Override
        protected void onMouseEvent(MouseEventContext mec) {
            super.onMouseEvent(mec);

            MouseEvent evt = mec.getEvent();
            if (MouseEvent.MOVED.equals(evt)) {
                this.setKeyTipText();
            }
        }

        void setKeyTipText() {
            Key key = this.info.key;
            float freq = key.getFrequency();
            int midi = key.getMidiNumber();
            String name = key.getName();
            String txt = name + " (KEY:" + midi + ", " + freq + " Hz)";
            this.context.adapter.setToolTipText(txt);
        }

    }

    private static class InnerBigKey extends InnerKey {

        // 大键, 每组 7 个

        // private CLabel mLabel;

        InnerBigKey(InnerContext ctx, InnerKeyInfo ki) {
            super(ctx, ki);
        }

        @Override
        void onCreate() {
            super.onCreate();

            Key key = this.info.key;
            String name = "";
            CLabel label = new CLabel();
            CSpace space = new CSpace();

            if (isCKey(key)) {
                name = key.getName();
            }

            space.setWeight(90);
            space.setWantSize(null);

            label.setText(name);
            label.setWeight(10);
            label.setWantSize(null);
            label.getStyle().setBackgroundColor(null);

            this.setLayout(new LinearLayout(LinearLayout.VERTICAL));
            this.add(space);
            this.add(label);
        }

        boolean isCKey(Key k) {
            Tone t1 = k.getTone();
            Tone t2 = Tone.C;
            return t2.equals(t1);
        }

        @Override
        void onCreateKey() {
            super.onCreateKey();

            BoxStyle st = this.getStyle();
            st = Getters.notNull(st);
            this.applyBaseStyle(st);
            if (this.info.key.isAvailable()) {
                this.applyNormalStyle(st);
            }

            this.setStyle(st);
        }

        void applyBaseStyle(BoxStyle bs) {
            bs.setBorderTopStyle(null);
            bs.setBorderLeftStyle(null);
            bs.setBorderRightStyle(null);
            bs.setBorderBottomStyle(null);

            bs.setBorderTopColor(null);
            bs.setBorderLeftColor(null);
            bs.setBorderRightColor(null);
            bs.setBorderBottomColor(null);
        }

        void applyNormalStyle(BoxStyle bs) {
            bs.setBackgroundColor(Color.white);
            bs.setBorderColor(Color.black);
            bs.setBorderStyle(LineStyle.SOLID);
            bs.setBorderWidth(1);
        }

        @Override
        protected void onPaintForeground(RenderContext rc) {
            super.onPaintForeground(rc);
        }

    }

    private static class InnerKeyInfo {

        final int index;
        final Tone tone;
        final Key key;

        InnerKeyInfo(int idx) {

            Key k = Key.getKeyAt(idx);

            this.index = idx;
            this.key = k;
            this.tone = k.getTone();
        }

    }

    private static class InnerLinearLayout extends LinearLayout {

        public InnerLinearLayout(Direction direction) {
            super(direction);
        }

        @Override
        public void onBuildLayoutContainer(LayoutContext lc, BoxContainer cantainer) {
            super.onBuildLayoutContainer(lc, cantainer);
        }

        @Override
        public void onBuildLayoutPost(LayoutContext lc, BoxContainer cantainer) {
            super.onBuildLayoutPost(lc, cantainer);
        }

        @Override
        public void onBuildLayoutPre(LayoutContext lc, BoxContainer cantainer) {
            super.onBuildLayoutPre(lc, cantainer);
        }

    }

    private static class InnerBigKeyBar extends InnerView {

        InnerBigKey[] keys;

        InnerBigKeyBar(InnerContext ctx) {
            super(ctx);
        }

        @Override
        void onCreate() {

            BoxStyle st = this.getStyle();
            st.setBackgroundColor(null);

            this.setStyle(st);
            this.setLayout(new InnerLinearLayout(LinearLayout.HORIZONTAL));

            this.onCreateKeys();
        }

        private void onCreateKeys() {

            final InnerContext ctx = this.context;
            final InnerKeyInfo[] src = ctx.keys;
            final List<InnerBigKey> tmp = new ArrayList<>();

            for (InnerKeyInfo info : src) {
                if (isWhite(info)) {
                    InnerBigKey k = new InnerBigKey(ctx, info);
                    k.onCreate();
                    tmp.add(k);
                    this.add(k);
                }
            }

            this.keys = tmp.toArray(new InnerBigKey[0]);
        }

    }

    private static class InnerSmallKey extends InnerKey {

        // 小键, 每组 12 个

        private InnerLED mLED;

        InnerSmallKey(InnerContext ctx, InnerKeyInfo ki) {
            super(ctx, ki);
        }

        @Override
        void onCreate() {
            super.onCreate();
            this.onCreateLED();
        }

        void onCreateLED() {

            InnerLED led = new InnerLED();
            CSpace space = new CSpace();

            led.setWeight(25);
            led.setWantSize(null);

            space.setWeight(75);
            space.setWantSize(null);

            this.setLayout(new LinearLayout(LinearLayout.VERTICAL));
            this.mLED = led;
            this.add(led);
            this.add(space);
        }

        @Override
        void onCreateKey() {
            super.onCreateKey();

            BoxStyle st = this.getStyle();
            st = Getters.notNull(st);

            this.applyDefaultStyle(st);
            if (this.isBlackKey()) {
                this.applyBlackKeyStyle(st);
            } else {
                this.applyWhiteKeyStyle(st);
            }
            this.setStyle(st);
        }

        void applyDefaultStyle(BoxStyle st) {

            st.setBorderTopColor(null);
            st.setBorderLeftColor(null);
            st.setBorderRightColor(null);
            st.setBorderBottomColor(null);

            st.setBorderTopStyle(null);
            st.setBorderLeftStyle(null);
            st.setBorderRightStyle(null);
            st.setBorderBottomStyle(null);
        }

        void applyBlackKeyStyle(BoxStyle st) {
            if (this.info.key.isAvailable()) {
                st.setBackgroundColor(Color.black);
                st.setBorderColor(Color.gray);
            }
        }

        void applyWhiteKeyStyle(BoxStyle st) {
            if (this.info.key.isAvailable()) {
                st.setBackgroundColor(null);
                st.setBorderStyle(LineStyle.NONE);
            }
        }
    }

    private static class InnerSmallKeyBar extends InnerView {

        InnerSmallKey[] keys;

        InnerSmallKeyBar(InnerContext ctx) {
            super(ctx);
        }

        @Override
        void onCreate() {

            BoxStyle st = this.getStyle();
            st.setBackgroundColor(null);

            this.setLayout(new InnerLinearLayout(LinearLayout.HORIZONTAL));
            this.setStyle(st);

            this.onCreateKeys();
        }

        private void onCreateKeys() {

            final InnerContext ctx = this.context;
            final InnerKeyInfo[] src = ctx.keys;
            final List<InnerSmallKey> tmp = new ArrayList<>();

            for (InnerKeyInfo info : src) {
                InnerSmallKey k = new InnerSmallKey(ctx, info);
                k.onCreate();
                tmp.add(k);
                this.add(k);
            }

            this.keys = tmp.toArray(new InnerSmallKey[0]);
        }

    }

    private static class InnerLED extends CSpace {

        @Override
        protected void onPaintForeground(RenderContext rc) {
            super.onPaintForeground(rc);

            Dimension my_size = this.getSize();
            Point my_pos = this.getPositionAtCanvas();
            final Graphics g = rc.getGraphics();

            if (my_size == null || my_pos == null) {
                return;
            }

            Color color = Color.yellow;
            final int w = my_size.width;
            final int padding = 2;
            final int padding2 = 2 * padding;

            g.setColor(color);
            g.fillOval(my_pos.x + padding, my_pos.y + padding, w - padding2, w - padding2);
        }

    }

    private static class InnerKeyBarLayout implements ILayout, ComponentListener {

        final InnerBigKeyBar mBigKeyBar;
        final InnerSmallKeyBar mSmallKeyBar;

        InnerKeyBarLayout(InnerBigKeyBar big, InnerSmallKeyBar small) {

            this.mBigKeyBar = big;
            this.mSmallKeyBar = small;

            this.setupResizeListener(big.context);
        }

        @Override
        public void onBuildLayoutContainer(LayoutContext lc, BoxContainer parent) {

        }

        public void rebuildLayoutInnerView(LayoutContext lc, BoxContainer parent, Box child, float height_rate) {

            int w, h;
            Dimension p_size = parent.getSize();
            w = p_size.width;
            h = (int) (p_size.height * height_rate);

            child.setSize(new Dimension(w, h));
            child.setWantSize(new Dimension(w, h));
            child.setPosition(new Point());

            LayoutContext lc2 = new LayoutContext(lc);
            lc2.setChild(child);
            lc2.setParent(parent);
            child.rebuildLayout(lc2);
        }

        @Override
        public void onBuildLayoutPost(LayoutContext lc, BoxContainer parent) {
            this.rebuildLayoutInnerView(lc, parent, this.mBigKeyBar, 1);
            this.rebuildLayoutInnerView(lc, parent, this.mSmallKeyBar, 0.6f);
        }

        @Override
        public void onBuildLayoutPre(LayoutContext arg0, BoxContainer arg1) {
        }

        void setupResizeListener(InnerContext ctx) {
            // 监听 scroll-pane 的大小变化
            ctx.scroller.addComponentListener(this);
        }

        void onResize(InnerContext ctx, Dimension size) {
            // 改变 adapter 的大小

            size = new Dimension(size);
            size.width = 1024 * 3;
            size.height -= 50;

            CanvasAdapter ada = ctx.adapter;
            // ada.setSize(size);
            ada.setPreferredSize(size);
        }

        @Override
        public void componentResized(ComponentEvent e) {
            Dimension size = e.getComponent().getSize();
            InnerContext ctx = this.mBigKeyBar.context;
            this.onResize(ctx, size);
        }

        @Override
        public void componentMoved(ComponentEvent e) {
        }

        @Override
        public void componentShown(ComponentEvent e) {
        }

        @Override
        public void componentHidden(ComponentEvent e) {
        }

    }

}
