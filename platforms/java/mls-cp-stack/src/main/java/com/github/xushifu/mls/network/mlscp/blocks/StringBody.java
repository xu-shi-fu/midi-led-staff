package com.github.xushifu.mls.network.mlscp.blocks;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;

import com.github.xushifu.mls.network.mlscp.BlockBody;
import com.github.xushifu.mls.network.mlscp.BlockType;
import com.github.xushifu.mls.utils.Strings;

public class StringBody implements BlockBody {

    private String value;
    private Snap snap;

    public StringBody() {
    }

    public void setLength(int len) {
        if (len < 0) {
            len = 0;
        }

        final byte[] buffer = new byte[len];
        final Snap s = new Snap();

        s.length = len;
        s.raw = buffer;
        s.str = "";

        this.snap = s;
        this.value = s.str;
    }

    public String getValue() {
        return value;
    }

    public void setValue(String value) {
        this.value = value;
        this.snap = null;
    }

    @Override
    public BlockType type() {
        return BlockType.STRING;
    }

    @Override
    public int length() {
        Snap s = this.getSnap();
        return s.length;
    }

    private final static class Snap {
        String str;
        byte[] raw;
        int length; // len(raw), include '\0'
    }

    private Snap getSnap() {

        Snap sn = this.snap;
        String str = this.value;
        if (sn != null) {
            String str2 = sn.str;
            if (Strings.equal(str, str2)) {
                return sn;
            }
        }

        if (str == null) {
            str = "";
        }

        Charset cs = StandardCharsets.UTF_8;
        ByteBuffer buffer = cs.encode(str);
        byte[] raw = buffer.array();

        sn = new Snap();
        sn.str = str;
        sn.raw = raw;
        sn.length = raw.length;

        this.snap = sn;
        this.value = str;
        return sn;
    }

    @Override
    public void encode(DataOutput dst) throws IOException {
        final Snap s = this.getSnap();
        dst.write(s.raw);
    }

    @Override
    public void decode(DataInput src) throws IOException {

        final Snap s = this.getSnap();
        int len = s.length;
        if (len < 0) {
            len = 0;
        }

        byte[] buffer = new byte[len];
        src.readFully(buffer);

        Charset cs = StandardCharsets.UTF_8;
        String str = new String(buffer, cs);

        s.raw = buffer;
        s.length = len;
        s.str = str;

        this.snap = s;
        this.value = str;
    }

}
