package com.github.xushifu.mls.client;

import java.io.IOException;

import org.junit.Test;

import com.github.xushifu.mls.client.core.clients.ClientService;
import com.github.xushifu.mls.network.mlscp.Response;
import com.github.xushifu.mls.network.mlscp.UserAgent;
import com.github.xushifu.mls.utils.IOUtils;

// import com.github.xushifu.mls.utils.TimeUtils;

public class ClientServiceTest {

    @Test
    public void testPing() throws IOException, InterruptedException {

        MLSClient client = MLSClient4test.openClient();
        ClientService cli_ser = client.getServices().getClientService();
        ClientService.PingOptions opt = new ClientService.PingOptions();

        opt.setWaitForResponse(true);
        opt.setTimeout(10000);
        opt.setResponseHandler((tc2) -> {
            Response resp = tc2.getResponse();
            System.out.println(resp);
        });

        try {
            cli_ser.ping(opt);
        } finally {
            // TimeUtils.sleep(2000);
            IOUtils.close(client);
        }

        UserAgent agent = cli_ser.getUserAgent();
        agent.join();
    }

}
