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
import com.bitwormhole.starter4j.swing.canvases.ILayout;
import com.bitwormhole.starter4j.swing.canvases.LayoutContext;
import com.bitwormhole.starter4j.swing.canvases.LineStyle;
import com.bitwormhole.starter4j.swing.canvases.MouseEventContext;
import com.bitwormhole.starter4j.swing.canvases.RenderContext;
import com.bitwormhole.starter4j.swing.canvases.MouseEventContext.MouseEvent;
import com.bitwormhole.starter4j.swing.layouts.LinearLayout;
import com.github.xushifu.mls.client.gui.utils.Colors;
import com.github.xushifu.mls.musical.DefaultKeyboardAdapter;
import com.github.xushifu.mls.musical.EmptyKeyHolder;
import com.github.xushifu.mls.musical.Key;
import com.github.xushifu.mls.musical.KeyHolder;
import com.github.xushifu.mls.musical.KeyState;
import com.github.xushifu.mls.musical.KeyboardAdapter;
import com.github.xushifu.mls.musical.KeyboardAdapter.Listener;
import com.github.xushifu.mls.musical.KeyboardRange;
import com.github.xushifu.mls.musical.Tone;
import com.github.xushifu.mls.network.mlscp.ARGB;

public class CanvasKeyboardView extends JPanel {

    static final Logger logger = LoggerFactory.getLogger(CanvasKeyboardView.class);

    public static Builder newBuilder() {
        return new Builder();
    }

    public static class Builder {

        private boolean scrollable;
        private KeyboardAdapter keyboard;
        private CanvasKeyboardTheme theme;

        public Builder() {
        }

        public boolean isScrollable() {
            return scrollable;
        }

        public void setScrollable(boolean scrollable) {
            this.scrollable = scrollable;
        }

