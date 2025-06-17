package com.github.xushifu.mls.client;

import com.bitwormhole.starter4j.application.ApplicationContext;
import com.bitwormhole.starter4j.application.ComponentRegistryFunc;
import com.bitwormhole.starter4j.application.ComponentTemplate;
import com.bitwormhole.starter4j.application.ComponentTemplate.RegistrationT;

public final class ClientContextHolder {

    private ClientContext clientContext;

    private ClientContextHolder() {
    }

    public ClientContext getClientContext() {
        return clientContext;
    }

    public void setClientContext(ClientContext clientContext) {
        this.clientContext = clientContext;
    }

    public static ClientContextHolder getInstance(ApplicationContext ac) {
        String sel = "#" + ClientContextHolder.class.getName();
        return ac.selectComponent(sel, ClientContextHolder.class);
    }

    public static ComponentRegistryFunc registry() {
        return (cr) -> {
            final ComponentTemplate ct = new ComponentTemplate(cr);
            final RegistrationT<ClientContextHolder> rt = ct.component(ClientContextHolder.class);
            rt.setId(ClientContextHolder.class);
            rt.addClass(ClientContextHolder.class);
            rt.onNew(() -> new ClientContextHolder());
            rt.onInject((ie, inst) -> {
            });
            rt.register();
        };
    }
}
