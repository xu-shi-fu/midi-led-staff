package com.github.xushifu.mls.network.mlscp;

import java.net.InetSocketAddress;

import org.junit.Test;

import com.github.xushifu.mls.utils.IOUtils;
import com.github.xushifu.mls.utils.TimeUtils;

public class ClientTest {

    @Test
    public void testClient() throws Exception {

        ClientBuilder builder = ClientBuilder.newInstance();
        builder.setRemote(InetSocketAddress.createUnresolved("192.168.0.104", 7923));
        builder.setLocal(InetSocketAddress.createUnresolved("0.0.0.0", 7928));
        builder.setTimeout(300 * 1000);
        Client client = builder.open();

        Request req = client.createNewRequest();
        req.setMethod(Method.GET);
        req.setLocation(Location.PING);

        client.getDispatcher().dispatch(req.context);

        TimeUtils.sleep(3600 * 1000);
        IOUtils.close(client);
        client.join();
    }

}
