package com.github.xushifu.mls.client.gui.frames;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.FlowLayout;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import com.bitwormhole.starter4j.application.ApplicationContext;
import com.bitwormhole.starter4j.application.tasks.Promise;
import com.bitwormhole.starter4j.application.tasks.PromiseContext;
import com.bitwormhole.starter4j.application.tasks.Result;
import com.bitwormhole.starter4j.swing.FrameRegistration;
import com.bitwormhole.starter4j.swing.Goal;
import com.github.xushifu.mls.client.MLSClientServices;
import com.github.xushifu.mls.client.core.leds.LEDService;
import com.github.xushifu.mls.client.core.leds.LEDState;
import com.github.xushifu.mls.client.core.leds.LEDStateBuffer;
import com.github.xushifu.mls.client.gui.SwingClientContext;
import com.github.xushifu.mls.client.gui.utils.Colors;
import com.github.xushifu.mls.client.gui.widgets.LedStateView;

public class LedMonitorFrame extends JFrame {

    private final Goal mGoal;

    private final LedStateView[] mLedViews;
    private final JButton mButtonPush = new JButton("Push");
    private final JButton mButtonPull = new JButton("Pull");
    private final JButton mButtonRefresh = new JButton("Refresh");

    private LedMonitorFrame(Goal goal) {
        int count = 128;
        LedStateView[] list = new LedStateView[count];

        this.mGoal = goal;
        this.mLedViews = list;
    }

    private SwingClientContext getSwingClientContext() {
        ApplicationContext ac = this.mGoal.getContext();
        return SwingClientContext.getInstance(ac);
    }

    private static LedMonitorFrame create(Goal goal) {
        LedMonitorFrame f = new LedMonitorFrame(goal);
        f.onCreate();
        return f;
    }

    private void onCreate() {
        String title = this.getClass().getName();
        this.setTitle(title);
        this.setSize(600, 360);

        this.onCreateLayout();
        this.onCreateBindData();

        this.mButtonPush.addActionListener((ae) -> onClickButtonPush());
        this.mButtonPull.addActionListener((ae) -> onClickButtonPull());
        this.mButtonRefresh.addActionListener((ae) -> onClickButtonRefresh());
    }

    private void onCreateBindData() {

        final SwingClientContext scc = this.getSwingClientContext();
        final MLSClientServices services = scc.getClient().getServices();
        final LEDStateBuffer buffer = services.getLEDService().getStateBuffer();
        final LEDState[] state_list = buffer.getDiodes();
        final LedStateView[] view_list = this.mLedViews;
        final int count = Math.min(state_list.length, view_list.length);

        for (int i = 0; i < count; i++) {
            LEDState state = state_list[i];
            LedStateView view = view_list[i];
            state.setIndex(i);
            view.setState(state);
            view.updateUI();
        }
    }

    private void onCreateLayout() {

        final JPanel p1 = new JPanel();
        final JPanel p2 = new JPanel();

        this.setLayout(new BorderLayout());
        p1.setLayout(new FlowLayout());
        p2.setLayout(new FlowLayout());

        LedStateView[] list = this.mLedViews;
        for (int i = 0; i < list.length; ++i) {
            LedStateView view = new LedStateView();
            list[i] = view;
            p2.add(view);
        }
        p1.add(this.mButtonPush);
        p1.add(this.mButtonPull);
        p1.add(this.mButtonRefresh);
        this.add(p1, BorderLayout.NORTH);
        this.add(p2, BorderLayout.CENTER);
    }

    private void onClickButtonRefresh() {
        final SwingClientContext scc = this.getSwingClientContext();
        final MLSClientServices services = scc.getClient().getServices();
        this.checkout(services);
    }

