package com.github.xushifu.mls.client;

import com.bitwormhole.starter4j.Starter;
import com.bitwormhole.starter4j.application.ComponentRegistry;
import com.bitwormhole.starter4j.application.ComponentRegistryFunc;
import com.bitwormhole.starter4j.application.ComponentRegistryMultiplexer;
import com.bitwormhole.starter4j.application.Module;
import com.bitwormhole.starter4j.application.ModuleBuilder;

final class ThisModule {

    private static final String theModuleName = MLSClient.class.getName();
    private static final String theModuleVersion = "0.0.0";
    private static final int theModuleRevision = 0;

    private ThisModule() {
    }

    public static Module module() {
        ModuleBuilder mb = new ModuleBuilder();

        mb.setName(theModuleName);
        mb.setVersion(theModuleVersion);
        mb.setRevision(theModuleRevision);

        mb.setComponents((cr) -> listComponents(cr));

        mb.depend(Starter.module());

        return mb.create();
    }

    private static void listComponents(ComponentRegistry cr) {
        ComponentRegistryMultiplexer multiplexer = new ComponentRegistryMultiplexer();
        multiplexer.add(ClientContextHolder.registry());
        multiplexer.multiplex().invoke(cr);
    }

}
