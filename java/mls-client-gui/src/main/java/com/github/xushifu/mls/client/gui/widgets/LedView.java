package com.github.xushifu.mls.client.gui.widgets;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Rectangle;

import javax.swing.JPanel;

public class LedView extends JPanel {

    public LedView() {
    }

    protected void onCreate() {
        this.setBackground(Color.YELLOW);
        this.setForeground(Color.BLUE);
    }

    @Override
    public void paint(Graphics g) {

        Color c0 = Color.black; // draw border
        Color c1 = this.getBackground(); // fill rect
        Color c2 = this.getForeground(); // fill oval

        Rectangle rect = this.getBounds();
        final int x1, y1, w1, h1; // rect
        x1 = rect.x;
        y1 = rect.y;
        w1 = rect.width;
        h1 = rect.height;

        int cx, cy, r;
        cx = x1 + (w1 / 2);
        cy = y1 + (h1 / 2);
        r = (int) (Math.min(w1, h1) * 0.35);

        final int x2, y2, w2, h2; // oval
        x2 = cx - r;
        y2 = cy - r;
        w2 = h2 = r * 2;

        // rect
        g.setColor(c1);
        g.fillRect(x1, y1, w1, h1);

        // oval
        g.setColor(c2);
        g.fillOval(x2, y2, w2, h2);

        // border
        g.setColor(c0);
        g.drawRect(x1, y1, w1, h1);
        g.drawOval(x2, y2, w2, h2);
    }

}