    private void onClickButtonPull() {

        final SwingClientContext scc = this.getSwingClientContext();
        final PromiseContext pc = scc.getPromiseContext();
        final MLSClientServices services = scc.getClient().getServices();
        final LEDService.FetchOptions opt = new LEDService.FetchOptions();

        opt.partPosition = 0;
        opt.partSize = 128;

        final JDialog dlg = this.displayWorkingDialog("fetching ...");

        Promise.init(pc, Long.class).Try(() -> {
            services.getLEDService().fetch(opt);
            return new Result<>(Long.valueOf(0));
        }).Then((res) -> {
            this.onPullOK(services);
            return res;
        }).Catch((res) -> {
            displayErrorDialog(res.getError());
            return res;
        }).Finally((res) -> {
            dlg.dispose();
            return res;
        }).start();

    }

    private void onPullOK(MLSClientServices services) {
        this.checkout(services);
    }

    private void checkout(MLSClientServices services) {

        // final LEDStateBuffer buffer = services.getLEDService().getStateBuffer();
        // final LEDState[] src = buffer.getDiodes();
        // final int count = Math.min(src.length, dst.length);

        final LedStateView[] vlist = this.mLedViews;

        // for (int i = 0; i < count; ++i) {
        // LEDState data1 = src[i];
        // LedStateView view = dst[i];
        // if (data1 == null || view == null) {
        // continue;
        // }
        // LedStateView.Data data2 = view.getData();
        // Color colorRx = Colors.toColor(data1.getRx());
        // Color colorTx = Colors.toColor(data1.getTx());
        // data2.colorRx = colorRx;
        // data2.colorMx = colorRx;
        // data2.colorTx = colorTx;

        // view.updateUI();
        // }

        for (LedStateView view : vlist) {
            view.updateUI();
        }
    }

    private void onPushPreparing(MLSClientServices services) {

        // final LEDStateBuffer buffer = services.getLEDService().getStateBuffer();
        // final LEDState[] dst = buffer.getDiodes();
        // final LedStateView[] src = this.mLedViews;
        // final int count = Math.min(dst.length, src.length);

        // for (int i = 0; i < count; i++) {
        // LedStateView view = src[i];
        // LEDState state = dst[i];
        // Color color = view.getData().colorTx;
        // state.setTx(Colors.toARGB(color));
        // }
    }

    private void onPushOK() {
    }

    private JDialog displayWorkingDialog(String msg) {
        String title = "Wait ...";
        JOptionPane op = new JOptionPane(msg, JOptionPane.PLAIN_MESSAGE);
        JDialog dlg = op.createDialog(this, title);
        // dlg.setVisible(true);
        dlg.setModal(false);
        return dlg;
    }

    private void displayErrorDialog(Throwable err) {
        if (err == null) {
            return;
        }
        String msg = err.getMessage();
        String title = "Error";
        JOptionPane.showMessageDialog(this, msg, title, JOptionPane.ERROR_MESSAGE);
    }

    private void onClickButtonPush() {

        final SwingClientContext scc = this.getSwingClientContext();
        final PromiseContext pc = scc.getPromiseContext();
        final MLSClientServices services = scc.getClient().getServices();
        final LEDService.PushOptions opt = new LEDService.PushOptions();

        this.onPushPreparing(services);

        opt.viewPosition = 0;
        opt.viewSize = 128;
        opt.addPart(0, 128);

        final JDialog dlg = this.displayWorkingDialog("pushing ...");

        Promise.init(pc, Long.class).Try(() -> {
            services.getLEDService().push(opt);
            return new Result<>(Long.valueOf(0));
        }).Then((res) -> {
            return res;
        }).Catch((res) -> {
            displayErrorDialog(res.getError());
            return res;
        }).Finally((res) -> {
            dlg.dispose();
            return res;
        }).start();
    }

    public static FrameRegistration registration() {
        FrameRegistration fr = new FrameRegistration();
        fr.setType(LedMonitorFrame.class);
        fr.setFactory((g) -> create(g));
        return fr;
    }

    private void updateUI() {
    }

    public void push() {
    }

    public void pull() {
        this.updateUI();
    }

}
