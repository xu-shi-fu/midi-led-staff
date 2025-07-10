package com.github.xushifu.mls.client.gui.widgets;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.LayoutManager2;
import java.awt.Rectangle;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;

import javax.swing.BorderFactory;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.Border;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.github.xushifu.mls.client.gui.widgets.Piano12KeysView.BlackKey;
import com.github.xushifu.mls.client.gui.widgets.Piano12KeysView.WhiteKey;
import com.github.xushifu.mls.musical.DefaultKeyboardAdapter;
import com.github.xushifu.mls.musical.Key;
import com.github.xushifu.mls.musical.KeyHolder;
import com.github.xushifu.mls.musical.KeyObserver;
import com.github.xushifu.mls.musical.KeyState;
import com.github.xushifu.mls.musical.KeyboardAdapter;
import com.github.xushifu.mls.musical.Tone;

public class Piano12KeysView extends JPanel implements KeyboardAdapter.Listener {

    private static final Logger logger = LoggerFactory.getLogger(Piano12KeysView.class);

    public static Piano12KeysView create(Key in_c) {
        Piano12KeysView view = new Piano12KeysView();
        view.onCreate(in_c);
        return view;
    }

    public KeyboardAdapter getAdapter() {
        return mAdapter;
    }

    public void setAdapter(KeyboardAdapter a) {
        a = prepareAdapter(a);
        this.mAdapter = a;
        this.onSetAdapter(a);
    }

    ////////////////////////////////////////////////////////////////////////////
    /// private

    private final WhiteKey[] mWhiteKeys;
    private final BlackKey[] mBlackKeys; // 包含 7 个白键占位
    private KeyboardAdapter mAdapter;

    private Piano12KeysView() {
        this.mWhiteKeys = new WhiteKey[7];
        this.mBlackKeys = new BlackKey[12]; // = (7x白键占位) + (5x黑键)
    }

    private KeyboardAdapter prepareAdapter(KeyboardAdapter have) {
        if (have == null) {
            have = new DefaultKeyboardAdapter();
        }
        return have;
    }

    class PianoKey extends JPanel implements KeyboardAdapter.Listener {

        final int index; // 表示在 WhiteKey[] (或 BlackKey[]) 数组中的位置
        final Tone tone;
        final Key key;

        // mutables
        KeyHolder keyHolder;
        KeyboardAdapter adapter;
        KeyObserver observer;

        PianoKey(int idx, Key k) {
            this.index = idx;
            this.tone = k.getTone();
            this.key = k;
        }

        String makeToolTipText(Key k) {
            if (!Key.isAvailable(k)) {
                return "N/A";
            }
            StringBuilder sb = new StringBuilder();
            sb.append(k.getName());
            sb.append("(MIDI:");
            sb.append(k.getMidiNumber());
            sb.append(", ");
            sb.append(k.getFrequency()).append("Hz");
            sb.append(")");
            return sb.toString();
        }

        void onSetAdapter(KeyboardAdapter a) {
            this.adapter = a;
            this.onKeyUpdate(this.key, this.adapter);
        }

        void onKeyUpdate(Key k, KeyboardAdapter ka) {
            if (k == null || ka == null) {
                return;
            }
            int i = k.getIndex();
            KeyHolder holder = ka.getKeyAt(i);
            this.setupObserver(holder);
            this.keyHolder = holder;
            this.setToolTipText(makeToolTipText(k));
        }

        void onKeyStateChange(KeyState ks) {
            Color bg = this.getBgColor(ks);
            if (bg == null) {
                return;
            }
            this.setBackground(bg);
        }

        Color getBgColor(KeyState ks) {
            return Color.gray;
        }

        void onCreate() {
            this.addMouseListener(new MyMouseAdapter(this));
        }

        void setupObserver(KeyHolder kh) {
            KeyObserver obs = new KeyObserver(kh);
            obs.setCallback((kh2) -> {
                Key k = kh2.getKey();
                logger.debug("KeyObserver.callback: key=" + k);
                this.onKeyStateChange(kh2.getState());
            });
            this.observer = obs;
        }

        @Override
        public void onKeyboardUpdate(KeyboardAdapter adapter) {
            KeyObserver.observe(this.observer);
        }

    }

