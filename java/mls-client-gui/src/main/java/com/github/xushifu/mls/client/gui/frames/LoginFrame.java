package com.github.xushifu.mls.client.gui.frames;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.awt.event.ActionEvent;

import com.bitwormhole.starter4j.application.tasks.Promise;
import com.bitwormhole.starter4j.application.tasks.PromiseContext;
import com.bitwormhole.starter4j.application.tasks.Result;
import com.bitwormhole.starter4j.swing.FrameManager;
import com.bitwormhole.starter4j.swing.FrameRegistration;
import com.bitwormhole.starter4j.swing.Goal;
import com.github.xushifu.mls.client.ClientContextHolder;
import com.github.xushifu.mls.client.MLSClient;
import com.github.xushifu.mls.client.MLSClientConfig;
import com.github.xushifu.mls.client.gui.SwingClientContext;

public class LoginFrame extends JFrame {

    private final static Logger logger = LoggerFactory.getLogger(LoginFrame.class);

    private final ClientContextHolder contextHolder;
    private final Goal goal;

    private LoginFrame(Goal g) {
        this.goal = g;
        this.contextHolder = ClientContextHolder.getInstance(g.getContext());
    }

    private void onCreate() {
        this.onCreateLayout();
    }

    private JButton mButtonConnect = new JButton("Connect");
    private JTextField mTextServerHost = new JTextField();
    private JTextField mTextServerPort = new JTextField();
    private JTextField mTextClientPort = new JTextField();
    private JLabel mLabelServerHost = new JLabel("Server Host");
    private JLabel mLabelServerPort = new JLabel("Server Port");
    private JLabel mLabelClientPort = new JLabel("Client Port");

    private void onCreateLayout() {

        JPanel panel = new JPanel();
        this.add(panel);

        BoxLayout layout = new BoxLayout(panel, BoxLayout.PAGE_AXIS);
        panel.setLayout(layout);

        panel.add(mLabelServerHost);
        panel.add(mTextServerHost);
        panel.add(mLabelServerPort);
        panel.add(mTextServerPort);
        panel.add(mLabelClientPort);
        panel.add(mTextClientPort);
        panel.add(mButtonConnect);

        mTextServerHost.setText("192.168.0.104"); // TODO: set default ip here ('.101' | '.104')
        mTextServerPort.setText("7923");
        mTextClientPort.setText("7921");

        mButtonConnect.addActionListener((ae) -> onClickConnect(ae));
    }

    private static int getIntValue(JTextField el) {
        String str = el.getText();
        return Integer.parseInt(str.trim());
    }

    private SwingClientContext getSwingClientContext() {
        return SwingClientContext.getInstance(this.contextHolder);
    }

    private void onClickConnect(ActionEvent ae) {
        final SwingClientContext scc = this.getSwingClientContext();
        final MLSClientConfig cfg = new MLSClientConfig();
        final PromiseContext pc = scc.getPromiseContext();

        cfg.setServerHost(mTextServerHost.getText());
        cfg.setServerPort(getIntValue(mTextServerPort));
        cfg.setClientPort(getIntValue(mTextClientPort));
        cfg.setTimeout(10000);

        final JDialog dlg = this.displayConnectingDialog();

        Promise.init(pc, MLSClient.class).Try(() -> {
            MLSClient client = MLSClient.open(cfg);
            scc.setClient(client);
            return new Result<>(client);
        }).Then((res) -> {
            logger.error("connect ok");
            this.displayHomeFrame();
            return res;
        }).Catch((res) -> {
            logger.error("connect err", res.getError());
            this.displayErrorInfo(res.getError());
            return res;
        }).Finally((res) -> {
            dlg.dispose();
            return res;
        }).start();
    }

    private void displayHomeFrame() {

        final SwingClientContext scc = this.getSwingClientContext();
        final FrameManager fm = scc.getFrameManager();
        final Goal goal = new Goal();

        goal.setContext(scc.getApplicationContext());
        goal.setFrameClass(HomeFrame.class);
        fm.show(goal);

        this.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        this.setVisible(false);
    }

    private void displayErrorInfo(Throwable err) {
        if (err == null) {
            return;
        }
        String msg = err.getMessage();
        String title = "Error";
        int type = JOptionPane.ERROR_MESSAGE;
        JOptionPane.showMessageDialog(this, msg, title, type);
    }

    private JDialog displayConnectingDialog() {

        String msg = "connecting ...";
        String title = "请稍侯";
        int type = JOptionPane.INFORMATION_MESSAGE;

        JOptionPane op = new JOptionPane(msg, type);
        JDialog dlg = op.createDialog(title);
        dlg.setModal(false);
        dlg.setVisible(true);
        return dlg;
    }

    private static LoginFrame createFrame(Goal goal) {
        LoginFrame f = new LoginFrame(goal);
        f.setTitle(f.getClass().getSimpleName());
        f.setSize(480, 360);
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.onCreate();
        return f;
    }

    public static FrameRegistration registration() {
        FrameRegistration fr = new FrameRegistration();
        fr.setType(LoginFrame.class);
        fr.setFactory((goal) -> createFrame(goal));
        return fr;
    }

}
