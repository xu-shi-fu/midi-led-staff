package com.github.xushifu.mls.client.gui;

import com.bitwormhole.starter4j.application.ApplicationContext;
import com.bitwormhole.starter4j.application.tasks.PromiseContext;
import com.bitwormhole.starter4j.swing.FrameManager;
import com.github.xushifu.mls.client.AbstractClientContext;
import com.github.xushifu.mls.client.ClientContext;
import com.github.xushifu.mls.client.ClientContextHolder;

public final class SwingClientContext extends AbstractClientContext {

    private PromiseContext promiseContext;
    private FrameManager frameManager;

    private SwingClientContext() {
    }

    public static SwingClientContext getInstance(ClientContextHolder holder) {
        final ClientContext cc1 = holder.getClientContext();
        if (cc1 instanceof SwingClientContext) {
            return (SwingClientContext) cc1;
        }
        final SwingClientContext cc2 = new SwingClientContext();
        holder.setClientContext(cc2);
        cc2.setClientContextHolder(holder);
        return cc2;
    }

    public static SwingClientContext getInstance(ApplicationContext ac) {
        ClientContextHolder holder = ClientContextHolder.getInstance(ac);
        return getInstance(holder);
    }

    public static SwingClientContext getInstance(final ClientContext cc1) {
        if (cc1 == null) {
            throw new RuntimeException("param: ClientContext is nil");
        }
        ApplicationContext ac = cc1.getApplicationContext();
        return getInstance(ac);
    }

    public PromiseContext getPromiseContext() {
        return promiseContext;
    }

    public void setPromiseContext(PromiseContext promiseContext) {
        this.promiseContext = promiseContext;
    }

    public FrameManager getFrameManager() {
        return frameManager;
    }

    public void setFrameManager(FrameManager frameManager) {
        this.frameManager = frameManager;
    }

}
