package com.github.xushifu.mls.network.mlscp;

import java.util.List;

import com.github.xushifu.mls.network.mlscp.blocks.BodyAdapter;

public final class ResponseResolver {

    private ResponseResolver() {
    }

    public static void resolve(Response resp) {

        if (resp == null) {
            return;
        }
        final long now = System.currentTimeMillis();
        resp.setTimestamp(now);
        scanBlocks(resp);
    }

    private static void scanBlocks(Response resp) {
        List<Block> blocks = resp.getBlocks();
        for (Block block : blocks) {
            handleBlock(resp, block);
        }
    }

    private static void handleBlock(Response resp, Block block) {

        final BlockField field = block.getHead().getField();
        final BlockBody body = block.getBody();

        if (field.equals(BlockField.COMMON_VERSION)) {
            int n = BodyAdapter.getInt(body);
            resp.setVersion(new ProtocolVersion(n));

        } else if (field.equals(BlockField.COMMON_TRANSACTION_ID)) {
            int n = BodyAdapter.getInt(body);
            resp.getContext().setId(new TransactionID(n));

        } else if (field.equals(BlockField.COMMON_STATUS_CODE)) {
            Status status = getStatus(resp, true);
            int n = BodyAdapter.getInt(body);
            status.setCode(n);

        } else if (field.equals(BlockField.COMMON_STATUS_MESSAGE)) {
            Status status = getStatus(resp, true);
            String str = BodyAdapter.getString(body);
            status.setMessage(str);
        }
    }

    private static Status getStatus(Response resp, boolean auto_make) {
        Status status = resp.getStatus();
        if (status == null && auto_make) {
            status = new Status();
            resp.setStatus(status);
        }
        return status;
    }

}
