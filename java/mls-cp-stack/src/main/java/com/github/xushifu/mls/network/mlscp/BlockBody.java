package com.github.xushifu.mls.network.mlscp;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

public interface BlockBody {

    BlockType type();

    /**
     * size_of(body), in bytes
     */
    int length();

    void encode(DataOutput dst) throws IOException;

    void decode(DataInput src) throws IOException;

}
