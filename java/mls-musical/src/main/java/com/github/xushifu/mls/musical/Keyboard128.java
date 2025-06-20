package com.github.xushifu.mls.musical;

import java.util.Arrays;

/****
 * Keyboard128 表示一个包含全部 128个 MIDI 按键的键盘。
 */
public final class Keyboard128 extends KeyboardWrapper {

    private Keyboard128(Keyboard in) {
        super(in);
    }

    public static Key[] allKeys() {
        Key[] src = the128Keys;
        return Arrays.copyOf(src, src.length);
    }

    ////////////////////////////////////////////////////////////////////////////
    /// private

    private static final Key[] the128Keys = makeTheAll128Keys();

    private static Key[] makeTheAll128Keys() {
        return KeyFactory.makeTheAll128Keys();
    }

}
