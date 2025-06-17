package com.github.xushifu.mls.client;

import com.github.xushifu.mls.client.core.clients.ClientService;
import com.github.xushifu.mls.client.core.leds.LEDService;

public interface MLSClientServices {

    ClientService getClientService();

    LEDService getLEDService();

}
