package com.github.xushifu.mls.client;

import com.bitwormhole.starter4j.application.ApplicationContext;

public interface ClientContext {

    ApplicationContext getApplicationContext();

    ClientContextHolder getClientContextHolder();

    MLSClient getClient();

}
