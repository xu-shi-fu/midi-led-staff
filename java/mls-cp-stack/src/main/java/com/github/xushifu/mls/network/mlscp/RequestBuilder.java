package com.github.xushifu.mls.network.mlscp;

import java.util.ArrayList;
import java.util.List;

import com.github.xushifu.mls.network.mlscp.blocks.ArgbArrayBody;
import com.github.xushifu.mls.network.mlscp.blocks.ByteArrayBody;
import com.github.xushifu.mls.network.mlscp.blocks.NoValueBody;
import com.github.xushifu.mls.network.mlscp.blocks.StringBody;
import com.github.xushifu.mls.network.mlscp.blocks.Uint16Body;
import com.github.xushifu.mls.network.mlscp.blocks.Uint32Body;
import com.github.xushifu.mls.network.mlscp.blocks.Uint64Body;
import com.github.xushifu.mls.network.mlscp.blocks.Uint8Body;

public class RequestBuilder {

    private Method method;
    private Location location;
    private Request request;

    private final UserAgent useragent;
    private final List<Block> additions;

    public RequestBuilder(UserAgent cl) {
        this.useragent = cl;
        this.additions = new ArrayList<>();
    }

    public RequestBuilder setMethod(Method m) {
        this.method = m;
        return this;
    }

    public RequestBuilder setLocation(Location l) {
        this.location = l;
        return this;
    }

    public Method getMethod() {
        return method;
    }

    public Location getLocation() {
        return location;
    }

    public Request getRequest() {
        return request;
    }

    public void setRequest(Request req) {
        if (req == null) {
            return;
        }
        this.method = req.getMethod();
        this.location = req.getLocation();
        this.request = req;
    }

    public UserAgent getUseragent() {
        return useragent;
    }

    public List<Block> getAdditions() {
        return additions;
    }

    public Request create() {
        Request req = this.request;
        if (req == null) {
            req = this.useragent.createNewRequest();
            this.request = req;
        }
        req.setLocation(this.location);
        req.setMethod(this.method);
        req.setBlocks(this.additions);
        return req;
    }

    public RequestBuilder addNoValue(BlockField field) {
        final Block block = new Block();
        final NoValueBody body = new NoValueBody();
        final BlockHead head = block.getHead();
        head.setType(body.type());
        head.setGroup(field.getOwnerGroup());
        head.setField(field);
        block.setBody(body);
        this.additions.add(block);
        return this;
    }

    public RequestBuilder addUint8(BlockField field, int value) {
        final Block block = new Block();
        final Uint8Body body = new Uint8Body();
        final BlockHead head = block.getHead();
        head.setType(body.type());
        head.setGroup(field.getOwnerGroup());
        head.setField(field);
        body.setValue((byte) value);
        block.setBody(body);
        this.additions.add(block);
        return this;
    }

    public RequestBuilder addUint16(BlockField field, int value) {
        final Block block = new Block();
        final Uint16Body body = new Uint16Body();
        final BlockHead head = block.getHead();
        head.setType(body.type());
        head.setGroup(field.getOwnerGroup());
        head.setField(field);
        body.setValue((short) value);
        block.setBody(body);
        this.additions.add(block);
        return this;
    }

    public RequestBuilder addUint32(BlockField field, int value) {
        final Block block = new Block();
        final Uint32Body body = new Uint32Body();
        final BlockHead head = block.getHead();
        head.setType(body.type());
        head.setGroup(field.getOwnerGroup());
        head.setField(field);
        body.setValue(value);
        block.setBody(body);
        this.additions.add(block);
        return this;
    }

    public RequestBuilder addUint64(BlockField field, long value) {
        final Block block = new Block();
        final Uint64Body body = new Uint64Body();
        final BlockHead head = block.getHead();
        head.setType(body.type());
        head.setGroup(field.getOwnerGroup());
        head.setField(field);
        body.setValue(value);
        block.setBody(body);
        this.additions.add(block);
        return this;
    }

    public RequestBuilder addBytes(BlockField field, byte[] value) {
        final Block block = new Block();
        final ByteArrayBody body = new ByteArrayBody();
        final BlockHead head = block.getHead();
        head.setType(body.type());
        head.setGroup(field.getOwnerGroup());
        head.setField(field);
        body.setValue(value);
        block.setBody(body);
        this.additions.add(block);
        return this;
    }

    public RequestBuilder addString(BlockField field, String value) {
        final Block block = new Block();
        final StringBody body = new StringBody();
        final BlockHead head = block.getHead();
        head.setType(body.type());
        head.setGroup(field.getOwnerGroup());
        head.setField(field);
        body.setValue(value);
        block.setBody(body);
        this.additions.add(block);
        return this;
    }

    public RequestBuilder addArgbArray(BlockField field, ARGB[] value) {
        final Block block = new Block();
        final ArgbArrayBody body = new ArgbArrayBody();
        final BlockHead head = block.getHead();
        head.setType(body.type());
        head.setGroup(field.getOwnerGroup());
        head.setField(field);
        body.setValue(value);
        block.setBody(body);
        this.additions.add(block);
        return this;
    }

}
