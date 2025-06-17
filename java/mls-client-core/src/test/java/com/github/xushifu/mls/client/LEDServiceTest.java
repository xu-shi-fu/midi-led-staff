package com.github.xushifu.mls.client;

import java.io.IOException;

import org.junit.Test;

import com.github.xushifu.mls.client.core.clients.ClientService;
import com.github.xushifu.mls.client.core.leds.LEDService;
import com.github.xushifu.mls.network.mlscp.UserAgent;
import com.github.xushifu.mls.utils.IOUtils;

public class LEDServiceTest {

    @Test
    public void testFetch() throws IOException, InterruptedException {

        MLSClient client = MLSClient4test.openClient();
        ClientService cli_ser = client.getServices().getClientService();
        LEDService led_ser = client.getServices().getLEDService();
        LEDService.FetchOptions opt = new LEDService.FetchOptions();

        // opt.setTimeout(3000);
        // opt.setWaitForResponse(true);

        try {
            led_ser.fetch(opt);
        } finally {
            // TimeUtils.sleep(2000);
            IOUtils.close(client);
        }

        UserAgent agent = cli_ser.getUserAgent();
        agent.join();
    }

}
