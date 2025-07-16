package com.github.xushifu.mls.client.gui.widgets;

import java.awt.Color;
import java.awt.Font;

import com.bitwormhole.starter4j.swing.canvases.BoxStyle;
import com.bitwormhole.starter4j.swing.canvases.LineStyle;

public class CanvasKeyboardTheme {

    ////////////////////////////////////////////////////////////////////////////
    /// public

    public CanvasKeyboardTheme() {
        this.initAsDefault();
    }

    public CanvasKeyboardTheme(CanvasKeyboardTheme src) {

        if (src == null) {
            this.initAsDefault();
            return;
        }

        this.blackKeyDisabled = src.blackKeyDisabled;
        this.blackKeyPressed = src.blackKeyPressed;
        this.blackKeyNormal = src.blackKeyNormal;
        this.blackKeyHover = src.blackKeyHover;

        this.whiteKeyDisabled = src.whiteKeyDisabled;
        this.whiteKeyPressed = src.whiteKeyPressed;
        this.whiteKeyNormal = src.whiteKeyNormal;
        this.whiteKeyHover = src.whiteKeyHover;

        this.unavailable = src.unavailable;
    }

    public static class Selector {
        public boolean sharp; // 黑白键
        public boolean pressed; // 是否 note-on
        public boolean enabled; // 是否激活
        public boolean available; // 是否可用
        public boolean hover;
    }

    public BoxStyle selectStyle(Selector sel) {

        if (sel == null) {
            sel = new Selector();
        }

        if (!sel.available) {
            return this.unavailable;
        }

        if (sel.enabled) {
            if (sel.pressed) {
                // return pressed
                return sel.sharp ? this.blackKeyPressed : this.whiteKeyPressed;
            } else if (sel.hover) {
                // return hover
                return sel.sharp ? this.blackKeyHover : this.whiteKeyHover;
            } else {
                // return normal
                return sel.sharp ? this.blackKeyNormal : this.whiteKeyNormal;
            }
        }

        // return disabled
        return sel.sharp ? this.blackKeyDisabled : this.whiteKeyDisabled;
    }

    public BoxStyle getWhiteKeyNormal() {
        return whiteKeyNormal;
    }

    public void setWhiteKeyNormal(BoxStyle whiteKeyNormal) {
        this.whiteKeyNormal = whiteKeyNormal;
    }

    public BoxStyle getWhiteKeyDisabled() {
        return whiteKeyDisabled;
    }

    public void setWhiteKeyDisabled(BoxStyle whiteKeyDisabled) {
        this.whiteKeyDisabled = whiteKeyDisabled;
    }

    public BoxStyle getWhiteKeyPressed() {
        return whiteKeyPressed;
    }

    public void setWhiteKeyPressed(BoxStyle whiteKeyPressed) {
        this.whiteKeyPressed = whiteKeyPressed;
    }

    public BoxStyle getBlackKeyNormal() {
        return blackKeyNormal;
    }

    public void setBlackKeyNormal(BoxStyle blackKeyNormal) {
        this.blackKeyNormal = blackKeyNormal;
    }

    public BoxStyle getBlackKeyDisabled() {
        return blackKeyDisabled;
    }

    public void setBlackKeyDisabled(BoxStyle blackKeyDisabled) {
        this.blackKeyDisabled = blackKeyDisabled;
    }

    public BoxStyle getBlackKeyPressed() {
        return blackKeyPressed;
    }

    public void setBlackKeyPressed(BoxStyle blackKeyPressed) {
        this.blackKeyPressed = blackKeyPressed;
    }

    public BoxStyle getUnavailable() {
        return unavailable;
    }

    public void setUnavailable(BoxStyle unavailable) {
        this.unavailable = unavailable;
    }

    public BoxStyle getWhiteKeyHover() {
        return whiteKeyHover;
    }

    public void setWhiteKeyHover(BoxStyle whiteKeyHover) {
        this.whiteKeyHover = whiteKeyHover;
    }

    public BoxStyle getBlackKeyHover() {
        return blackKeyHover;
    }

    public void setBlackKeyHover(BoxStyle blackKeyHover) {
        this.blackKeyHover = blackKeyHover;
    }

    ////////////////////////////////////////////////////////////////////////////
    /// private

    private BoxStyle whiteKeyNormal;
    private BoxStyle whiteKeyDisabled;
    private BoxStyle whiteKeyPressed;
    private BoxStyle whiteKeyHover;

    private BoxStyle blackKeyNormal;
    private BoxStyle blackKeyDisabled;
    private BoxStyle blackKeyPressed;
    private BoxStyle blackKeyHover;

    private BoxStyle unavailable;

    private static class MyStyleFactory {

        BoxStyle createStyleBase() {
            BoxStyle style = new BoxStyle();

            style.setBorderColor(Color.BLACK);
            style.setBorderStyle(LineStyle.SOLID);
            style.setBorderWidth(1);
            style.setFont(new Font("Canvas-Keyboard", Font.PLAIN, 10));

            return style;
        }

        BoxStyle createStyleForUnavailable() {
            BoxStyle style = this.createStyleBase();
            style.setBackgroundColor(new Color(30, 30, 30));
            return style;
        }

        BoxStyle createStyleForBlackDisabled() {
            BoxStyle style = this.createStyleBase();
            style.setBackgroundColor(Color.GRAY);
            return style;
        }

        BoxStyle createStyleForBlackNormal() {
            BoxStyle style = this.createStyleBase();
            style.setBackgroundColor(Color.BLACK);
            return style;
        }

        BoxStyle createStyleForBlackPressed() {
            BoxStyle style = this.createStyleBase();
            style.setBackgroundColor(new Color(150, 100, 50));
            return style;
        }

        BoxStyle createStyleForWhiteDisabled() {
            BoxStyle style = this.createStyleBase();
            style.setBackgroundColor(Color.GRAY);
            return style;
        }

        BoxStyle createStyleForWhiteNormal() {
            BoxStyle style = this.createStyleBase();
            style.setBackgroundColor(new Color(230, 230, 230));
            // style.setBackgroundColor(Color.WHITE);
            return style;
        }

        BoxStyle createStyleForWhitePressed() {
            BoxStyle style = this.createStyleBase();
            style.setBackgroundColor(new Color(200, 150, 100));
            return style;
        }

        BoxStyle createStyleForWhiteHover() {
            BoxStyle style = this.createStyleBase();
            // style.setBackgroundColor(new Color(240, 240, 240));
            style.setBackgroundColor(Color.WHITE);
            style.setBorderWidth(3);
            return style;
        }

        BoxStyle createStyleForBlackHover() {
            BoxStyle style = this.createStyleBase();
            style.setBackgroundColor(new Color(50, 50, 50));
            style.setBorderWidth(3);
            return style;
        }

    }

    private void initAsDefault() {
        MyStyleFactory f = new MyStyleFactory();

        this.blackKeyNormal = f.createStyleForBlackNormal();
        this.blackKeyPressed = f.createStyleForBlackPressed();
        this.blackKeyDisabled = f.createStyleForBlackDisabled();
        this.blackKeyHover = f.createStyleForBlackHover();

        this.whiteKeyNormal = f.createStyleForWhiteNormal();
        this.whiteKeyPressed = f.createStyleForWhitePressed();
        this.whiteKeyDisabled = f.createStyleForWhiteDisabled();
        this.whiteKeyHover = f.createStyleForWhiteHover();

        this.unavailable = f.createStyleForUnavailable();
    }

}