        public CanvasKeyboardView create() {

            if (this.keyboard == null) {
                this.keyboard = new DefaultKeyboardAdapter();
            }

            if (this.theme == null) {
                this.theme = new CanvasKeyboardTheme();
            }

            CanvasKeyboardView view = new CanvasKeyboardView(this);
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

    public double getScale() {
        return scale;
    }

    public void setScale(double scale) {
        this.scale = scale;
    }

    ////////////////////////////////////////////////////////////////////////////
    /// private

    private double scale; // [0.01,1]; 1 = 显示 100% 全部按键; <1, 表示放大

    private final InnerContext mContext;

    private CanvasKeyboardView(Builder b) {

        InnerContext ctx = new InnerContext();
        ctx.scrollable = b.scrollable;
        ctx.keyboard = b.keyboard;
        ctx.theme = b.theme;

        this.scale = 1;
        this.mContext = ctx;
    }

    private void onCreate() {

        // mAdapter.setPreferredSize(new Dimension(1024, 100));

        this.onCreateKeys();
        this.onCreateLayout();
        this.onCreateSmallWhiteKeyStyle();
        this.setupKeyboardAdapterListener();

        logger.info(this + ".onCreate() : done");
    }

    private void onCreateSmallWhiteKeyStyle() {
        BoxStyle st = new BoxStyle();
        st.setBackgroundColor(null);
        st.setForegroundColor(null);
        st.setBorderStyle(LineStyle.NONE);
        st.setBorderColor(null);
        this.mContext.smallWhiteKeyStyle = st;
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
        if (ctx.scrollable) {
            ctx.scroller.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
            ctx.scroller.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_NEVER);
        } else {
            ctx.scroller.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
            ctx.scroller.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_NEVER);
        }

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
            info.initWith(ctx.keyboard);
            all[i] = info;
        }
    }

    private void setupKeyboardAdapterListener() {
        MyKeyboardAdapterListener li = new MyKeyboardAdapterListener();
        this.mContext.keyboard.addListener(li);
    }

    private class MyKeyboardAdapterListener implements Listener {

        @Override
        public void onKeyboardUpdate(KeyboardAdapter adapter) {
            InnerContext ctx = CanvasKeyboardView.this.mContext;
            ctx.adapter.repaint();
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

        BoxStyle smallWhiteKeyStyle;
        CanvasKeyboardTheme theme;
        InnerSmallKeyBar smallKeyBar;
        InnerBigKeyBar bigKeyBar;
        boolean scrollable;
        KeyboardAdapter keyboard;

        InnerContext() {

            CanvasAdapter ada = new CanvasAdapter();

            this.keys = new InnerKeyInfo[12 * 11];
            this.canvas = ada.getCanvas();
            this.adapter = ada;
            this.scroller = new JScrollPane();
        }

        @Override
        public int hashCode() {
            nop(this.bigKeyBar);
            nop(this.smallKeyBar);
            return super.hashCode();
        }

    }

    private static void nop(Object o) {
    }

    private static class InnerView extends CGroup {

        // InnerView 是好几个内部视图的超类

        protected final InnerContext context;

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

            this.setWeight(1);

            int idx = this.info.index;
            CanvasKeyboardTheme.Selector sel = this.info.styleSelector;
            sel.available = ((0 <= idx) && (idx < 128));
            sel.sharp = this.isBlackKey();
        }

        @Override
        public BoxStyle getStyle() {

            // select style
            CanvasKeyboardTheme.Selector sel = this.info.styleSelector;
            CanvasKeyboardTheme theme = this.context.theme;

            // sel.available = false;
            // sel.sharp = false;
            sel.enabled = this.isThisKeyEnabled();
            sel.pressed = this.isThisKeyPressed();
            sel.hover = this.isThisKeyHover();

            return theme.selectStyle(sel);
        }

        boolean isThisKeyPressed() {
            KeyState state = this.info.keyHolder.getState();
            return state.isPressed();
        }

        boolean isThisKeyHover() {
            Box hover = this.context.canvas.getHover();
            return this.equals(hover);
        }

        boolean isThisKeyEnabled() {
            KeyboardAdapter kb = this.context.keyboard;
            KeyboardRange range = kb.getEnabledRange();
            int idx = this.info.index;
            int i1 = range.getOffset();
            int i2 = i1 + range.getCount();
            return (i1 <= idx) && (idx < i2);
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
                this.setCurrentHover(this);
                mec.setCancelled(true);
                this.context.adapter.repaint();

            } else if (MouseEvent.PRESSED.equals(evt)) {
                this.setKeyPressed(true);
                mec.setCancelled(true);

            } else if (MouseEvent.RELEASED.equals(evt)) {
                this.setKeyPressed(false);
                mec.setCancelled(true);
            }
        }

        void setKeyPressed(boolean pressed) {
            KeyHolder kh = this.info.keyHolder;
            KeyState state = kh.getState();
            state.setPressed(pressed);
            kh.setState(state);
            this.context.keyboard.update(false);
        }

        void setCurrentHover(Box target) {
            this.context.canvas.setHover(target);
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
            BoxStyle my_style = this.getStyle();

            if (isCKey(key)) {
                name = key.getName();
            }

            space.setWeight(90);
            space.setWantSize(null);

            label.setText(name);
            label.setWeight(10);
            label.setWantSize(null);
            label.getStyle().setBackgroundColor(null);
            label.getStyle().setFont(my_style.getFont());

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
        final CanvasKeyboardTheme.Selector styleSelector;

        KeyHolder keyHolder;

        InnerKeyInfo(int idx) {

            Key k = Key.getKeyAt(idx);

            this.index = idx;
            this.key = k;
            this.tone = k.getTone();
            this.styleSelector = new CanvasKeyboardTheme.Selector();
        }

        void initWith(KeyboardAdapter ka) {

            KeyHolder kh = ka.getKeyAt(this.index);
            if (kh == null) {
                kh = new EmptyKeyHolder();
            }
            this.keyHolder = kh;

            // nop(this.keyHolder);
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

            nop(this.keys);
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

            nop(this.mLED);
        }

        void onCreateLED() {

            InnerLED led = new InnerLED(this.context, this.info);
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
        }

        @Override
        public BoxStyle getStyle() {
            if (this.isSmallWhiteKey()) {
                return this.context.smallWhiteKeyStyle;
            }
            return super.getStyle();
        }

        boolean isSmallWhiteKey() {
            boolean sharp = this.info.tone.isSharp();
            return !sharp;
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

            nop(this.keys);
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

    private static class InnerLED extends InnerView {

        final InnerKeyInfo info;

        InnerLED(InnerContext ctx, InnerKeyInfo ki) {
            super(ctx);
            this.info = ki;
        }

        @Override
        protected void onPaintBackground(RenderContext rc) {
            // super.onPaintBackground(rc);
        }

        @Override
        protected void onPaintForeground(RenderContext rc) {

            // super.onPaintForeground(rc);

            Dimension my_size = this.getSize();
            Point my_pos = this.getPositionAtCanvas();
            final Graphics g = rc.getGraphics();

            if (my_size == null || my_pos == null) {
                return;
            }

            Color color = this.getLedColor();
            final int w = my_size.width;
            final int padding = 2;
            final int padding2 = 2 * padding;

            g.setColor(color);
            g.fillOval(my_pos.x + padding, my_pos.y + padding, w - padding2, w - padding2);
        }

        Color getLedColor() {
            KeyState ks = this.info.keyHolder.getState();
            // ks = null;
            if (ks == null) {
                return Color.yellow;
            }
            ARGB argb = Colors.toARGB(ks.getColor());
            return Colors.toColor(argb);
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
            size = this.computeCanvasSize(ctx, size, ctx.scrollable);
            CanvasAdapter ada = ctx.adapter;
            ada.setPreferredSize(size);
        }

        Dimension computeCanvasSize(InnerContext ctx, Dimension size, boolean scrollable) {
            int w, h;
            w = size.width;
            h = size.height;
            if (scrollable) {
                // todo ...
                KeyboardRange range = ctx.keyboard.getViewportRange();
                int count = range.getCount();
                int total = ctx.keys.length;
                count = (count > 0) ? count : 1;
                w = (total * size.width) / count;
            }
            return new Dimension(w, h);
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
