package com.github.xushifu.mls.client.gui.widgets;

import java.awt.Color;

import javax.swing.JColorChooser;

import com.bitwormhole.starter4j.swing.canvases.CanvasAdapter;
import com.github.xushifu.mls.client.gui.utils.Colors;
import com.github.xushifu.mls.musical.Key;
import com.github.xushifu.mls.musical.KeyHolder;
import com.github.xushifu.mls.musical.KeyState;
import com.github.xushifu.mls.musical.KeyboardAdapter;
import com.github.xushifu.mls.musical.KeyboardEvent;
import com.github.xushifu.mls.musical.LightColor;
import com.github.xushifu.mls.musical.KeyboardEvent.EventType;

public class CanvasLedColorSelector extends CanvasKeyboardWrapper {

    public static CanvasLedColorSelector create(IKeyboardView inner) {
        CanvasLedColorSelector inst = new CanvasLedColorSelector(inner);
        inst.tryOnCreate();
        return inst;
    }

    ////////////////////////////////////////////////////////////////////////////
    /// private

    private CanvasLedColorSelector(IKeyboardView in) {
        super(in);
    }

    @Override
    protected void onCreate() {
        super.onCreate();
        this.onCreateSetupListener();
    }

    private void onCreateSetupListener() {
        KeyboardAdapter ka = this.getKeyboardAdapter();
        ka.addListener((evt) -> {
            EventType et = evt.getType();
            if (et == null) {
            } else if (et.equals(EventType.LED_PRESSED)) {
                this.onLEDPressed(evt);
            } else if (et.equals(EventType.LED_RELEASED)) {
                this.onLEDReleased(evt);
            }
        });
    }

    private void showColorDialog(KeyboardEvent ke) {

        KeyboardAdapter ka = ke.getAdapter();
        Key key = ke.getKey();
        KeyHolder key_holder = ka.getKeyAt(key.getIndex());
        KeyState state = key_holder.getState();
        LightColor c1 = state.getLightColor();
        Color color1 = Colors.toAWT(c1);
        String title = "select key color";
        CanvasAdapter ca = this.getCanvasAdapter();

        Color color2 = JColorChooser.showDialog(ca, title, color1);
        if (color2 == null) {
            return;
        }

        state.setColor(Colors.toLight(color2));
        key_holder.setState(state);
    }

    private void onLEDPressed(KeyboardEvent ke) {
    }

    private void onLEDReleased(KeyboardEvent ke) {
        this.showColorDialog(ke);
    }

}
