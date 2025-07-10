package com.github.xushifu.mls.client.gui.frames;

import java.awt.BorderLayout;

import javax.swing.JFrame;

import com.bitwormhole.starter4j.swing.FrameRegistration;
import com.bitwormhole.starter4j.swing.Goal;
import com.github.xushifu.mls.client.gui.widgets.PianoKeyboardView;

public class PianoFrame extends JFrame {

    public static FrameRegistration registration() {
        FrameRegistration fr = new FrameRegistration();
        fr.setType(PianoFrame.class);
        fr.setFactory((goal) -> createFrame(goal));
        return fr;
    }

    ////////////////////////////////////////////////////////////////////////////
    /// private

    private PianoFrame(Goal goal) {
    }

    private static PianoFrame createFrame(Goal goal) {
        PianoFrame f = new PianoFrame(goal);
        f.setTitle(f.getClass().getSimpleName());
        f.setSize(480, 360);
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.onCreate();
        return f;
    }

    private void onCreate() {
        this.setLayout(new BorderLayout());
        PianoKeyboardView view = PianoKeyboardView.create();
        this.add(view, BorderLayout.SOUTH);
    }

}
