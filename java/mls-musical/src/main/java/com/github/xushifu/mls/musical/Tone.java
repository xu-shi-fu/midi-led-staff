package com.github.xushifu.mls.musical;

public final class Tone {

    ////////////////////////////////////////////////////////////////////////////
    // public

    public final static Tone C = create(0, 'C', false);
    public final static Tone CS = create(1, 'C', true);

    public final static Tone D = create(2, 'D', false);
    public final static Tone DS = create(3, 'D', true);

    public final static Tone E = create(4, 'E', false);

    public final static Tone F = create(5, 'F', false);
    public final static Tone FS = create(6, 'F', true);

    public final static Tone G = create(7, 'G', false);
    public final static Tone GS = create(8, 'G', true);

    public final static Tone A = create(9, 'A', false);
    public final static Tone AS = create(10, 'A', true);

    public final static Tone B = create(11, 'B', false);

    /***
     * 返回所有的 12个 音调
     */
    public static Tone[] values() {
        return new Tone[] {
                C, CS, D, DS, E, F, FS, G, GS, A, AS, B
        };
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + at;
        result = prime * result + (sharp ? 1231 : 1237);
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
        Tone other = (Tone) obj;
        if (at != other.at)
            return false;
        if (sharp != other.sharp)
            return false;
        return true;
    }

    @Override
    public String toString() {
        return "[Tone " + name + "]";
    }

    public String getName() {
        return name;
    }

    public int getPosition() {
        return position;
    }

    public static boolean equals(Tone t1, Tone t2) {
        if (t1 == null || t2 == null) {
            return false;
        }
        return t1.equals(t2);
    }

    public static Tone getInstance(int index) {
        Tone[] all = theNormalToneArray;
        if (index < 0) {
            return all[0];
        }
        int count = all.length;
        return all[index % count];
    }

    ////////////////////////////////////////////////////////////////////////////
    // private

    private final String name;
    private final char at;
    private final boolean sharp;
    private final int position;

    private static final Tone[] theNormalToneArray = values();

    private Tone(int _pos, char _base, boolean _sharp) {
        this.at = _base;
        this.sharp = _sharp;
        this.position = _pos;
        this.name = String.valueOf(_base) + (_sharp ? "#" : "");
    }

    private static Tone create(int pos, char base, boolean sharp) {
        return new Tone(pos, base, sharp);
    }

}
