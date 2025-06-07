package com.github.xushifu.mls.network.mlscp.blocks;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

import com.github.xushifu.mls.network.mlscp.BlockBody;
import com.github.xushifu.mls.network.mlscp.BlockType;

public class NoValueBody implements BlockBody {

    public NoValueBody() {
    }

    @Override
    public BlockType type() {
        return BlockType.NO_VALUE;
    }

    @Override
    public int length() {
        return 0;
    }

    @Override
    public void encode(DataOutput dst) throws IOException {
    }

    @Override
    public void decode(DataInput src) throws IOException {
    }

}
