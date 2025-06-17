package com.github.xushifu.mls.client.gui;

import com.bitwormhole.starter4j.application.Module;
import com.bitwormhole.starter4j.swing.SwingApplicationConfig;
import com.bitwormhole.starter4j.swing.SwingApplicationStarter;
import com.github.xushifu.mls.client.gui.frames.LoginFrame;

public final class MLSClientGUI {

    public static void main(String[] args) {
        SwingApplicationConfig cfg = new SwingApplicationConfig();
        cfg.setMainFrameClass(LoginFrame.class);
        cfg.setArguments(args);
        cfg.setModule(module());
        SwingApplicationStarter.run(cfg);
    }

    public static Module module() {
        return ThisModule.module();
    }
}
