package org.cocos2dx.plugin;

import java.util.Hashtable;

public class InterfaceIAP {
	public static final int PAYRESULT_SUCCESS = 0;
	public static final int PAYRESULT_FAIL    = 1;
	public static final int PAYRESULT_CANCEL  = 2;
	public static final int PAYRESULT_TIMEOUT = 3;

	public interface IAPAdapter {
		public void initDeveloperInfo(Hashtable<String, String> cpInfo);
		public void payForProduct(Hashtable<String, String> cpInfo);
		public void setDebugMode(boolean debug);
		public String getSDKVersion();
	}

	public static void payResult(int ret, String msg) {
		final int curRet = ret;
		final String curMsg = msg;
		PluginWrapper.runOnGLThread(new Runnable() {
			@Override
			public void run() {
				nativePayResult(curRet, curMsg);
			}
		});
	}
	private static native void nativePayResult(int ret, String msg);
}
