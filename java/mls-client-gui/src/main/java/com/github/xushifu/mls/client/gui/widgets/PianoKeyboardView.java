package com.github.xushifu.mls.client.gui.widgets;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;

import javax.swing.JPanel;
import javax.swing.JScrollPane;

import com.github.xushifu.mls.musical.DefaultKeyboardAdapter;
import com.github.xushifu.mls.musical.Key;
import com.github.xushifu.mls.musical.KeyboardAdapter;
import com.github.xushifu.mls.musical.KeyboardObserver;
import com.github.xushifu.mls.musical.KeyboardRange;

public class PianoKeyboardView extends JPanel {

    public static PianoKeyboardView create() {
        PianoKeyboardView view = new PianoKeyboardView();
        view.onCreate();
        return view;
    }

    public KeyboardAdapter getAdapter() {
        return mAdapter;
    }

    public void setAdapter(KeyboardAdapter adapterNewer) {

        final KeyboardAdapter.Listener l = this.mInnerContainer;
        final KeyboardAdapter adapterOlder = this.mAdapter;
        adapterNewer = prepareAdapter(adapterNewer);

        if (adapterOlder != null) {
            adapterOlder.removeListener(l);
        }
        if (adapterNewer != null) {
            adapterNewer.addListener(l);
        }

        this.mAdapter = adapterNewer;
        this.mInnerContainer.onSetAdapter(adapterNewer);
    }

    ////////////////////////////////////////////////////////////////////////////
    /// private

    private Inner128KeysContainer mInnerContainer;
    private KeyboardAdapter mAdapter;

    private PianoKeyboardView() {
        this.mAdapter = prepareAdapter(null);
    }

    private static KeyboardAdapter prepareAdapter(KeyboardAdapter have) {
        if (have == null) {
            have = new DefaultKeyboardAdapter();
        }
        return have;
    }

    private class Inner128KeysContainer extends JPanel implements KeyboardAdapter.Listener {

        private final Piano12KeysView[] mGroups;
        private KeyboardObserver observer;

        public Inner128KeysContainer() {
            this.mGroups = new Piano12KeysView[11]; // 11 组, 132按键 (128有效按键)
        }

        private void onCreate() {

            int count_groups = this.mGroups.length;
            Color bgColor = Color.BLACK;

            this.setPreferredSize(new Dimension(100, 100));
            this.setLayout(new GridLayout(1, count_groups));

            Piano12KeysView[] groups = mGroups;
            for (int i = 0; i < groups.length; i++) {
                Key ck = getCKeyByGroupIndex(i);
                Piano12KeysView group = Piano12KeysView.create(ck);
                groups[i] = group;
                group.setBackground(bgColor);
                this.add(group);
            }

            this.setBackground(bgColor);
        }

        void setupObserver(KeyboardAdapter ada) {
            KeyboardObserver obs = new KeyboardObserver(ada);
            obs.setCallback((x) -> {
            });
            this.observer = obs;
        }

        Key getCKeyByGroupIndex(int index) {
            return Key.getKeyAt(index * 12);
        }

        void onScrollPaneResize(Dimension sp_size) {
            if (sp_size == null) {
                sp_size = PianoKeyboardView.this.getSize();
            }
            int w = this.computeInnerWidth(sp_size);
            int h = (int) sp_size.getHeight();
            // this.setSize(w, h);
            this.setPreferredSize(new Dimension(w, h));
        }

        int computeInnerWidth(Dimension sp_size) {
            try {
                KeyboardAdapter ada = PianoKeyboardView.this.mAdapter;
                KeyboardRange range = ada.getViewportRange();
                int viewport_width = sp_size.width;
                int viewport_count = range.getCount();
                final int total_count = 128;
                return (viewport_width * total_count) / viewport_count;
            } catch (Exception e) {
                return 100;
            }
        }

        void onSetAdapter(KeyboardAdapter a) {
            a = prepareAdapter(a);
            Piano12KeysView[] groups = mGroups;
            for (Piano12KeysView g : groups) {
                g.setAdapter(a);
            }
            this.setupObserver(a);
        }

        @Override
        public void onKeyboardUpdate(KeyboardAdapter adapter) {
            // dispatch to groups
            Piano12KeysView[] list = this.mGroups;
            for (Piano12KeysView v : list) {
                v.onKeyboardUpdate(adapter);
            }
            KeyboardObserver.observe(this.observer);
        }
    }

    private Inner128KeysContainer createInnerContainer(KeyboardAdapter adapter) {
        Inner128KeysContainer i = new Inner128KeysContainer();
        i.onCreate();
        i.onSetAdapter(adapter);
        return i;
    }

    class MyScrollPaneListener implements ComponentListener {

        @Override
        public void componentResized(ComponentEvent e) {
            Component com = e.getComponent();
            Dimension size = com.getSize();
            mInnerContainer.onScrollPaneResize(size);
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

    private void onCreate() {

        KeyboardAdapter adapter = this.mAdapter;
        adapter = prepareAdapter(adapter);

        Inner128KeysContainer inner = createInnerContainer(adapter);
        JScrollPane sp = new JScrollPane(inner);

        this.mInnerContainer = inner;

        sp.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_NEVER);
        sp.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
        sp.addComponentListener(new MyScrollPaneListener());
        // sp.add(inner);
        sp.setPreferredSize(new Dimension(600, 240));

        this.setLayout(new BorderLayout());
        this.add(sp, BorderLayout.CENTER);
        this.setAdapter(adapter);
    }

}
