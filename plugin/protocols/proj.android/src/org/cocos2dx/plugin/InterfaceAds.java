package org.cocos2dx.plugin;

import java.util.Hashtable;

import android.content.Context;
import android.view.Gravity;
import android.view.View;
import android.view.WindowManager;

public class InterfaceAds {
	public static final int UNKNOWN_ERROR = 0;
	public static final int NETWORK_ERROR = 1;
	public static final int REQUESTING_ERROR = 2;

	public static final int POS_TOP		     = 0;
	public static final int POS_TOP_LEFT     = 1;
	public static final int POS_TOP_RIGHT    = 2;
	public static final int POS_BOTTOM       = 3;
	public static final int POS_BOTTOM_LEFT  = 4;
	public static final int POS_BOTTOM_RIGHT = 5;

	public interface AdsAdapter {
		public void initAppInfo(Hashtable<String, String> appInfo);
		public void showBannerAd(int pos, int sizeEnum);
		public void hideBannerAd();
		public void setDebugMode(boolean debug);
		public String getSDKVersion();
	}

	public static void addAdView(WindowManager mWm, View adView, int pos) {
		WindowManager.LayoutParams mLayoutParams = new WindowManager.LayoutParams();
		mLayoutParams.type = WindowManager.LayoutParams.TYPE_APPLICATION_PANEL;
		mLayoutParams.width = WindowManager.LayoutParams.WRAP_CONTENT;
		mLayoutParams.height = WindowManager.LayoutParams.WRAP_CONTENT;
		mLayoutParams.flags |= WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
		
		switch (pos) {
		case POS_TOP:
			mLayoutParams.gravity = Gravity.TOP;
			break;
		case POS_TOP_LEFT:
			mLayoutParams.gravity = Gravity.TOP | Gravity.LEFT;
			break;
		case POS_TOP_RIGHT:
			mLayoutParams.gravity = Gravity.TOP | Gravity.RIGHT;
			break;
		case POS_BOTTOM:
			mLayoutParams.gravity = Gravity.BOTTOM;
			break;
		case POS_BOTTOM_LEFT:
			mLayoutParams.gravity = Gravity.BOTTOM | Gravity.LEFT;
			break;
		case POS_BOTTOM_RIGHT:
			mLayoutParams.gravity = Gravity.BOTTOM | Gravity.RIGHT;
			break;
		default:
			break;
		}
		mWm.addView(adView, mLayoutParams);
	}

	public static void receiveAd() {
		PluginWrapper.runOnGLThread(new Runnable(){
			@Override
			public void run() {
				InterfaceAds.nativeReceiveAd();
			}
		});
	}
	private native static void nativeReceiveAd();
	
	public static void presentScreen() {
		PluginWrapper.runOnGLThread(new Runnable(){
			@Override
			public void run() {
				InterfaceAds.nativePresentScreen();
			}
		});
	}
	private native static void nativePresentScreen();
	
	public static void failedToReceiveAd(int code, String msg) {
		final int eCode = code;
		final String eMsg = msg;
		PluginWrapper.runOnGLThread(new Runnable(){
			@Override
			public void run() {
				InterfaceAds.nativeFailedToReceiveAd(eCode, eMsg);
			}
		});
	}
	private native static void nativeFailedToReceiveAd(int code, String msg);
	
	public static void dismissScreen() {
		PluginWrapper.runOnGLThread(new Runnable(){
			@Override
			public void run() {
				InterfaceAds.nativeDismissScreen();
			}
		});
	}
	private native static void nativeDismissScreen();
}
