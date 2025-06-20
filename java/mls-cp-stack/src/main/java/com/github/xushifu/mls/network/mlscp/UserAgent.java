package com.github.xushifu.mls.network.mlscp;

import java.io.Closeable;
import java.net.SocketAddress;

public interface UserAgent extends Closeable {

    Request createNewRequest();

    Dispatcher getDispatcher();

    void join() throws InterruptedException;

    SocketAddress getLocal();

    SocketAddress getRemote();

}
