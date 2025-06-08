package com.github.xushifu.mls.network.mlscp;

import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.github.xushifu.mls.utils.IOUtils;

public class AccessLedTest {

    private final static Logger logger = LoggerFactory.getLogger(AccessLedTest.class);

    @Test
    public void testGetLedState() throws Exception {
        TestingUserAgentHolder holder = new TestingUserAgentHolder();
        try {

            UserAgent cl = holder.open();
            RequestBuilder rb = new RequestBuilder(cl);

            rb.setMethod(Method.GET).setLocation(Location.LEDS);

            rb.addUint8(BlockField.LED_VIEW_POSITION, 0);
            rb.addUint8(BlockField.LED_VIEW_SIZE, 0);

            rb.addNoValue(BlockField.COMMON_FLUSH);

            rb.addUint8(BlockField.LED_PART_POSITION, 20);
            rb.addUint8(BlockField.LED_PART_SIZE, 30);

            rb.addNoValue(BlockField.COMMON_FLUSH);

            Request req = rb.create();

            req.context.setHandler((ctx) -> {
                logger.debug("ctx.class = " + ctx.getClass());
            });

            cl.getDispatcher().dispatch(req.context);

        } finally {
            IOUtils.close(holder);
        }
    }

    @Test
    public void testSetLedState() throws Exception {
        TestingUserAgentHolder holder = new TestingUserAgentHolder();

        int count = 36;
        ARGB[] items = new ARGB[count];

        try {

            UserAgent cl = holder.open();
            RequestBuilder rb = new RequestBuilder(cl);

            rb.setMethod(Method.POST).setLocation(Location.LEDS);
            rb.addUint8(BlockField.LED_PART_POSITION, 12);
            rb.addUint8(BlockField.LED_PART_SIZE, count);
            rb.addArgbArray(BlockField.LED_PART_ITEMS, items);

            Request req = rb.create();
            cl.getDispatcher().dispatch(req.context);

        } finally {
            IOUtils.close(holder);
        }
    }

}
