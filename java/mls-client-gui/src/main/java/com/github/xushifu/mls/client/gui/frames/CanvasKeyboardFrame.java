package com.github.xushifu.mls.client.gui.frames;

import java.awt.BorderLayout;
import java.awt.Dimension;

import javax.swing.JFrame;

import com.bitwormhole.starter4j.swing.FrameRegistration;
import com.bitwormhole.starter4j.swing.Goal;
import com.github.xushifu.mls.client.gui.widgets.CanvasKeyboardView;

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

        CanvasKeyboardView viewSmall = this.createSmallView();
        CanvasKeyboardView viewLarge = this.createBigView();

        viewSmall.setPreferredSize(new Dimension(100, 100));

        this.setLayout(new BorderLayout());
        this.setSize(new Dimension(1024, 768));

        this.add(viewSmall, BorderLayout.NORTH);
        this.add(viewLarge, BorderLayout.CENTER);

    }

    private CanvasKeyboardView createSmallView() {

        CanvasKeyboardView.Builder builder = CanvasKeyboardView.newBuilder();

        return builder.create();
    }

    private CanvasKeyboardView createBigView() {
        CanvasKeyboardView.Builder builder = CanvasKeyboardView.newBuilder();

        return builder.create();
    }

    public static CanvasKeyboardFrame create(Goal goal) {
        CanvasKeyboardFrame f = new CanvasKeyboardFrame();
        f.onCreate();
        return f;
    }

}
