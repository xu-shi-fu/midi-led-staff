package com.github.xushifu.mls.musical;

public final class Tone {

    ////////////////////////////////////////////////////////////////////////////
    // public

    public final static Tone C = create('C', false);
    public final static Tone CS = create('C', true);

    public final static Tone D = create('D', false);
    public final static Tone DS = create('D', true);

    public final static Tone E = create('E', false);

    public final static Tone F = create('F', false);
    public final static Tone FS = create('F', true);

    public final static Tone G = create('G', false);
    public final static Tone GS = create('G', true);

    public final static Tone A = create('A', false);
    public final static Tone AS = create('A', true);

    public final static Tone B = create('B', false);

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
        return name;
    }

    public static boolean equals(Tone t1, Tone t2) {
        if (t1 == null || t2 == null) {
            return false;
        }
        return t1.equals(t2);
    }

    ////////////////////////////////////////////////////////////////////////////
    // private

    private final String name;
    private final char at;
    private final boolean sharp;

    private Tone(char _base, boolean _sharp) {
        this.at = _base;
        this.sharp = _sharp;
        this.name = String.valueOf(_base) + (_sharp ? "#" : "");
    }

    private static Tone create(char base, boolean sharp) {
        return new Tone(base, sharp);
    }

}
