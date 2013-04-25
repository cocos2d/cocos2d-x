/****************************************************************************
Copyright (c) 2012-2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.plugin;

import java.util.Hashtable;

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
