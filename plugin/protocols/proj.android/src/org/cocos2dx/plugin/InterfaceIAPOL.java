package org.cocos2dx.plugin;

import java.util.Hashtable;

public class InterfaceIAPOL {
	
	public interface IAPOLAdapter {
		public void initDeveloperInfo(Hashtable<String, String> cpInfo);
		public void payForProduct(Hashtable<String, String> cpInfo);
		public void setDebugMode(boolean debug);
		public String getSDKVersion();
	}

	public static void payFailedLocally(int ret, String msg) {
		final int curRet = ret;
		final String curMsg = msg;
		PluginWrapper.runOnGLThread(new Runnable() {
			@Override
			public void run() {
				nativePayFailedLocally(curRet, curMsg);
			}
		});
	}
	private static native void nativePayFailedLocally(int ret, String msg);
}
