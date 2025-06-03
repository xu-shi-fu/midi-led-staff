package com.github.xushifu.mls.client;

import javax.swing.SwingUtilities;

import com.github.xushifu.mls.client.gui.LoginFrame;

public final class AppMain {

    public static void main(String[] args) {
        try {
            run();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void run() throws Exception {
        String[] args = {};
        SwingUtilities.invokeAndWait(() -> {
            LoginFrame.show(args);
        });
    }

}
