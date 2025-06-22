package com.github.xushifu.mls.musical;

import java.util.Arrays;

public final class Group {

    public final static Group NONE = initNone();

    public static Group[] listGroups() {
        Group[] src = theCache.groups;
        return Arrays.copyOf(src, src.length);
    }

    public static boolean equals(Group a, Group b) {
        if (a == null || b == null) {
            return false;
        }
        if (a == b) {
            return true;
        }
        return a.number == b.number;
    }

    public static final Group getGroupByIndex(int index) {
        Group[] groups = theCache.groups;
        if (0 <= index && index < groups.length) {
            return groups[index];
        }
        return NONE;
    }

    public static final Group getGroupByNumber(int num) {
        int index = number2index(num);
        return getGroupByIndex(index);
    }

    public int getIndex() {
        return index;
    }

    public int getNumber() {
        return number;
    }

    public String getName() {
        return name;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + number;
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (obj == null)
            return false;
        if (getClass() != obj.getClass())
            return false;
        Group other = (Group) obj;
        if (number != other.number)
            return false;
        return true;
    }

    @Override
    public String toString() {
        return "[Group " + this.number + "]";
    }

    /***
     * upper 返回当前组的高一个8度组。
     */
    public Group upper() {
        return getGroupByIndex(this.index + 1);
    }

    /***
     * lower 返回当前组的低一个8度组。
     */
    public Group lower() {
        return getGroupByIndex(this.index - 1);
    }

    ////////////////////////////////////////////////////////////////////////////
    /// private

    private final int number;
    private final int index;
    private final String name;

    private final static Cache theCache = initTheCache();

    private Group(int idx) {

        final int num = index2number(idx);
        String txt = "key-group" + num;

        if (idx < 0) {
            txt = "key-group-none";
        }

        this.number = num;
        this.index = idx;
        this.name = txt;
    }

    private static Cache initTheCache() {
        Group[] array = new Group[11];
        for (int i = 0; i < array.length; i++) {
            array[i] = new Group(i);
        }
        return new Cache(array);
    }

    /****
     * number_index_difference 是 number 和 index 之间的差值。
     */
    private static final int number_index_difference = 2;

    private static int number2index(int num) {
        return num + number_index_difference;
    }

    private static int index2number(int idx) {
        return idx - number_index_difference;
    }

    private final static class Cache {

        final Group[] groups;

        Cache(Group[] array) {
            this.groups = array;
        }
    }

    private static Group initNone() {
        return new Group(-99);
    }

}
