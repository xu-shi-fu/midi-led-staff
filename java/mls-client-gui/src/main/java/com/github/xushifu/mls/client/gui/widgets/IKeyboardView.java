package com.github.xushifu.mls.client.gui.widgets;

import javax.swing.JComponent;

import com.bitwormhole.starter4j.swing.canvases.Canvas;
import com.bitwormhole.starter4j.swing.canvases.CanvasAdapter;
import com.github.xushifu.mls.musical.KeyboardAdapter;

public interface IKeyboardView {

    Canvas getCanvas();

    CanvasAdapter getCanvasAdapter();

    KeyboardAdapter getKeyboardAdapter();

    JComponent getComponent();

}
