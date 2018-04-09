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
        final String curKey = appKey;
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                try {
                    Class.forName("android.os.AsyncTask");
                } catch (ClassNotFoundException e) {
                   e.printStackTrace();
                }
                FlurryAgent.onStartSession(mContext, curKey);
            }
            
        });
    }

    @Override
    public void stopSession() {
        LogD("stopSession invoked!");
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                FlurryAgent.onEndSession(mContext);
            }
        });
    }

    @Override
    public void setSessionContinueMillis(int millis) {
        LogD("setSessionContinueMillis invoked!");
        final int curMillis = millis;
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                FlurryAgent.setContinueSessionMillis(curMillis);
            }
        });
    }

    @Override
    public void setCaptureUncaughtException(boolean isEnabled) {
        LogD("setCaptureUncaughtException invoked!");
        final boolean curEnable = isEnabled;
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                FlurryAgent.setCaptureUncaughtExceptions(curEnable);
            }
        });
    }

    @Override
    public void setDebugMode(boolean isDebugMode) {
        isDebug = isDebugMode;
        final boolean curDebugMode = isDebug;
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                FlurryAgent.setLogEnabled(curDebugMode);
                if (curDebugMode) {
                    FlurryAgent.setLogLevel(Log.DEBUG);
                }
            }
        });
    }

    @Override
    public void logError(String errorId, String message) {
        LogD("logError invoked!");
        final String curID = errorId;
        final String curMsg = message;
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                FlurryAgent.onError(curID, curMsg, "");
            }
        });
    }

    @Override
    public void logEvent(String eventId) {
        LogD("logEvent(eventId) invoked!");
        final String curId = eventId;
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                FlurryAgent.logEvent(curId);
            }
        });
    }

    @Override
    public void logEvent(String eventId, Hashtable<String, String> paramMap) {
        LogD("logEvent(eventId, paramMap) invoked!");
        final String curId = eventId;
        final Hashtable<String, String> curParam = paramMap;
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                FlurryAgent.logEvent(curId, curParam);
            }
        });
    }

    @Override
    public void logTimedEventBegin(String eventId) {
        LogD("logTimedEventBegin invoked!");
        final String curId = eventId;
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                FlurryAgent.logEvent(curId, true);
            }
        });
    }

    @Override
    public void logTimedEventEnd(String eventId) {
        LogD("logTimedEventEnd invoked!");
        final String curId = eventId;
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                FlurryAgent.endTimedEvent(curId);
            }
        });
    }

    @Override
    public String getSDKVersion() {
        return "3.2.1";
    }

    protected void logTimedEventBeginWithParams(JSONObject eventInfo) {
        LogD("logTimedEventBegin invoked!");
        final JSONObject curInfo = eventInfo;
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                try{
                    String eventId = curInfo.getString("Param1");
                    
                    if (curInfo.has("Param2"))
                    {
                        JSONObject params = curInfo.getJSONObject("Param2");
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
        });
    }
    
    protected void setReportLocation(boolean enabled) {
        LogD("setReportLocation invoked!");
        final boolean curEnable = enabled;
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                try{
                    FlurryAgent.setReportLocation(curEnable);
                } catch(Exception e){
                    LogE("Exception in setReportLocation", e);
                }
            }
        });
    }
    
    protected void  logPageView() {
        LogD("logPageView invoked!");
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                try{
                    FlurryAgent.onPageView();
                } catch(Exception e){
                    LogE("Exception in logPageView", e);
                }
            }
        });
    }

    protected void setVersionName(String versionName) {
        LogD("setVersionName invoked!");
        final String curVer = versionName;
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                try {
                    FlurryAgent.setVersionName(curVer);
                } catch(Exception e){
                    LogE("Exception in setVersionName", e);
                }
            }
        });
    }
    
    protected void setAge(int age) {
        LogD("setAge invoked!");
        final int curAge = age;
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                try {
                    FlurryAgent.setAge(curAge);
                } catch(Exception e){
                    LogE("Exception in setAge", e);
                }
            }
        });
    }
    
    protected void setGender(int gender) {
        LogD("setGender invoked!");
        final int curGender = gender;
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                try {
                    byte bGender;
                    if (1 == curGender) {
                        bGender = Constants.MALE;
                    } else {
                        bGender = Constants.FEMALE;
                    }
                    FlurryAgent.setGender(bGender);
                } catch(Exception e){
                    LogE("Exception in setGender", e);
                }
            }
        });
    }
    
    protected void setUserId(String userId) {
        LogD("setUserId invoked!");
        final String curUser = userId;
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                try {
                    FlurryAgent.setUserId(curUser);
                } catch(Exception e){
                    LogE("Exception in setUserId", e);
                }
            }
        });
    }
    
    protected void setUseHttps(boolean useHttps) {
        LogD("setUseHttps invoked!");
        
        final boolean curCfg = useHttps;
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                try {
                    FlurryAgent.setUseHttps(curCfg);
                } catch(Exception e){
                    LogE("Exception in setUseHttps", e);
                }
            }
        });
    }

    @Override
    public String getPluginVersion() {
        return "0.2.0";
    }
}
