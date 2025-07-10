package com.github.xushifu.mls.client.gui.config;

import java.util.List;

import com.bitwormhole.starter4j.application.ComponentRegistryFunc;
import com.bitwormhole.starter4j.application.ComponentTemplate;
import com.bitwormhole.starter4j.application.ComponentTemplate.RegistrationT;
import com.bitwormhole.starter4j.swing.FrameRegistration;
import com.bitwormhole.starter4j.swing.FrameRegistry;
import com.github.xushifu.mls.client.gui.frames.LoginFrame;
import com.github.xushifu.mls.client.gui.frames.PianoFrame;
import com.github.xushifu.mls.client.gui.frames.CanvasKeyboardFrame;
import com.github.xushifu.mls.client.gui.frames.HomeFrame;
import com.github.xushifu.mls.client.gui.frames.LedMonitorFrame;
import com.github.xushifu.mls.client.gui.frames.PingFrame;

// 这个类负责把所有的 frames 注册到 FrameManager
final class ConfigFrames {

    private static class MyFramesReg implements FrameRegistry {

        @Override
        public List<FrameRegistration> listRegistrations(List<FrameRegistration> list) {

            list.add(LoginFrame.registration());
            list.add(HomeFrame.registration());
            list.add(PingFrame.registration());
            list.add(LedMonitorFrame.registration());
            list.add(PianoFrame.registration());
            list.add(CanvasKeyboardFrame.registration());

            return list;
        }
    }

    public static ComponentRegistryFunc registerFunc() {
        return (cr) -> {
            final ComponentTemplate ct = new ComponentTemplate(cr);
            RegistrationT<MyFramesReg> rt = ct.component(MyFramesReg.class);
            rt.setId(MyFramesReg.class);
            rt.addClass("jframe");
            rt.onNew(() -> new MyFramesReg());
            rt.onInject((ie, inst) -> {
            });
            rt.register();
        };
    }
}
