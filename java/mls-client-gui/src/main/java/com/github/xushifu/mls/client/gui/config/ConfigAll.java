package com.github.xushifu.mls.client.gui.config;

import com.bitwormhole.starter4j.application.ComponentRegistryFunc;
import com.bitwormhole.starter4j.application.ComponentRegistryMultiplexer;

public final class ConfigAll {

    public static ComponentRegistryFunc all() {
        ComponentRegistryMultiplexer multiplexer = new ComponentRegistryMultiplexer();
        multiplexer.add(ConfigFrames.registerFunc());
        multiplexer.add(ConfigSwingContext.registerFunc());
        return multiplexer.multiplex();
    }

}
