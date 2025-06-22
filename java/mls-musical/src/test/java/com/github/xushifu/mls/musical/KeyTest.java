package com.github.xushifu.mls.musical;

import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class KeyTest {

    private static final Logger logger = LoggerFactory.getLogger(KeyTest.class);

    @Test
    public void testAll() {
        Key[] all = Key.all();
        for (Key key : all) {
            logger.debug(key + "");
        }
    }
}
