package com.github.xushifu.mls.client.gui.frames;

import java.awt.BorderLayout;
import java.awt.Dimension;

import javax.swing.JFrame;
import javax.swing.JComponent;

import com.bitwormhole.starter4j.swing.FrameRegistration;
import com.bitwormhole.starter4j.swing.Goal;
import com.github.xushifu.mls.client.gui.widgets.CanvasKeyboardOverview;
import com.github.xushifu.mls.client.gui.widgets.CanvasKeyboardView;
import com.github.xushifu.mls.musical.DefaultKeyboardAdapter;
import com.github.xushifu.mls.musical.KeyboardAdapter;

public class CanvasKeyboardFrame extends JFrame {

    public static FrameRegistration registration() {
        FrameRegistration fr = new FrameRegistration();
        fr.setType(CanvasKeyboardFrame.class);
        fr.setFactory((goal) -> create(goal));
        return fr;
    }

    ////////////////////////////////////////////////////////////////////////////
    /// private

    private CanvasKeyboardFrame() {
    }

    private void onCreate() {

        KeyboardAdapter ka = new DefaultKeyboardAdapter();
        JComponent viewSmall = this.createSmallView(ka);
        CanvasKeyboardView viewLarge = this.createBigView(ka);

        viewSmall.setPreferredSize(new Dimension(100, 100));

        this.setLayout(new BorderLayout());
        this.setSize(new Dimension(1024, 768));

        this.add(viewSmall, BorderLayout.NORTH);
        this.add(viewLarge, BorderLayout.CENTER);

    }

    private CanvasKeyboardOverview createSmallView(KeyboardAdapter ka) {

        CanvasKeyboardOverview.Builder builder = CanvasKeyboardOverview.newBuilder();
        builder.setKeyboard(ka);

        return builder.create();
    }

    private CanvasKeyboardView createBigView(KeyboardAdapter ka) {
        CanvasKeyboardView.Builder builder = CanvasKeyboardView.newBuilder();
        builder.setScrollable(true);
        builder.setKeyboard(ka);

        return builder.create();
    }

    public static CanvasKeyboardFrame create(Goal goal) {
        CanvasKeyboardFrame f = new CanvasKeyboardFrame();
        f.onCreate();
        return f;
    }

}
