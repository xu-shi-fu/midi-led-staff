package com.github.xushifu.mls.network.mlscp;

import java.net.SocketAddress;
import java.util.List;

public class Stack {

    public SocketAddress remote;
    public SocketAddress local;
    public RxFilterChain rx;
    public TxFilterChain tx;
    public Dispatcher dispatcher;
    public List<Layer> layers;
    public StackRuntime runtime;
    public UserAgent useragent;
    public int timeout;

}
