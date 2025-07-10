package com.github.xushifu.mls.client.gui.frames;

import javax.swing.JButton;
import javax.swing.JFrame;

import java.awt.FlowLayout;
import java.awt.event.ActionListener;

import com.bitwormhole.starter4j.application.ApplicationContext;
import com.bitwormhole.starter4j.swing.FrameManager;
import com.bitwormhole.starter4j.swing.FrameRegistration;
import com.bitwormhole.starter4j.swing.Goal;
import com.github.xushifu.mls.client.ClientContextHolder;
import com.github.xushifu.mls.client.gui.SwingClientContext;

public class HomeFrame extends JFrame {

    private final ClientContextHolder contextHolder;
    private final Goal goal;

    private HomeFrame(Goal g) {
        this.goal = g;
        this.contextHolder = ClientContextHolder.getInstance(g.getContext());
    }

    private static HomeFrame createFrame(Goal g) {
        HomeFrame f = new HomeFrame(g);
        f.onCreate();
        return f;
    }

    private void onCreate() {

        String title = this.getClass().getName();
        FlowLayout layout = new FlowLayout();

        this.setTitle(title);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setSize(640, 480);
        this.setLayout(layout);

        this.addMenuItem("Ping", (ae) -> onClickMenuItemOpenFrame(PingFrame.class));
        this.addMenuItem("LED State Monitor", (ae) -> onClickMenuItemOpenFrame(LedMonitorFrame.class));
        this.addMenuItem("Piano Frame", (ae) -> onClickMenuItemOpenFrame(PianoFrame.class));
        this.addMenuItem("Canvas Keyboard Frame", (ae) -> onClickMenuItemOpenFrame(CanvasKeyboardFrame.class));

    }

    private SwingClientContext getSwingClientContext() {
        return SwingClientContext.getInstance(this.contextHolder);
    }

    private void onClickMenuItemOpenFrame(Class<? extends JFrame> fc) {
        ApplicationContext ac = this.goal.getContext();
        SwingClientContext scc = this.getSwingClientContext();
        FrameManager fm = scc.getFrameManager();
        Goal goal = new Goal();

        goal.setContext(ac);
        goal.setFrameClass(fc);
        fm.show(goal);
    }

    private void onClickMenuItemPing() {
    }

    private void onClickMenuItemLedStateMonitor() {
    }

    private void addMenuItem(String label, ActionListener l) {
        JButton btn = new JButton(label);
        btn.addActionListener(l);
        this.add(btn);
    }

    public static FrameRegistration registration() {
        FrameRegistration fr = new FrameRegistration();
        fr.setType(HomeFrame.class);
        fr.setFactory((goal) -> createFrame(goal));
        return fr;
    }

}
