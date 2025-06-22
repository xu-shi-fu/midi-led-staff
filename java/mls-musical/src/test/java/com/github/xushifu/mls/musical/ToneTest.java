package com.github.xushifu.mls.musical;

import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class ToneTest {

    private static final Logger logger = LoggerFactory.getLogger(ToneTest.class);

    @Test
    public void testValues() {
        Tone[] list = Tone.values();
        for (Tone tone : list) {
            logger.debug(tone + "");
        }
    }

    @Test
    public void testGetInstance() {
        for (int i = -10; i < 255; i++) {
            Tone t = Tone.getInstance(i);
            logger.debug("index." + i + "=" + t);
        }
    }

}
