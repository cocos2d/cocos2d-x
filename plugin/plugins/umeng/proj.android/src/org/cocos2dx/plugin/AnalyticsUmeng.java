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

import java.util.HashMap;
import java.util.Hashtable;
import java.util.Iterator;

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
		MobclickAgent.setWrapper("Cocos2d-x", "1.0");
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
		HashMap<String, String> curParam = changeTableToMap(paramMap);
		MobclickAgent.onEvent(mContext, eventId, curParam);
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
			HashMap<String, String> curMap = changeTableToMap(paramMap);
			MobclickAgent.onEventDuration(mContext, eventId, curMap, duration);
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
			HashMap<String, String> curMap = changeTableToMap(paramMap);
			MobclickAgent.onKVEventBegin(mContext, eventId, curMap, label);
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

	private HashMap<String, String> changeTableToMap(Hashtable<String, String> param) {
		HashMap<String, String> retParam = new HashMap<String, String>();
		for(Iterator<String> it = param.keySet().iterator(); it.hasNext(); ) {   
            String key = it.next();
            String value = param.get(key);

            retParam.put(key, value);
        }

		return retParam;
	}
}
