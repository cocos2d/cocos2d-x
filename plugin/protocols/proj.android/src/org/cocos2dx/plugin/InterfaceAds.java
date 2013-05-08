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

	public static final int RESULT_CODE_AdsReceived = 0;               // The ad is received
	public static final int RESULT_CODE_FullScreenViewShown = 1;       // The full screen advertisement shown
    public static final int RESULT_CODE_FullScreenViewDismissed = 2;   // The full screen advertisement dismissed
    public static final int RESULT_CODE_PointsSpendSucceed = 3;        // The points spend succeed
    public static final int RESULT_CODE_PointsSpendFailed = 4;         // The points spend failed
    public static final int RESULT_CODE_NetworkError = 5;              // Network error
    public static final int RESULT_CODE_UnknownError = 6;              // Unknown error

    public static final int ADS_TYPE_BANNER        = 0;
    public static final int ADS_TYPE_FULL_SCREEN   = 1;

	public static final int POS_CENTER 	     = 0;
	public static final int POS_TOP		     = 1;
	public static final int POS_TOP_LEFT     = 2;
	public static final int POS_TOP_RIGHT    = 3;
	public static final int POS_BOTTOM       = 4;
	public static final int POS_BOTTOM_LEFT  = 5;
	public static final int POS_BOTTOM_RIGHT = 6;

	public interface AdsAdapter {
		public void configDeveloperInfo(Hashtable<String, String> devInfo);
		public void showAds(int type, int sizeEnum, int pos);
		public void hideAds(int type);
		public void spendPoints(int points);
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
		case POS_CENTER:
			mLayoutParams.gravity = Gravity.CENTER;
			break;
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

	public static void onAdsResult(AdsAdapter adapter, int code, String msg) {
		final int curCode = code;
		final String curMsg = msg;
		final AdsAdapter curObj = adapter;
		PluginWrapper.runOnGLThread(new Runnable(){
			@Override
			public void run() {
				InterfaceAds.nativeOnAdsResult(curObj, curCode, curMsg);
			}
		});
	}
	private native static void nativeOnAdsResult(Object obj, int code, String msg);

	public static void onPlayerGetPoints(AdsAdapter adapter, int points) {
		final int curPoints = points;
		final AdsAdapter curAdapter = adapter;
		PluginWrapper.runOnGLThread(new Runnable(){
			@Override
			public void run() {
				InterfaceAds.nativeOnPlayerGetPoints(curAdapter, curPoints);
			}
		});
	}
	private native static void nativeOnPlayerGetPoints(Object obj, int points);
}
