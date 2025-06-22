package com.github.xushifu.mls.musical;

import java.util.Arrays;

/****
 * Keyboard128 表示一个包含全部 128个 MIDI 按键的键盘。
 */
final class Midi128Keys {

    public static Key[] allKeys() {
        Key[] src = the128Keys;
        return Arrays.copyOf(src, src.length);
    }

    public static KeyArraySlice slice() {
        Key[] a1 = allKeys();
        KeyArray array = KeyArray.create(a1);
        return KeyArraySlice.create(array, 0, a1.length);
    }

    public static KeyArray array() {
        Key[] a1 = allKeys();
        return KeyArray.create(a1);
    }

    ////////////////////////////////////////////////////////////////////////////
    /// private

    private static final Key[] the128Keys = makeTheAll128Keys();

    private Midi128Keys() {
    }

    private static Key[] makeTheAll128Keys() {
        return KeyFactory.makeTheAll128Keys();
    }

}
