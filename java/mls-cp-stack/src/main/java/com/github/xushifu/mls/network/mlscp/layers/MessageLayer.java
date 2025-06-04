package com.github.xushifu.mls.network.mlscp.layers;

import java.util.ArrayList;
import java.util.List;

import com.github.xushifu.mls.network.mlscp.Block;
import com.github.xushifu.mls.network.mlscp.BlockBody;
import com.github.xushifu.mls.network.mlscp.BlockField;
import com.github.xushifu.mls.network.mlscp.BlockGroup;
import com.github.xushifu.mls.network.mlscp.BlockTypeAdapter;
import com.github.xushifu.mls.network.mlscp.Layer;
import com.github.xushifu.mls.network.mlscp.Location;
import com.github.xushifu.mls.network.mlscp.Method;
import com.github.xushifu.mls.network.mlscp.ProtocolVersion;
import com.github.xushifu.mls.network.mlscp.Request;
import com.github.xushifu.mls.network.mlscp.Response;
import com.github.xushifu.mls.network.mlscp.RxFilterChain;
import com.github.xushifu.mls.network.mlscp.Status;
import com.github.xushifu.mls.network.mlscp.TxFilterChain;
import com.github.xushifu.mls.network.mlscp.blocks.ByteBody;
import com.github.xushifu.mls.network.mlscp.blocks.StringBody;
import com.github.xushifu.mls.network.mlscp.blocks.Uint16Body;
import com.github.xushifu.mls.network.mlscp.blocks.Uint32Body;
import com.github.xushifu.mls.network.mlscp.blocks.Uint8Body;
import com.github.xushifu.mls.network.mlscp.TransactionContext;
import com.github.xushifu.mls.network.mlscp.TransactionID;

/**
 * 消息层用于对收发的消息进行预处理/后处理
 */
public class MessageLayer implements Layer {

    public MessageLayer() {
    }

    @Override
    public void receive(TransactionContext ctx, RxFilterChain next) throws Exception {

        Response resp = ctx.getResponse();
        BlockHolder holder = new BlockHolder();
        scanBlocks(resp.getBlocks(), holder);

        resp.setVersion(holder.getVersion());
        resp.setStatus(holder.getStatus());
        ctx.setId(holder.getTransaction());

        next.receive(ctx);
    }

    @Override
    public void send(TransactionContext ctx, TxFilterChain next) throws Exception {

        Request req = ctx.getRequest();
        BlockHolder holder = new BlockHolder();
        scanBlocks(req.getBlocks(), holder);

        holder.setVersion(req.getVersion());
        holder.setMethod(req.getMethod());
        holder.setLocation(req.getLocation());
        holder.setTransaction(ctx.getId());
        holder.setEOP();

        req.setBlocks(listAllBlocks(holder));
        next.send(ctx);
    }

    private final static class BlockHolder {

        Block version;
        Block transaction;
        Block method;
        Block location;
        Block code;
        Block message;
        Block eop; // end-of-pack

        final List<Block> others;

        BlockHolder() {
            this.others = new ArrayList<>();
        }

        static BlockBody bodyOf(Block block) {
            if (block == null) {
                return null;
            }
            return block.getBody();
        }

        void setEOP() {
            Block older = this.eop;
            if (older == null) {
                ByteBody body = new ByteBody();
                this.eop = Block.create(BlockGroup.COMMON, BlockField.COMMON_EOP, body);
            }
        }

        void setVersion(ProtocolVersion ver) {
            if (ver != null) {
                Uint16Body body = new Uint16Body();
                body.setValue((short) ver.toInt());
                this.version = Block.create(BlockGroup.COMMON, BlockField.COMMON_VERSION, body);
            }
        }

        void setTransaction(TransactionID tid) {
            if (tid != null) {
                Uint32Body body = new Uint32Body();
                body.setValue(tid.toInt());
                this.transaction = Block.create(BlockGroup.COMMON, BlockField.COMMON_TRANSACTION_ID, body);
            }
        }

