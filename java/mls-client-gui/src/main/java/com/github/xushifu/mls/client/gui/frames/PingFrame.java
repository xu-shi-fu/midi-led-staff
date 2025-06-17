package com.github.xushifu.mls.client.gui.frames;

import javax.swing.JFrame;

import com.bitwormhole.starter4j.swing.FrameRegistration;
import com.bitwormhole.starter4j.swing.Goal;
import com.github.xushifu.mls.client.ClientContextHolder;

public class PingFrame extends JFrame {

    private final ClientContextHolder contextHolder;
    private final Goal goal;

    private PingFrame(Goal g) {
        this.contextHolder = ClientContextHolder.getInstance(g.getContext());
        this.goal = g;
    }

    private static PingFrame createFrame(Goal goal) {
        PingFrame f = new PingFrame(goal);
        f.onCreate();
        return f;
    }

    private void onCreate() {
        String title = this.getClass().getName();
        this.setTitle(title);
        this.setSize(600, 360);
    }

    public static FrameRegistration registration() {
        FrameRegistration fr = new FrameRegistration();
        fr.setType(PingFrame.class);
        fr.setFactory((goal) -> createFrame(goal));
        return fr;
    }

}
