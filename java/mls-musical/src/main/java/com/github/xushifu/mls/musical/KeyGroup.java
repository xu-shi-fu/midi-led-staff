package com.github.xushifu.mls.musical;

import java.util.Arrays;

/***
 * KeyGroup 表示一组(12个) 按键.
 */
public final class KeyGroup {

    public Group getGroup() {
        return group;
    }

    public Key[] listKeys() {
        return Arrays.copyOf(keys, keys.length);
    }

    ////////////////////////////////////////////////////////////////////////////
    /// private

    private final Key[] keys;
    private final Group group;

    private KeyGroup(Group g, Key[] array) {

        if (array.length != 12) {
            throw new IllegalArgumentException("KeyGroup must have 12 keys, but got " + array.length);
        }

        if (g == null) {
            throw new IllegalArgumentException("Group cannot be null");
        }

        this.keys = array;
        this.group = g;
    }

}
