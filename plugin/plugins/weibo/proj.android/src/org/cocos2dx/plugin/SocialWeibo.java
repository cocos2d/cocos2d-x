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

import java.io.IOException;
import java.util.Hashtable;


import com.weibo.sdk.android.Oauth2AccessToken;
import com.weibo.sdk.android.Weibo;
import com.weibo.sdk.android.WeiboAuthListener;
import com.weibo.sdk.android.WeiboDialogError;
import com.weibo.sdk.android.WeiboException;
import com.weibo.sdk.android.api.StatusesAPI;
import com.weibo.sdk.android.net.RequestListener;

import android.app.Activity;
import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.util.Log;

public class SocialWeibo implements InterfaceSocial {

	private static final String LOG_TAG = "SocialWeibo";
	private static Activity mContext = null;
	private static SocialWeibo mSocialAdapter = null;
	protected static boolean bDebug = false;

	private String APP_KEY = "";
	private String REDIRECT_URL = "";

	private boolean isInitialized = false;
	private Hashtable<String, String> mShareInfo = null;

	public static final String KEY_TEXT="SharedText";
	public static final String KEY_IMAGE_PATH = "SharedImagePath";

	private Weibo mWeibo = null;
	private Oauth2AccessToken accessToken = null;

	protected static void LogE(String msg, Exception e) {
		Log.e(LOG_TAG, msg, e);
		e.printStackTrace();
	}

	protected static void LogD(String msg) {
		if (bDebug) {
			Log.d(LOG_TAG, msg);
		}
	}

	public SocialWeibo(Context context) {
		mContext = (Activity) context;
		mSocialAdapter = this;
	}

	@Override
	public void configDeveloperInfo(Hashtable<String, String> cpInfo) {
		LogD("configDeveloperInfo invoked " + cpInfo.toString());
		try {
			mSocialAdapter.APP_KEY = cpInfo.get("WeiboAppKey");
			mSocialAdapter.REDIRECT_URL = cpInfo.get("WeiboRedirectUrl");

			LogD("app key : " + mSocialAdapter.APP_KEY);
			LogD("redirect url : " + mSocialAdapter.REDIRECT_URL);
			if(isInitialized){
				return;
			}
			isInitialized = true;
			PluginWrapper.runOnMainThread(new Runnable() {
				
				@Override
				public void run() {
					mSocialAdapter.mWeibo = Weibo.getInstance(APP_KEY, REDIRECT_URL);
					mSocialAdapter.accessToken = AccessTokenKeeper.readAccessToken(mContext);
				}
			});
		} catch (Exception e) {
			LogE("Developer info is wrong!", e);
		}
	}

	@Override
	public void share(Hashtable<String, String> info) {
		LogD("share invoked " + info.toString());
		mShareInfo =  info;
		if (! networkReachable()) {
			shareResult(SocialWrapper.SHARERESULT_FAIL, "Network error!");
			return;
		}

		if (! isInitialized) {
			shareResult(SocialWrapper.SHARERESULT_FAIL, "Initialize failed!");
			return;
		}

		PluginWrapper.runOnMainThread(new Runnable() {
			@Override
			public void run() {
				if (mSocialAdapter.accessToken.isSessionValid()) {
					mSocialAdapter.shareToWeibo();
				} else {
					mSocialAdapter.mWeibo.authorize(mContext, new WeiboAuthDialogListener());
				}
			}
		});
	}

	@Override
	public void setDebugMode(boolean debug) {
		bDebug = debug;
	}

	@Override
	public String getSDKVersion() {
		return "Unknown version";
	}

	private boolean networkReachable() {
		boolean bRet = false;
		try {
			ConnectivityManager conn = (ConnectivityManager)mContext.getSystemService(Context.CONNECTIVITY_SERVICE);
			NetworkInfo netInfo = conn.getActiveNetworkInfo();
			bRet = (null == netInfo) ? false : netInfo.isAvailable();
		} catch (Exception e) {
			LogE("Fail to check network status", e);
		}
		LogD("NetWork reachable : " + bRet);
		return bRet;
	}

	public static void shareResult(int ret, String msg) {
		SocialWrapper.onShareResult(mSocialAdapter, ret, msg);
		LogD("SocialWeibo result : " + ret + " msg : " + msg);
	}

	class WeiboAuthDialogListener implements WeiboAuthListener {

        @Override
        public void onComplete(Bundle values) {
        	try {
                String token = values.getString("access_token");
                String expires_in = values.getString("expires_in");
                mSocialAdapter.accessToken = new Oauth2AccessToken(token, expires_in);
                AccessTokenKeeper.keepAccessToken(mContext, accessToken);

                mSocialAdapter.shareToWeibo();
        	} catch (Exception e) {
        		shareResult(SocialWrapper.SHARERESULT_FAIL, "认证失败!");
        		LogE("anthorize failed", e);
        	}
        }

        @Override
        public void onError(WeiboDialogError e) {
        	shareResult(SocialWrapper.SHARERESULT_FAIL, e.getMessage());
        }

        @Override
        public void onCancel() {
        	shareResult(SocialWrapper.SHARERESULT_FAIL, "取消认证!");
        }

        @Override
        public void onWeiboException(WeiboException e) {
        	shareResult(SocialWrapper.SHARERESULT_FAIL, e.getMessage());
        }
    }

	private void shareToWeibo() {
		String text = mShareInfo.get(KEY_TEXT);
		String imagePath = mShareInfo.get(KEY_IMAGE_PATH);
		StatusesAPI api = new StatusesAPI(accessToken);
		if (imagePath != null && imagePath.length() > 0) {
			api.upload(text, imagePath, "90.0", "90.0", new WeiboRequestListener());
		} else {
			api.update(text, "90.0", "90.0", new WeiboRequestListener());
		}
	}

	class WeiboRequestListener implements RequestListener {

		@Override
		public void onComplete(String arg0) {
			shareResult(SocialWrapper.SHARERESULT_SUCCESS, "分享成功!");
		}

		@Override
		public void onError(WeiboException arg0) {
			LogE("Share onError", arg0);
			shareResult(SocialWrapper.SHARERESULT_FAIL, "分享失败!");
		}

		@Override
		public void onIOException(IOException arg0) {
			LogE("Share onIOException", arg0);
			shareResult(SocialWrapper.SHARERESULT_FAIL, "分享失败!");
		}
	}

	@Override
	public String getPluginVersion() {
		return "0.2.0";
	}
}