    class MyMouseAdapter extends MouseAdapter {

        final PianoKey mPK;

        MyMouseAdapter(PianoKey pk) {
            this.mPK = pk;
        }

        void updateStatePressed(boolean pressed) {
            KeyHolder holder = this.mPK.keyHolder;
            KeyState state = holder.getState();
            state.setPressed(pressed);
            holder.setState(state);
            Piano12KeysView.this.mAdapter.update(false);
        }

        @Override
        public void mousePressed(MouseEvent e) {
            super.mousePressed(e);
            this.updateStatePressed(true);
        }

        @Override
        public void mouseReleased(MouseEvent e) {
            super.mouseReleased(e);
            this.updateStatePressed(false);
        }
    }

    class WhiteKey extends PianoKey {

        final JLabel mLabel = new JLabel("X#N");

        WhiteKey(int idx, Key k) {
            super(idx, k);
        }

        void onCreate() {
            super.onCreate();
            this.setBackground(Color.white);
            this.setLayout(new BorderLayout());

            Border border = BorderFactory.createLineBorder(Color.black);
            this.setBorder(border);

            this.mLabel.setForeground(Color.gray);
            this.mLabel.setBorder(BorderFactory.createEmptyBorder(20, 0, 20, 0));
            this.mLabel.setText(computeKeyLabel(this.key));

            this.add(this.mLabel, BorderLayout.SOUTH);
        }

        @Override
        Color getBgColor(KeyState ks) {
            if (ks.isAvailable()) {
                if (ks.isPressed()) {
                    return Color.red;
                } else {
                    return Color.white;
                }
            }
            return super.getBgColor(ks);
        }

        String computeKeyLabel(Key k) {
            if (k == null) {
                return "";
            }
            Tone tone = k.getTone();
            if (Tone.C.equals(tone)) {
                return k.getName();
            }
            return "";
        }
    }

    class BlackKey extends PianoKey {

        final WS2812View mLED;

        BlackKey(int idx, Key k) {
            super(idx, k);
            this.mLED = WS2812View.create();
        }

        void onCreate() {
            super.onCreate();
            this.setBackground(Color.black);

            // layout
            this.setLayout(new BorderLayout());
            this.add(this.mLED, BorderLayout.NORTH);

            final int padding = 5;
            this.mLED.setBorder(BorderFactory.createEmptyBorder(padding, padding, padding, padding));

            // border
            Border border = BorderFactory.createLineBorder(Color.black);
            this.setBorder(border);

            if (!this.isBlackKey()) {
                this.setAsWhiteKeyUpper();
            }

            // this.setVisible();
        }

        @Override
        Color getBgColor(KeyState ks) {
            if (!this.isBlackKey()) {
                return null;
            }
            if (ks.isAvailable()) {
                if (ks.isPressed()) {
                    return Color.red;
                } else {
                    return Color.black;
                }
            }
            return super.getBgColor(ks);
        }

        void setAsWhiteKeyUpper() {
            this.setBackground(new Color(0, 0, 0, 0));
            this.setBorder(BorderFactory.createEmptyBorder());
        }

        boolean isBlackKey() {
            return this.tone.isSharp();
        }
    }

    class PianoLayout implements LayoutManager2 {

        PianoLayout() {
        }

        void applyLayout1(Container parent) {
            if (parent instanceof Piano12KeysView) {
                Piano12KeysView p2 = (Piano12KeysView) parent;
                Rectangle rect = p2.getBounds();
                this.applyLayout2(p2, rect.getWidth(), rect.getHeight());
            }
        }

        void applyLayout2(Piano12KeysView parent, double width, double height) {
            this.applyLayoutBK(parent, width, height);
            this.applyLayoutWK(parent, width, height);
        }

        void applyLayoutWK(Piano12KeysView parent, double width, double height) {

            final WhiteKey[] list = parent.mWhiteKeys;
            final double unit_width = width / 7;

            int x, y, w, h;
            x = 0;
            y = 0;
            w = (int) unit_width;
            h = (int) height;

            for (int i = 0; i < list.length; i++) {
                WhiteKey key = list[i];
                x = (int) (i * unit_width);
                key.setBounds(x, y, w, h);
            }
        }

