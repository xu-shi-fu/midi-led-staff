package com.github.xushifu.mls.network.mlscp;

import java.io.Closeable;
import java.io.IOException;
import java.net.InetSocketAddress;

import org.junit.Test;

import com.github.xushifu.mls.utils.IOUtils;
import com.github.xushifu.mls.utils.TimeUtils;

public final class TestingUserAgentHolder implements Closeable {

    private UserAgent useragent;

    public UserAgent open() throws IOException {

        final String host = "192.168.0.104";

        UserAgent cl = this.useragent;
        if (cl != null) {
            return cl;
        }

        UserAgentBuilder builder = UserAgentBuilder.newInstance();
        builder.setRemote(InetSocketAddress.createUnresolved(host, 7923));
        builder.setLocal(InetSocketAddress.createUnresolved("0.0.0.0", 7928));
        builder.setTimeout(300 * 1000);
        cl = builder.open();

        this.useragent = cl;
        return cl;
    }

    @Override
    public void close() throws IOException {

        TimeUtils.sleep(6 * 1000);

        final UserAgent cl = this.useragent;
        this.useragent = null;
        if (cl == null) {
            return;
        }

        try {
            IOUtils.close(cl);
            cl.join();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

    @Test
    public void testUserAgent() throws Exception {
        TestingUserAgentHolder holder = new TestingUserAgentHolder();
        try {

            UserAgent cl = holder.open();
            Request req = cl.createNewRequest();

            req.setMethod(Method.GET);
            req.setLocation(Location.PING);

            cl.getDispatcher().dispatch(req.getContext());

        } finally {
            IOUtils.close(holder);
        }
    }

}
