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
import java.util.Iterator;

import org.json.JSONObject;

import android.content.Context;
import android.util.Log;

import com.flurry.android.Constants;
import com.flurry.android.FlurryAgent;

public class AnalyticsFlurry implements InterfaceAnalytics {

    private Context mContext = null;
    protected static String TAG = "AnalyticsFlurry";

    protected static void LogE(String msg, Exception e) {
        Log.e(TAG, msg, e);
        e.printStackTrace();
    }

    private static boolean isDebug = false;
    protected static void LogD(String msg) {
        if (isDebug) {
            Log.d(TAG, msg);
        }
    }

    public AnalyticsFlurry(Context context) {
        mContext = context;
    }
    
    @Override
    public void startSession(String appKey) {
        LogD("startSession invoked!");
        FlurryAgent.onStartSession(mContext, appKey);
    }

    @Override
    public void stopSession() {
        LogD("stopSession invoked!");
        FlurryAgent.onEndSession(mContext);
    }

    @Override
    public void setSessionContinueMillis(int millis) {
        LogD("setSessionContinueMillis invoked!");
        FlurryAgent.setContinueSessionMillis(millis);
    }

    @Override
    public void setCaptureUncaughtException(boolean isEnabled) {
        LogD("setCaptureUncaughtException invoked!");
        FlurryAgent.setCaptureUncaughtExceptions(isEnabled);
    }

    @Override
    public void setDebugMode(boolean isDebugMode) {
        isDebug = isDebugMode;
        FlurryAgent.setLogEnabled(isDebug);
        if (isDebugMode) {
            FlurryAgent.setLogLevel(Log.DEBUG);
        }
    }

    @Override
    public void logError(String errorId, String message) {
        LogD("logError invoked!");
        FlurryAgent.onError(errorId, message, "");
    }

    @Override
    public void logEvent(String eventId) {
        LogD("logEvent(eventId) invoked!");
        FlurryAgent.logEvent(eventId);
    }

    @Override
    public void logEvent(String eventId, Hashtable<String, String> paramMap) {
        LogD("logEvent(eventId, paramMap) invoked!");
        FlurryAgent.logEvent(eventId, paramMap);
    }

    @Override
    public void logTimedEventBegin(String eventId) {
        LogD("logTimedEventBegin invoked!");
        FlurryAgent.logEvent(eventId, true);
    }

    @Override
    public void logTimedEventEnd(String eventId) {
        LogD("logTimedEventEnd invoked!");
        FlurryAgent.endTimedEvent(eventId);
    }

    @Override
    public String getSDKVersion() {
        return "3.2.0";
    }

    protected void logTimedEventBeginWithParams(JSONObject eventInfo) {
        LogD("logTimedEventBegin invoked!");
        try{
            String eventId = eventInfo.getString("Param1");
            
            if (eventInfo.has("Param2"))
            {
                JSONObject params = eventInfo.getJSONObject("Param2");
                @SuppressWarnings("rawtypes")
                Iterator it = params.keys();
                Hashtable<String, String> paramMap = new Hashtable<String, String>();
                while (it.hasNext()) {
                    String key = (String) it.next();
                    String value = params.getString(key);
                    paramMap.put(key, value);
                }
                FlurryAgent.logEvent(eventId, paramMap, true);
            } else {
                FlurryAgent.logEvent(eventId, true);
            }
        } catch(Exception e){
            LogE("Exception in logTimedEventBegin", e);
        }
    }
    
    protected void setReportLocation(boolean enabled) {
        LogD("setReportLocation invoked!");
        try{
            FlurryAgent.setReportLocation(enabled);
        } catch(Exception e){
            LogE("Exception in setReportLocation", e);
        }
    }
    
    protected void  logPageView() {
        LogD("logPageView invoked!");
        try{
            FlurryAgent.onPageView();
        } catch(Exception e){
            LogE("Exception in logPageView", e);
        }
    }

    protected void setVersionName(String versionName) {
        LogD("setVersionName invoked!");
        try {
            FlurryAgent.setVersionName(versionName);
        } catch(Exception e){
            LogE("Exception in setVersionName", e);
        }
    }
    
    protected void setAge(int age) {
        LogD("setAge invoked!");
        try {
            FlurryAgent.setAge(age);
        } catch(Exception e){
            LogE("Exception in setAge", e);
        }
    }
    
    protected void setGender(int gender) {
        LogD("setGender invoked!");
        try {
            byte bGender;
            if (1 == gender) {
                bGender = Constants.MALE;
            } else {
                bGender = Constants.FEMALE;
            }
            FlurryAgent.setGender(bGender);
        } catch(Exception e){
            LogE("Exception in setGender", e);
        }
    }
    
    protected void setUserId(String userId) {
        LogD("setUserId invoked!");
        try {
            FlurryAgent.setUserId(userId);
        } catch(Exception e){
            LogE("Exception in setUserId", e);
        }
    }
    
    protected void setUseHttps(boolean useHttps) {
        LogD("setUseHttps invoked!");
        try {
            FlurryAgent.setUseHttps(useHttps);
        } catch(Exception e){
            LogE("Exception in setUseHttps", e);
        }
    }

    @Override
    public String getPluginVersion() {
        return "0.2.0";
    }
}
