package com.github.xushifu.mls.network.mlscp;

import java.net.InetSocketAddress;

import org.junit.Test;

import com.github.xushifu.mls.utils.IOUtils;

public class ClientTest {

    @Test
    public void testClient() throws Exception {

        ClientBuilder builder = ClientBuilder.newInstance();
        builder.setRemote(InetSocketAddress.createUnresolved("192.168.0.111", 7923));
        builder.setLocal(InetSocketAddress.createUnresolved("0.0.0.0", 7928));
        Client client = builder.open();

        Request req = client.createNewRequest();
        req.setMethod(Method.GET);
        req.setLocation(Location.PING);

        client.getDispatcher().dispatch(req.context);

        IOUtils.close(client);
        client.join();
    }

}
