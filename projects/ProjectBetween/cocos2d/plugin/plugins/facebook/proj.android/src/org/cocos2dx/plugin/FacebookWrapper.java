package org.cocos2dx.plugin;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

import com.facebook.AppEventsLogger;
import com.facebook.UiLifecycleHelper;
import com.facebook.widget.FacebookDialog;
import com.facebook.widget.FacebookDialog.PendingCall;

public class FacebookWrapper {
	
	private static UiLifecycleHelper uiHelper = null;
	private static FacebookDialog.Callback dialogCallback = null;
	
	public static void setDialogCallback(FacebookDialog.Callback callback){
		dialogCallback = callback;
	}
	
	public static void onCreate(Activity activity){
		uiHelper = new UiLifecycleHelper(activity, null);
	}
	
	public static void onAcitivityResult(int requestCode, int resultCode, Intent data){
		uiHelper.onActivityResult(requestCode, resultCode, data, dialogCallback);
	}
	
	public static void onSaveInstanceState(Bundle outState) {
		uiHelper.onSaveInstanceState(outState);
	}
	
	public static void track(PendingCall pendingCall){
		uiHelper.trackPendingDialogCall(pendingCall);
	}
	
	public static AppEventsLogger getAppEventsLogger(){
		return uiHelper.getAppEventsLogger();
	}
}
