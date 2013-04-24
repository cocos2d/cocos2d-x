package org.cocos2dx.plugin;

import java.util.Hashtable;

import org.cocos2dx.plugin.InterfaceSocial.ShareAdapter;
import org.cocos2dx.plugin.TwitterApp.TwDialogListener;

import android.app.Activity;
import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.util.Log;

public class SocialTwitter implements ShareAdapter {

	private static final String LOG_TAG = "SocialTwitter";
	private static Activity mContext = null;
	protected static boolean bDebug = false;
	private static String CONSUMER_KEY="";
	private static String CONSUMER_SECRET="";
	
	private static TwitterApp mTwitter = null;
	private static boolean isInitialized = false;
	private static Hashtable<String, String> mShareInfo = null;
	
	public static String KEY_TEXT="text";
	public static String KEY_IMAGE_PATH = "imagePath";

	protected static void LogE(String msg, Exception e) {
		Log.e(LOG_TAG, msg, e);
		e.printStackTrace();
	}

	protected static void LogD(String msg) {
		if (bDebug) {
			Log.d(LOG_TAG, msg);
		}
	}

	public SocialTwitter(Context context) {
		mContext = (Activity) context;
	}
	

	@Override
	public void initDeveloperInfo(Hashtable<String, String> cpInfo) {
		LogD("initDeveloperInfo invoked " + cpInfo.toString());
		mShareInfo = cpInfo;
		mShareInfo = cpInfo;
		try {
			SocialTwitter.CONSUMER_KEY = cpInfo.get("consumerkey");
			SocialTwitter.CONSUMER_SECRET = cpInfo.get("consumersecret");
			if(isInitialized){
				return;
			}
			isInitialized = true;	
			PluginWrapper.runOnMainThread(new Runnable() {
				
				@Override
				public void run() {
					mTwitter =  new TwitterApp(PluginWrapper.getContext(), SocialTwitter.CONSUMER_KEY, SocialTwitter.CONSUMER_SECRET);
					mTwitter.setListener(mTwLoginDialogListener);
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
			shareResult(InterfaceSocial.SHARERESULT_FAIL, "网络不可用");
			return;
		}
		// need login
		if(!mTwitter.hasAccessToken()){
			PluginWrapper.runOnMainThread(new Runnable() {
				
				@Override
				public void run() {
					mTwitter.authorize();
				}
			});

			return;
		}
		
		PluginWrapper.runOnMainThread(new Runnable() {
			
			@Override
			public void run() {
				String text = mShareInfo.get(KEY_TEXT);
				String imagePath = mShareInfo.get(KEY_IMAGE_PATH);				
				try {
					if(imagePath != null && imagePath.length() > 0){
						mTwitter.updateStatus(text, imagePath);
					}else{
						mTwitter.updateStatus(text);	
					}
					LogD("Posted to Twitter!");
					shareResult(InterfaceSocial.SHARERESULT_SUCCESS, "user lihex");
				} catch (Exception e) {
					LogD("Post to Twitter failed!");
					shareResult(InterfaceSocial.SHARERESULT_FAIL, "user lihex");
					e.printStackTrace();
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

	private static void shareResult(int ret, String msg) {
		InterfaceSocial.shareResult(ret, msg);
		LogD("SocialTwitter result : " + ret + " msg : " + msg);
	}

	private static final TwDialogListener mTwLoginDialogListener = new TwDialogListener() {
		
		@Override
		public void onError(int flag, String value) {
			LogD("Twitter connection failed!");
			shareResult(InterfaceSocial.SHARERESULT_FAIL, value);			
		}
		
		@Override
		public void onComplete(String value) {
			String username = mTwitter.getUsername();
			LogD("Connected to Twitter as" + username);
			String text = mShareInfo.get(KEY_TEXT);
			String imagePath = mShareInfo.get(KEY_IMAGE_PATH);	
			try {
				if(imagePath != null && imagePath.length() > 0){
					mTwitter.updateStatus(text, imagePath);
				}else{
					mTwitter.updateStatus(text);	
				}
				LogD("Posted to Twitter!");
				shareResult(InterfaceSocial.SHARERESULT_SUCCESS, username);
			} catch (Exception e) {
				LogD("Post to Twitter failed!");
				shareResult(InterfaceSocial.SHARERESULT_FAIL, username);
				e.printStackTrace();
			}
		}
	};
}
