package com.github.xushifu.mls.client.nativeapp;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.github.xushifu.mls.client.gui.MLSClientGUI;

public final class MLSClientNative {

   private static final Logger logger = LoggerFactory.getLogger(MLSClientNative.class);

   public static void main(String[] args) {
      logger.info("hello, " + MLSClientNative.class);
      MLSClientGUI.main(args);
   }

}
