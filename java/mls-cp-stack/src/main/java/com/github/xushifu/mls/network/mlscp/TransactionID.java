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

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + id;
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
        TransactionID other = (TransactionID) obj;
        if (id != other.id)
            return false;
        return true;
    }

    public static TransactionID next() {
        return generator.gen();
    }

    private static final class Generator {

        private int count = 1;

        Generator() {
            this.count = (int) System.currentTimeMillis();
        }

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
