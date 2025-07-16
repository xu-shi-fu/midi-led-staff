package com.github.xushifu.mls.client.gui.widgets;

import com.github.xushifu.mls.musical.KeyboardAdapter;

public class ComplexKeyboardViewBuilder {

    public ComplexKeyboardViewBuilder() {
    }

    public IKeyboardView create() {
        IKeyboardView view = this.makeCoreView();
        view = this.tryWrapAsOverview(view);
        view = this.tryWrapAsColorSelector(view);
        return view;
    }

    //////////////////////////////////////////
    /// private

    private KeyboardAdapter adapter;
    private CanvasKeyboardTheme theme;

    private boolean scrollable;
    private boolean asOverview;
    private boolean asColorSelector;

    private IKeyboardView makeCoreView() {
        CanvasKeyboardView.Builder b = CanvasKeyboardView.newBuilder();
        b.setKeyboard(this.adapter);
        b.setScrollable(this.scrollable);
        return b.create();
    }

    private IKeyboardView tryWrapAsOverview(IKeyboardView view) {
        if (this.asOverview) {
            view = CanvasKeyboardOverview.create(view);
        }
        return view;
    }

    private IKeyboardView tryWrapAsColorSelector(IKeyboardView view) {
        if (this.asColorSelector) {
            view = CanvasLedColorSelector.create(view);
        }
        return view;
    }

    public boolean isAsOverview() {
        return asOverview;
    }

    public void setAsOverview(boolean asOverview) {
        this.asOverview = asOverview;
    }

    public boolean isAsColorSelector() {
        return asColorSelector;
    }

    public void setAsColorSelector(boolean asColorSelector) {
        this.asColorSelector = asColorSelector;
    }

    public KeyboardAdapter getAdapter() {
        return adapter;
    }

    public void setAdapter(KeyboardAdapter adapter) {
        this.adapter = adapter;
    }

    public CanvasKeyboardTheme getTheme() {
        return theme;
    }

    public void setTheme(CanvasKeyboardTheme theme) {
        this.theme = theme;
    }

    public boolean isScrollable() {
        return scrollable;
    }

    public void setScrollable(boolean scrollable) {
        this.scrollable = scrollable;
    }

}
