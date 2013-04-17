package org.cocos2dx.plugin;

import java.util.Hashtable;
import android.content.Context;
import android.util.Log;

import com.umeng.analytics.MobclickAgent;

public class AnalyticsUmeng implements InterfaceAnalytics{
	
	private Context mContext = null;
	
	protected static String TAG = "AnalyticsUmeng";
	
	protected static void LogE(String msg, Exception e) {
		Log.e(TAG, msg, e);
		e.printStackTrace();
	}

	private static boolean isDebug = true;
	protected static void LogD(String msg) {
		if (isDebug) {
			Log.d(TAG, msg);
		}
	}

	public AnalyticsUmeng(Context context) {
		mContext = context;
	}
	
	public boolean isValid() {
		return mContext != null;
	}
	@Override
	public void startSession(String appKey) {
		LogD("startSession invoked!");
		MobclickAgent.onResume(mContext);
	}

	@Override
	public void stopSession() {
		LogD("stopSession invoked!");
		MobclickAgent.onPause(mContext);
	}

	@Override
	public void setSessionContinueMillis(int millis) {
		LogD("setSessionContinueMillis invoked!");
		MobclickAgent.setSessionContinueMillis(millis);
	}

	@Override
	public void setCaptureUncaughtException(boolean isEnabled) {
		LogD("setCaptureUncaughtException invoked!");
		if (isEnabled) {
			MobclickAgent.onError(mContext);
		}
	}

	@Override
	public void setDebugMode(boolean isDebugMode) {
		isDebug = isDebugMode;
		MobclickAgent.setDebugMode(isDebugMode);
	}

	@Override
	public void logError(String errorId, String message) {
		LogD("logError invoked!");
		MobclickAgent.reportError(mContext, message);
	}

	@Override
	public void logEvent(String eventId) {
		LogD("logEvent(eventId) invoked!");
		MobclickAgent.onEvent(mContext, eventId);
	}

	@Override
	public void logEvent(String eventId, Hashtable<String, String> paramMap) {
		LogD("logEvent(eventId, paramMap) invoked!");
		MobclickAgent.onEvent(mContext, eventId, paramMap);
	}

	@Override
	public void logTimedEventBegin(String eventId) {
		LogD("logTimedEventBegin invoked!");
		MobclickAgent.onEventBegin(mContext, eventId);
	}

	@Override
	public void logTimedEventEnd(String eventId) {
		LogD("logTimedEventEnd invoked!");
		MobclickAgent.onEventEnd(mContext, eventId);
	}

	@Override
	public String getSDKVersion() {
		LogD("getSDKVersion invoked!");
		return "UMeng no version info";
	}

	protected String getConfigParams(String key) {
		LogD("getConfigParams invoked!");
		if (!isValid()) return null;
		String ret = "";
		try{
			ret = MobclickAgent.getConfigParams(mContext, key);
		} catch(Exception e){
			LogE("Exception in logTimedEventBegin", e);
		}
		return ret;
	}
	
	protected void updateOnlineConfig() {
		LogD("updateOnlineConfig invoked!");
		if (!isValid()) return;
		try{
			MobclickAgent.updateOnlineConfig(mContext);
		} catch(Exception e){
			LogE("Exception in updateOnlineConfig", e);
		}
	}
	
	protected void setDefaultReportPolicy(int policy) {
		LogD("setDefaultReportPolicy invoked!");
		if (!isValid()) return;
		try{
			MobclickAgent.setDefaultReportPolicy(mContext, policy);
		} catch(Exception e){
			LogE("Exception in setDefaultReportPolicy", e);
		}
	}
	
	protected void logEventWithLabel(String eventId, String label) {
		LogD("logEventWithLabel invoked!");
		if (!isValid()) return;
		try{
			MobclickAgent.onEvent(mContext, eventId, label);
		} catch(Exception e){
			LogE("Exception in logEventWithLabel", e);
		}
	}
	
	protected void logEventWithDuration(String eventId, int duration) {
		LogD("logEventWithDuration(eventId, duration) invoked!");
		if (!isValid()) return;
		try{
			MobclickAgent.onEventDuration(mContext, eventId, duration);
		} catch(Exception e){
			LogE("Exception in logEventWithDuration, eventId, duration", e);
		}
	}
	
	protected void logEventWithDuration(String eventId, int duration, String label) {
		LogD("logEventWithDuration(eventId, duration, label) invoked!");
		if (!isValid()) return;
		try{
			MobclickAgent.onEventDuration(mContext, eventId, label, duration);
		} catch(Exception e){
			LogE("Exception in logEventWithDuration, eventId, label, duration", e);
		}
	}
	
	protected void logEventWithDuration(String eventId, int duration, Hashtable<String, String> paramMap) {
		LogD("logEventWithDuration(eventId, duration, paramMap) invoked!");
		if (!isValid()) return;
		try{
			MobclickAgent.onEventDuration(mContext, eventId, paramMap, duration);
		} catch(Exception e){
			LogE("Exception in logEventWithDuration,eventId,duration,paramMap", e);
		}
	}
	
	protected void logTimedEventWithLabelBegin(String eventId, String label) {
		LogD("logTimedEventWithLabelBegin invoked!");
		if (!isValid()) return;
		try{
			MobclickAgent.onEventBegin(mContext, eventId, label);
		} catch(Exception e){
			LogE("Exception in logTimedEventWithLabelBegin", e);
		}
	}
	
	protected void logTimedEventWithLabelEnd(String eventId, String label) {
		LogD("logTimedEventWithLabelEnd invoked!");
		if (!isValid()) return;
		try{
			MobclickAgent.onEventEnd(mContext, eventId, label);
		} catch(Exception e){
			LogE("Exception in logTimedEventWithLabelEnd", e);
		}
	}
	
	protected void logTimedKVEventBegin(String eventId, String label, Hashtable<String, String> paramMap) {
		LogD("logTimedKVEventBegin invoked!");
		if (!isValid()) return;
		try{
			MobclickAgent.onKVEventBegin(mContext, eventId, paramMap, label);
		} catch(Exception e){
			LogE("Exception in logTimedKVEventBegin", e);
		}
	}
	
	protected void logTimedKVEventEnd(String eventId, String label) {
		LogD("logTimedKVEventEnd invoked!");
		if (!isValid()) return;
		try{
			MobclickAgent.onKVEventEnd(mContext, eventId, label);
		} catch(Exception e){
			LogE("Exception in logTimedKVEventEnd", e);
		}
	}
}
