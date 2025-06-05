package com.github.xushifu.mls.network.mlscp;

import org.junit.Test;

import com.github.xushifu.mls.utils.IOUtils;

public class AccessLedTest {

    @Test
    public void testGetLedState() throws Exception {
        UnitClientHolder holder = new UnitClientHolder();
        try {

            Client cl = holder.open();
            RequestBuilder rb = new RequestBuilder(cl);

            rb.setMethod(Method.GET).setLocation(Location.LEDS);
            rb.addUint8(BlockField.LED_POSITION, 12);
            rb.addUint8(BlockField.LED_COUNT, 36);

            Request req = rb.create();
            cl.getDispatcher().dispatch(req.context);

        } finally {
            IOUtils.close(holder);
        }
    }

    @Test
    public void testSetLedState() throws Exception {
        UnitClientHolder holder = new UnitClientHolder();

        int count = 36;
        ARGB[] items = new ARGB[count];

        try {

            Client cl = holder.open();
            RequestBuilder rb = new RequestBuilder(cl);

            rb.setMethod(Method.POST).setLocation(Location.LEDS);
            rb.addUint8(BlockField.LED_POSITION, 12);
            rb.addUint8(BlockField.LED_COUNT, count);
            rb.addArgbArray(BlockField.LED_ITEMS, items);

            Request req = rb.create();
            cl.getDispatcher().dispatch(req.context);

        } finally {
            IOUtils.close(holder);
        }
    }

}
