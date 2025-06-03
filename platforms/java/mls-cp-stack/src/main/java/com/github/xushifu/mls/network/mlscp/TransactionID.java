package com.github.xushifu.mls.network.mlscp;

public final class TransactionID implements IntegerValue {

    private final int id;

    public TransactionID(int n) {
        this.id = n;
    }

    @Override
    public String toString() {
        return String.valueOf(this.id);
    }

    public static TransactionID next() {
        return generator.gen();
    }

    private static final class Generator {

        private int count = 1;

        synchronized TransactionID gen() {
            int id = this.count++;
            return new TransactionID(id);
        }
    }

    private static final Generator generator = new Generator();

    @Override
    public int toInt() {
        return this.id;
    }
}
