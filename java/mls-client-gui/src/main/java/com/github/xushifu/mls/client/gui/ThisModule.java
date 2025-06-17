package com.github.xushifu.mls.client.gui;

import com.bitwormhole.starter4j.application.Module;
import com.bitwormhole.starter4j.application.ModuleBuilder;
import com.bitwormhole.starter4j.swing.SwingApplicationStarter;
import com.github.xushifu.mls.client.MLSClient;
import com.github.xushifu.mls.client.gui.config.ConfigAll;

final class ThisModule {

    private static final String theModuleName = MLSClientGUI.class.getName();
    private static final String theModuleVersion = "0.0.0";
    private static final int theModuleRevision = 0;

    private ThisModule() {
    }

    public static Module module() {
        ModuleBuilder mb = new ModuleBuilder();

        mb.setName(theModuleName);
        mb.setVersion(theModuleVersion);
        mb.setRevision(theModuleRevision);

        mb.setComponents(ConfigAll.all());

        mb.depend(MLSClient.module());
        mb.depend(SwingApplicationStarter.module());

        return mb.create();
    }

}
