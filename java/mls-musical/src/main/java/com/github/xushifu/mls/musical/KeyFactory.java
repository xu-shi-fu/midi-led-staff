package com.github.xushifu.mls.musical;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

final class KeyFactory {

    private static final class KeyGroupTemplate {

        final Key[] keys;
        final Group group;

        KeyGroupTemplate(Key[] array) {
            this.keys = array;
            this.group = array[0].getGroup();
        }

        // 取向下一个八度的模板
        public KeyGroupTemplate lower() {

            final Key[] src = this.keys;
            final Key[] dst = new Key[src.length];
            final Key.Builder b = new Key.Builder();
            final Group group2 = this.group.lower();

            if (isGroupNA(group2)) {
                return null;
            }

            for (int i = 0; i < src.length; i++) {
                final Key key1 = src[i];
                b.index = key1.getIndex() - 12; // 八度下移
                b.group = group2;
                b.tone = key1.getTone();
                b.frequency = key1.getFrequency() / 2;
                dst[i] = b.build();
            }

            return new KeyGroupTemplate(dst);
        }

        // 取向上一个八度的模板
        public KeyGroupTemplate upper() {

            final Key[] src = this.keys;
            final Key[] dst = new Key[src.length];
            final Key.Builder b = new Key.Builder();
            final Group group2 = this.group.upper();

            if (isGroupNA(group2)) {
                return null;
            }

            for (int i = 0; i < src.length; i++) {
                final Key key1 = src[i];
                b.index = key1.getIndex() + 12; // 八度上移
                b.group = group2;
                b.tone = key1.getTone();
                b.frequency = key1.getFrequency() * 2;
                dst[i] = b.build();
            }

            return new KeyGroupTemplate(dst);
        }

        static boolean isGroupNA(Group g) {
            if (g == null) {
                return true;
            }
            return Group.NONE.equals(g);
        }
    }

    private static Key makeA440hz() {
        int index = 69; // A (440hz) is 69
        Key.Builder b = new Key.Builder();
        b.group = Group.getGroupByIndex(index / 12);
        b.index = index;
        b.tone = Tone.A;
        b.frequency = 440.0f;
        return b.build();
    }

    private static KeyGroupTemplate makeBaseTemplate() {

        final Key a440 = makeA440hz();
        final Tone[] tones = Tone.values();
        final Key[] keys = new Key[tones.length];
        final Key.Builder b = new Key.Builder();

        // check a1 & a2
        final int a2at = 9;
        final Tone a2 = tones[a2at];
        final Tone a1 = a440.getTone();
        if (!Tone.equals(a1, a2)) {
            throw new IllegalStateException("A2 tone is not A, but " + a1);
        }

        final Group group = a440.getGroup();

        for (int i = 0; i < tones.length; i++) {
            final int offset = i - a2at;
            b.index = a440.getIndex() + offset;
            b.frequency = computeFrequency(offset, a440);
            b.tone = tones[i];
            b.group = group;
            keys[i] = b.build();
        }

        return new KeyGroupTemplate(keys);
    }

    private static float computeFrequency(int offset, Key a440) {
        final float f1 = a440.getFrequency();
        final float x = 1.059463094f; // 2^(1/12);
        float freq = f1;
        if (offset < 0) {
            for (; offset < 0; offset++) {
                freq = freq / x;
            }
        } else if (offset > 0) {
            for (; offset > 0; offset--) {
                freq = freq * x;
            }
        }
        return freq;
    }

    private static void copyTemplateKeysToList(List<Key> dst, KeyGroupTemplate src) {
        Key[] items = src.keys;
        for (Key key : items) {
            dst.add(key);
        }
    }

    private static int compareKeys(Key a, Key b) {
        if (a == null || b == null) {
            if (a == null) {
                return -1;
            }
            return 1;
        }
        int diff = a.getIndex() - b.getIndex();
        if (diff == 0) {
            return 0; // 相等
        }
        return (diff > 0) ? 1 : -1;
    }

    public static Key[] makeTheAllKeys() {

        final List<Key> list = new ArrayList<>();
        final KeyGroupTemplate template1 = makeBaseTemplate();

        copyTemplateKeysToList(list, template1);
        KeyGroupTemplate template;

        // lowers
        template = template1;
        for (;;) {
            template = template.lower();
            if (template == null) {
                break;
            }
            copyTemplateKeysToList(list, template);
        }

        // uppers
        template = template1;
        for (;;) {
            template = template.upper();
            if (template == null) {
                break;
            }
            copyTemplateKeysToList(list, template);
        }

        // sort list
        list.sort((a, b) -> compareKeys(a, b));

        Key[] array = list.toArray(new Key[0]);
        // return Arrays.copyOf(array, 128);
        return Arrays.copyOf(array, array.length);
    }

}