        void setMethod(Method m) {
            if (m != null) {
                Uint8Body body = new Uint8Body();
                body.setValue((byte) Method.toInt(m));
                this.method = Block.create(BlockGroup.COMMON, BlockField.COMMON_METHOD, body);
            }
        }

        void setLocation(Location l) {
            if (l != null) {
                StringBody body = new StringBody();
                body.setValue(l.toString());
                this.location = Block.create(BlockGroup.COMMON, BlockField.COMMON_LOCATION, body);
            }
        }

        void setCode(Status s) {
            if (s != null) {
                Uint16Body body = new Uint16Body();
                body.setValue((short) s.getCode());
                this.code = Block.create(BlockGroup.COMMON, BlockField.COMMON_STATUS_CODE, body);
            }
        }

        void setMessage(Status s) {
            if (s != null) {
                StringBody body = new StringBody();
                body.setValue(s.getMessage());
                this.message = Block.create(BlockGroup.COMMON, BlockField.COMMON_STATUS_MESSAGE, body);
            }
        }

        Status getStatus() {

            BlockBody body;

            // code
            body = bodyOf(this.code);
            int _code = BlockTypeAdapter.getInt16(body);

            // msg
            body = bodyOf(this.message);
            String _msg = BlockTypeAdapter.getString(body);

            return new Status(_code, _msg);
        }

        ProtocolVersion getVersion() {
            final Block block = this.version;
            final BlockBody body = bodyOf(block);
            int n = BlockTypeAdapter.getInt16(body);
            return new ProtocolVersion(n);
        }

        TransactionID getTransaction() {
            final Block block = this.transaction;
            final BlockBody body = bodyOf(block);
            int n = BlockTypeAdapter.getInt32(body);
            return new TransactionID(n);
        }
    }

    private static List<Block> listAllBlocks(BlockHolder holder) {

        final List<Block> oth = holder.others;
        final List<Block> dst = new ArrayList<>();
        final List<Block> tmp = new ArrayList<>();

        tmp.add(holder.version);
        tmp.add(holder.method);
        tmp.add(holder.location);
        tmp.add(holder.code);
        tmp.add(holder.message);
        tmp.add(holder.transaction);
        if (oth != null) {
            tmp.addAll(oth);
        }
        tmp.add(holder.eop);

        for (Block b : tmp) {
            if (b == null) {
                continue;
            }
            dst.add(b);
        }
        return dst;
    }

    private static Block scanOnBlock(Block b, BlockHolder holder) {

        if (b == null) {
            return null;
        }

        // BlockGroup g = b.getHead().getGroup();
        BlockField f = b.getHead().getField();

        if (f == null) {
            return null;

        } else if (f.equals(BlockField.COMMON_METHOD)) {
            holder.method = b;

        } else if (f.equals(BlockField.COMMON_LOCATION)) {
            holder.location = b;

        } else if (f.equals(BlockField.COMMON_STATUS_CODE)) {
            holder.code = b;

        } else if (f.equals(BlockField.COMMON_STATUS_MESSAGE)) {
            holder.message = b;

        } else if (f.equals(BlockField.COMMON_VERSION)) {
            holder.version = b;

        } else if (f.equals(BlockField.COMMON_TRANSACTION_ID)) {
            holder.transaction = b;

        } else if (f.equals(BlockField.COMMON_EOP)) {
            holder.eop = b;

        } else {
            return b; // others
        }
        return null;
    }

    private static void scanBlocks(final List<Block> blocks, BlockHolder holder) {

        if (blocks == null || holder == null) {
            return;
        }

        final List<Block> others2 = new ArrayList<>();
        for (Block b : blocks) {
            b = scanOnBlock(b, holder);
            if (b == null) {
                continue;
            }
            others2.add(b);
        }
        holder.others.clear();
        holder.others.addAll(others2);
    }

}
