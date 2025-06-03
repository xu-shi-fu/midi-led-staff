package com.github.xushifu.mls.client.gui;

import javax.swing.JFrame;

public class LoginFrame extends JFrame {

    public static LoginFrame show(String[] args) {
        LoginFrame frame = new LoginFrame();
        frame.setTitle(frame.getClass().getSimpleName());
        frame.setSize(640, 480);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        return frame;
    }

}
