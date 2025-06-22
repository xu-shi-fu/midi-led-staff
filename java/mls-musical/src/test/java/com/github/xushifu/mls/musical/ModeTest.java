package com.github.xushifu.mls.musical;

import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class ModeTest {

    private static final Logger logger = LoggerFactory.getLogger(ModeTest.class);

    @Test
    public void testAllModes() {

        final ModePattern[] pattern_list = {
                Modes.ionianPattern(),
                Modes.dorianPattern(),
                Modes.phrygianPattern(),
                Modes.lydianPattern(),
                Modes.mixolydianPattern(),
                Modes.aeolianPattern(),
                Modes.locrianPattern(),
        };
        final Tone[] tone_list = Tone.values();

        for (Tone main : tone_list) {
            for (ModePattern pattern : pattern_list) {
                final Mode mode = Mode.create(main, pattern);
                ToneStep[] steps = mode.getSteps();

                logger.debug(mode + "");
                for (ToneStep ts : steps) {
                    logger.debug(ts + "");
                }
                logger.debug("");
            }
        }

        logger.debug("[done]");
    }

}