        void applyLayoutBK(Piano12KeysView parent, double width, double height) {

            final BlackKey[] list = parent.mBlackKeys;
            final double unit_width = width / 12;

            int x, y, w, h;
            x = 0;
            y = 0;
            w = (int) unit_width;
            h = (int) (height * 0.6);

            for (int i = 0; i < list.length; i++) {
                BlackKey key = list[i];
                x = (int) (i * unit_width);
                key.setBounds(x, y, w, h);
            }
        }

        @Override
        public void addLayoutComponent(String name, Component comp) {
            // NOP
        }

        @Override
        public void removeLayoutComponent(Component comp) {
            // NOP
        }

        @Override
        public Dimension preferredLayoutSize(Container parent) {
            return parent.getPreferredSize();
        }

        @Override
        public Dimension minimumLayoutSize(Container parent) {
            return parent.getMinimumSize();
        }

        @Override
        public void layoutContainer(Container parent) {
            // NOP
        }

        @Override
        public void addLayoutComponent(Component comp, Object constraints) {
            // NOP
        }

        @Override
        public Dimension maximumLayoutSize(Container target) {
            return target.getMaximumSize();
        }

        @Override
        public float getLayoutAlignmentX(Container target) {
            return 0;
        }

        @Override
        public float getLayoutAlignmentY(Container target) {
            return 0;
        }

        @Override
        public void invalidateLayout(Container target) {
            this.applyLayout1(target);
        }
    }

    static class KeySelector {

        private Key mC;
        private Tone mWant;

        KeySelector setCKey(Key c) {
            this.mC = c;
            return this;
        }

        KeySelector setTone(Tone t) {
            this.mWant = t;
            return this;
        }

        Key select() {
            Tone want = this.mWant;
            Key c = this.mC;
            if (want == null || c == null) {
                return Key.NONE;
            }
            Tone base = c.getTone();
            int pos0 = base.getPosition();
            int pos1 = want.getPosition();
            int diff = pos1 - pos0;
            int num = c.getMidiNumber();
            return Key.getKeyAt(num + diff);
        }
    }

    private void onCreate(Key c) {
        this.setPreferredSize(new Dimension(100, 100));
        this.setLayout(new PianoLayout());
        this.onCreateBlackKeys(c);
        this.onCreateWhiteKeys(c);
    }

    private void onSetAdapter(KeyboardAdapter adapter) {

        BlackKey[] bk_list = this.mBlackKeys;
        WhiteKey[] wk_list = this.mWhiteKeys;

        for (BlackKey key : bk_list) {
            key.onSetAdapter(adapter);
        }

        for (WhiteKey key : wk_list) {
            key.onSetAdapter(adapter);
        }
    }

    private void onCreateBlackKeys(Key c) {
        Tone[] tone_list = {
                Tone.C, Tone.CS,
                Tone.D, Tone.DS,
                Tone.E,
                Tone.F, Tone.FS,
                Tone.G, Tone.GS,
                Tone.A, Tone.AS,
                Tone.B,
        };
        KeySelector ks = new KeySelector();
        ks.setCKey(c);
        for (int i = 0; i < tone_list.length; i++) {
            ks.setTone(tone_list[i]);
            BlackKey black = new BlackKey(i, ks.select());
            black.onCreate();
            this.add(black);
            this.mBlackKeys[i] = black;
        }
    }

    private void onCreateWhiteKeys(Key c) {
        Tone[] tone_list = {
                Tone.C, Tone.D, Tone.E,
                Tone.F, Tone.G, Tone.A, Tone.B,
        };
        KeySelector ks = new KeySelector();
        ks.setCKey(c);
        for (int i = 0; i < tone_list.length; i++) {
            ks.setTone(tone_list[i]);
            WhiteKey white = new WhiteKey(i, ks.select());
            white.onCreate();
            this.add(white);
            this.mWhiteKeys[i] = white;
        }
    }

    @Override
    public void onKeyboardUpdate(KeyboardAdapter adapter) {

        final BlackKey[] list1 = this.mBlackKeys;
        final WhiteKey[] list2 = this.mWhiteKeys;

        for (BlackKey bk : list1) {
            bk.onKeyboardUpdate(adapter);
        }

        for (WhiteKey wk : list2) {
            wk.onKeyboardUpdate(adapter);
        }
    }

}
