package com.github.xushifu.mls.client.gui.widgets;

import java.awt.BorderLayout;
import java.awt.Color;

import javax.swing.JButton;
import javax.swing.JColorChooser;
import javax.swing.JLabel;
import javax.swing.JPanel;

import com.github.xushifu.mls.client.core.leds.LEDState;
import com.github.xushifu.mls.client.gui.utils.Colors;

public class LedStateView extends JPanel {

    private final JLabel labelRx = new JLabel("Rx");
    private final JButton labelMx = new JButton("LED");
    private final JLabel labelTx = new JLabel("Tx");

    private static final LEDState theDefaultState = new LEDState();
    private final MyStateWrapper state = new MyStateWrapper();

    private boolean ready;

    public LedStateView() {
        this.onCreate();
    }

    private static final class MyStateWrapper {

        private LEDState target;

        private MyStateWrapper() {
            this.target = theDefaultState;
        }

        void setTarget(LEDState s) {
            if (s == null) {
                s = theDefaultState;
            }
            this.target = s;
        }

        LEDState getTarget() {
            LEDState t = this.target;
            if (t == null) {
                t = theDefaultState;
            }
            return t;
        }

        Color getRx() {
            return Colors.toAWT(target.getRx());
        }

        Color getMx() {
            return Colors.toAWT(target.getMx());
        }

        Color getTx() {
            return Colors.toAWT(target.getTx());
        }

        void setRx(Color c) {
            this.target.setRx(Colors.toARGB(c));
        }

        void setMx(Color c) {
            this.target.setMx(Colors.toARGB(c));
        }

        void setTx(Color c) {
            this.target.setTx(Colors.toARGB(c));
        }

        int getIndex() {
            return this.target.getIndex();
        }

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

        final MyStateWrapper sw = this.state;

        int idx = sw.getIndex();
        Color color1 = sw.getMx();
        String title = "Choose LED [" + idx + "] Color";
        Color color2 = JColorChooser.showDialog(this, title, color1);

        if (color2 == null) {
            return;
        }

        sw.setMx(color2);
        sw.setTx(color2);

        this.updateUI();
    }

    public void updateUI() {
        if (this.ready) {
            final MyStateWrapper sw = this.state;
            this.labelRx.setBackground(sw.getRx());
            this.labelMx.setBackground(sw.getMx());
            this.labelTx.setBackground(sw.getTx());
            this.labelMx.setText("LED-" + sw.getIndex());
        }
        super.updateUI();
    }

    public void push() {
    }

    public void pull() {
        this.updateUI();
    }

    public LEDState getState() {
        return this.state.getTarget();
    }

    public void setState(LEDState state) {
        this.state.setTarget(state);
    }

}
