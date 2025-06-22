package com.github.xushifu.mls.musical;

import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class ChordTest {

    private static final Logger logger = LoggerFactory.getLogger(ChordTest.class);

    @Test
    public void testAllChords() {

        final ChordPattern[] pattern_list = {

                Chords.patternMajor(),
                Chords.patternMinor(),
                Chords.patternDiminished(),
                Chords.patternAugmented(),

                Chords.patternMajor7th(),
                Chords.patternMinor7th(),
                Chords.patternDominant7th(),
                Chords.patternMinor7b5(),
                Chords.patternDiminished7th(),

        };
        final Tone[] tone_list = Tone.values();

        for (Tone root : tone_list) {
            for (ChordPattern pattern : pattern_list) {
                final Chord chd = Chord.create(root, pattern);
                ToneStep[] steps = chd.getSteps();

                logger.debug(chd + "");
                for (ToneStep ts : steps) {
                    logger.debug(ts + "");
                }
                logger.debug("");
            }
        }

        logger.debug("[done]");
    }

}
