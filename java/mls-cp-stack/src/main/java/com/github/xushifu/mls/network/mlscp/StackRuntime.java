package com.github.xushifu.mls.network.mlscp;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.net.SocketException;
import java.util.ArrayList;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.github.xushifu.mls.utils.IOUtils;
import com.github.xushifu.mls.utils.TimeUtils;

public final class StackRuntime implements Runnable {

    private final static Logger logger = LoggerFactory.getLogger(StackRuntime.class);

    private final Stack stack;
    private Thread thread;
    private DatagramSocket socket;

    private boolean starting;
    private boolean started;
    private boolean stopped;
    private boolean stopping;

    public StackRuntime(Stack s) {
        this.stack = s;
    }

    public void start() {
        Thread th = new Thread(this);
        this.thread = th;
        this.starting = true;
        th.start();
    }

    public void stop() {
        this.stopping = true;
        Stopper st = new Stopper();
        Thread th = new Thread(st);
        th.start();
    }

    private final class Stopper implements Runnable {

        @Override
        public void run() {
            DatagramSocket sock = StackRuntime.this.socket;
            IOUtils.close(sock);
        }
    }

    public void join() throws InterruptedException {
        Thread th = this.thread;
        if (th == null) {
            return;
        }
        th.join();
    }

    @Override
    public void run() {
        try {
            this.run1();

        } catch (SocketException e) {
            if (!this.stopping) {
                e.printStackTrace();
            }
        } catch (Exception e) {
            e.printStackTrace();
            logger.error(this + ":error:", e);
        } finally {
            this.stopped = true;
            logger.info(this + ": stopped");
        }
    }

    private static InetSocketAddress resolveAddress(SocketAddress addr) {
        InetSocketAddress a2 = (InetSocketAddress) addr;
        String host = a2.getHostName();
        int port = a2.getPort();
        return new InetSocketAddress(host, port);
    }

    private void run1() throws IOException {

        InetSocketAddress local = resolveAddress(this.stack.local);
        InetSocketAddress remote = resolveAddress(this.stack.remote);

        this.stack.remote = remote;
        this.stack.local = local;
        DatagramSocket sock = new DatagramSocket(local);

        try {
            this.socket = sock;
            this.run2();
        } finally {
            IOUtils.close(sock);
        }
    }

    private void run2() throws IOException {

        byte[] buffer = new byte[1024 * 2];
        DatagramSocket sock = this.socket;
        DatagramPacket p = new DatagramPacket(buffer, buffer.length);

        logger.info("listen UDP at " + sock.getLocalSocketAddress());
        this.started = true;

        for (;;) {
            if (this.stopped || this.stopping) {
                break;
            }
            p.setData(buffer);
            sock.receive(p);
            this.handle1(p, sock);
        }
    }

    private void handle1(DatagramPacket pack, DatagramSocket sock) {
        try {
            this.handle2(pack, sock);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void handle2(DatagramPacket pack, DatagramSocket sock) throws Exception {

        TransactionContext ctx = new TransactionContext();
        Response resp = new Response(ctx);
        ByteArraySlice payload = new ByteArraySlice(pack.getData(), pack.getOffset(), pack.getLength());

        ctx.setResponse(resp);

        resp.setBlocks(new ArrayList<>());
        resp.setData(payload);
        resp.setRemote(pack.getSocketAddress());

        RxFilterChain chain = this.stack.rx;
        chain.receive(ctx);
    }

    public void waitUntilStarted(int timeout) {
        final int step = 1000;
        if (!this.starting) {
            throw new RuntimeException("waitUntilStarted: without starting");
        }
        for (;;) {
            if (timeout < 1) {
                throw new RuntimeException("waitUntilStarted: timeout");
            } else if (this.started) {
                break;
            } else if (this.stopped) {
                throw new RuntimeException("waitUntilStarted: stopped");
            }
            TimeUtils.sleep(step);
            timeout -= step;
        }
    }

    public DatagramSocket getSocket() {
        return socket;
    }

    public void setSocket(DatagramSocket socket) {
        this.socket = socket;
    }

}
