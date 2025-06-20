package com.github.xushifu.mls.musical;

import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class KeyboardTest {

    private static final Logger logger = LoggerFactory.getLogger(KeyboardTest.class);

    @Test
    public void testKeyboard128AllKeys() {

        Key[] all = Keyboard128.allKeys();
        for (Key key : all) {
            String str = KeyLogger.stringify(key);
            logger.info(str);
        }

    }

}
