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

import org.json.JSONObject;

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
        LogD("logEvent(" + eventId + ") invoked!");
        MobclickAgent.onEvent(mContext, eventId);
    }

    @Override
    public void logEvent(String eventId, Hashtable<String, String> paramMap) {
        LogD("logEvent(" + eventId + "," + paramMap.toString() + ") invoked!");
        HashMap<String, String> curParam = changeTableToMap(paramMap);
        MobclickAgent.onEvent(mContext, eventId, curParam);
    }

    @Override
    public void logTimedEventBegin(String eventId) {
        LogD("logTimedEventBegin(" + eventId + ") invoked!");
        MobclickAgent.onEventBegin(mContext, eventId);
    }

    @Override
    public void logTimedEventEnd(String eventId) {
        LogD("logTimedEventEnd(" + eventId + ") invoked!");
        MobclickAgent.onEventEnd(mContext, eventId);
    }

    @Override
    public String getSDKVersion() {
        LogD("getSDKVersion invoked!");
        return "UMeng no version info";
    }

    protected String getConfigParams(String key) {
        LogD("getConfigParams(" + key + ") invoked!");
        if (!isValid()) return null;
        String ret = "";
        try{
            ret = MobclickAgent.getConfigParams(mContext, key);
        } catch(Exception e){
            LogE("Exception in logTimedEventBegin", e);
        }
        LogD("get config : " + ret);
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

    protected void logEventWithLabel(JSONObject eventInfo) {
        LogD("logEventWithLabel invoked! event : " + eventInfo.toString());
        if (!isValid()) return;
        try{
            String eventId = eventInfo.getString("Param1");
            String label = eventInfo.getString("Param2");
            MobclickAgent.onEvent(mContext, eventId, label);
        } catch(Exception e){
            LogE("Exception in logEventWithLabel", e);
        }
    }
    
    protected void logEventWithDurationLabel(JSONObject eventInfo) {
        LogD("logEventWithDurationLabel invoked! event : " + eventInfo.toString());
        if (!isValid()) return;
        try {
            String eventId = eventInfo.getString("Param1");
            int duration = eventInfo.getInt("Param2");
            if (eventInfo.has("Param3")) {
                String label = eventInfo.getString("Param3");
                MobclickAgent.onEventDuration(mContext, eventId, label, duration);
            } else {
                MobclickAgent.onEventDuration(mContext, eventId, duration);
            }
        } catch (Exception e) {
            LogE("Exception in logEventWithDurationLabel", e);
        }
    }

    protected void logEventWithDurationParams(JSONObject eventInfo) {
        LogD("logEventWithDurationParams invoked! event : " + eventInfo.toString());
        if (!isValid()) return;
        try {
            String eventId = eventInfo.getString("Param1");
            int duration = eventInfo.getInt("Param2");
            if (eventInfo.has("Param3")) {
                JSONObject params = eventInfo.getJSONObject("Param3");
                HashMap<String, String> curMap = getMapFromJson(params);
                MobclickAgent.onEventDuration(mContext, eventId, curMap, duration);
            } else {
                MobclickAgent.onEventDuration(mContext, eventId, duration);
            }
        } catch (Exception e) {
            LogE("Exception in logEventWithDurationParams", e);
        }
    }

    protected void logEventWithDuration(JSONObject eventInfo) {
        LogD("logEventWithDuration invoked! event : " + eventInfo.toString());
        if (!isValid()) return;
        try{
            String eventId = eventInfo.getString("Param1");
            int duration = eventInfo.getInt("Param2");
            MobclickAgent.onEventDuration(mContext, eventId, duration);
        } catch(Exception e){
            LogE("Exception in logEventWithDuration", e);
        }
    }

    protected void logTimedEventWithLabelBegin(JSONObject eventInfo) {
        LogD("logTimedEventWithLabelBegin invoked! event : " + eventInfo.toString());
        if (!isValid()) return;
        try{
            String eventId = eventInfo.getString("Param1");
            String label = eventInfo.getString("Param2");
            MobclickAgent.onEventBegin(mContext, eventId, label);
        } catch(Exception e){
            LogE("Exception in logTimedEventWithLabelBegin", e);
        }
    }
    
    protected void logTimedEventWithLabelEnd(JSONObject eventInfo) {
        LogD("logTimedEventWithLabelEnd invoked! event : " + eventInfo.toString());
        if (!isValid()) return;
        try{
            String eventId = eventInfo.getString("Param1");
            String label = eventInfo.getString("Param2");
            MobclickAgent.onEventEnd(mContext, eventId, label);
        } catch(Exception e){
            LogE("Exception in logTimedEventWithLabelEnd", e);
        }
    }
    
    protected void logTimedKVEventBegin(JSONObject eventInfo) {
        LogD("logTimedKVEventBegin invoked! event : " + eventInfo.toString());
        if (!isValid()) return;
        try{
            String eventId = eventInfo.getString("Param1");
            String label = eventInfo.getString("Param2");
            JSONObject params = eventInfo.getJSONObject("Param3");
            
            if (params != null) {
                HashMap<String, String> curMap = getMapFromJson(params);
                MobclickAgent.onKVEventBegin(mContext, eventId, curMap, label);
            }
        } catch(Exception e){
            LogE("Exception in logTimedKVEventBegin", e);
        }
    }
    
    protected void logTimedKVEventEnd(JSONObject eventInfo) {
        LogD("logTimedKVEventEnd invoked! event : " + eventInfo.toString());
        if (!isValid()) return;
        try{
            String eventId = eventInfo.getString("Param1");
            String label = eventInfo.getString("Param2");
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

    private HashMap<String, String> getMapFromJson(JSONObject json) {
        HashMap<String, String> curMap = new HashMap<String, String>();
        try {
            @SuppressWarnings("rawtypes")
            Iterator it = json.keys();
            while (it.hasNext()) {
                String key = (String) it.next();
                String value = json.getString(key);
                curMap.put(key, value);
            }
        } catch (Exception e) {
            LogE("Error when get HashMap from JSONObject", e);
        }

        return curMap;
    }

    @Override
    public String getPluginVersion() {
        return "0.2.0";
    }
}
