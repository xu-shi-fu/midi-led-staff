package com.github.xushifu.mls.network.mlscp;

public final class Method implements IntegerValue {

    public final static Method GET = create(1, "GET");
    public final static Method POST = create(2, "POST");
    public final static Method PUT = create(3, "PUT");
    public final static Method DELETE = create(4, "DELETE");

    private Method(int n, String text) {
        this.num = n;
        this.str = text;
    }

    private final int num;
    private final String str;

    private static Method create(int num, String text) {
        return new Method(num, text);
    }

    @Override
    public int toInt() {
        return this.num;
    }

    public static int toInt(Method m) {
        if (m == null) {
            return 0;
        }
        return m.num;
    }

    @Override
    public String toString() {
        return this.str;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + num;
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
        Method other = (Method) obj;
        if (num != other.num)
            return false;
        return true;
    }

}
