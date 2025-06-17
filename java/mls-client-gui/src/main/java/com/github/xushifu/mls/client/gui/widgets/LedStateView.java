package com.github.xushifu.mls.client.gui.widgets;

import java.awt.BorderLayout;
import java.awt.Color;

import javax.swing.JButton;
import javax.swing.JColorChooser;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class LedStateView extends JPanel {

    private final JLabel labelRx = new JLabel("Rx");
    private final JButton labelMx = new JButton("LED");
    private final JLabel labelTx = new JLabel("Tx");

    private final Data data;
    private boolean ready;

    public LedStateView() {
        this.data = new Data();
        this.onCreate();
    }

    public static class Data {
        public int index;
        public Color colorRx;
        public Color colorTx;
        public Color colorMx;
    }

    private void onCreate() {
        this.onCreateLayout();

        labelRx.setOpaque(true);
        labelMx.setOpaque(true);
        labelTx.setOpaque(true);

        labelRx.setBackground(Color.red);
        labelMx.setBackground(Color.green);
        labelTx.setBackground(Color.blue);

        labelRx.setForeground(Color.white);
        labelMx.setForeground(Color.white);
        labelTx.setForeground(Color.white);

        labelMx.addActionListener((ae) -> onClickMx());

        this.ready = true;
    }

    private void onCreateLayout() {
        BorderLayout layout = new BorderLayout();
        this.setLayout(layout);
        this.add(labelRx, BorderLayout.NORTH);
        this.add(labelMx, BorderLayout.CENTER);
        this.add(labelTx, BorderLayout.SOUTH);
    }

    private void onClickMx() {

        Color color1 = data.colorMx;
        String title = "Choose LED Color";
        Color color2 = JColorChooser.showDialog(this, title, color1);

        if (color2 == null) {
            return;
        }

        data.colorMx = color2;
        data.colorTx = color2;

        this.updateUI();
    }

    public void updateUI() {
        if (this.ready) {
            this.labelRx.setBackground(data.colorRx);
            this.labelMx.setBackground(data.colorMx);
            this.labelTx.setBackground(data.colorTx);
            this.labelMx.setText("LED-" + data.index);
        }
        super.updateUI();
    }

    public void push() {
    }

    public void pull() {
        this.updateUI();
    }

    public Data getData() {
        return data;
    }

}
