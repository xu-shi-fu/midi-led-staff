package com.github.xushifu.mls.client.gui.config;

import com.bitwormhole.starter4j.application.ApplicationContext;
import com.bitwormhole.starter4j.application.ComponentRegistryFunc;
import com.bitwormhole.starter4j.application.ComponentTemplate;
import com.bitwormhole.starter4j.application.LifeCycle;
import com.bitwormhole.starter4j.application.ComponentTemplate.RegistrationT;
import com.bitwormhole.starter4j.application.components.ComponentSelector;
import com.bitwormhole.starter4j.swing.FrameManager;
import com.bitwormhole.starter4j.swing.SwingPromiseContext;
import com.github.xushifu.mls.client.gui.SwingClientContext;
import com.bitwormhole.starter4j.application.Life;

final class ConfigSwingContext implements LifeCycle {

    private ApplicationContext ac;

    private ConfigSwingContext() {
    }

    public static ComponentRegistryFunc registerFunc() {
        return (cr) -> {
            final ComponentTemplate ct = new ComponentTemplate(cr);
            RegistrationT<ConfigSwingContext> rt = ct.component(ConfigSwingContext.class);
            rt.setId(ConfigSwingContext.class);
            rt.addClass("jframe");
            rt.onNew(() -> new ConfigSwingContext());
            rt.onInject((ie, inst) -> {
                inst.ac = ie.getContext();
            });
            rt.register();
        };
    }

    @Override
    public Life life() {
        Life l = new Life();
        l.onCreate = () -> this.onCreate();
        return l;
    }

    private void onCreate() {

        ComponentSelector sel = ComponentSelector.getInstance();
        FrameManager fm = this.ac.selectComponent(sel.ID(FrameManager.class), FrameManager.class);
        SwingClientContext ctx = SwingClientContext.getInstance(this.ac);

        ctx.setPromiseContext(SwingPromiseContext.getInstance());
        ctx.setApplicationContext(this.ac);
        ctx.setFrameManager(fm);
    }

}
