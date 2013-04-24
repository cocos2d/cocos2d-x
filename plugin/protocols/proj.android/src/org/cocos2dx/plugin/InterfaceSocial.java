package org.cocos2dx.plugin;

import java.util.Hashtable;

public class InterfaceSocial {
	public static final int SHARERESULT_SUCCESS = 0;
	public static final int SHARERESULT_FAIL    = 1;
	public static final int SHARERESULT_CANCEL  = 2;
	public static final int SHARERESULT_TIMEOUT = 3;

	public interface ShareAdapter {
		public void initDeveloperInfo(Hashtable<String, String> cpInfo);
		public void share(Hashtable<String, String> cpInfo);
		public void setDebugMode(boolean debug);
		public String getSDKVersion();
	}

	public static void shareResult(int ret, String msg) {
		final int curRet = ret;
		final String curMsg = msg;
		PluginWrapper.runOnGLThread(new Runnable() {
			@Override
			public void run() {
				nativeShareResult(curRet, curMsg);
			}
		});
	}
	private static native void nativeShareResult(int ret, String msg);
}
