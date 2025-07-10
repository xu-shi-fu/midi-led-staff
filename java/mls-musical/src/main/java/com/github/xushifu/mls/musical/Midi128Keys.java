package com.github.xushifu.mls.musical;

import java.util.Arrays;

/****
 * Keyboard128 表示一个包含全部 128个 MIDI 按键的键盘。
 */
final class Midi128Keys {

    public static Key[] allKeys() {
        Key[] src = theAllKeys;
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

    public static Key getKeyAt(int index) {
        Key[] src = theAllKeys;
        Key k = null;
        if ((0 <= index) && (index < src.length)) {
            k = src[index];
        }
        return (k == null) ? Key.NONE : k;
    }

    ////////////////////////////////////////////////////////////////////////////
    /// private

    private static final Key[] theAllKeys = makeTheAllKeys();

    private Midi128Keys() {
    }

    private static Key[] makeTheAllKeys() {
        return KeyFactory.makeTheAllKeys();
    }

}
