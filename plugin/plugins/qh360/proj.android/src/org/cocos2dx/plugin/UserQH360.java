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

import org.json.JSONObject;

import com.qihoopay.insdk.activity.ContainerActivity;
import com.qihoopay.insdk.matrix.Matrix;
import com.qihoopay.sdk.protocols.IDispatcherCallback;
import com.qihoopay.sdk.protocols.ProtocolConfigs;
import com.qihoopay.sdk.protocols.ProtocolKeys;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.content.res.Configuration;
import android.os.Bundle;
import android.util.Log;

public class UserQH360 implements InterfaceUser {

    private static Context mContext = null;
    protected static String TAG = "UserQH360";
    private static InterfaceUser mAdapter = null;
    private String mAuthCode = "";
    private boolean mLogined = false;

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

    public UserQH360(Context context) {
        mContext = context;
        mAdapter = this;

        PluginWrapper.runOnMainThread(new Runnable() {

            @Override
            public void run() {
                Matrix.init((Activity) mContext, UserQH360.isLandscape(), new IDispatcherCallback() {
                    @Override
                    public void onFinished(String data) {
                    }
                });
            }
        });
    }

    @Override
    public void configDeveloperInfo(Hashtable<String, String> cpInfo) {
        LogD("Developer info should configed in AndroidManifest.xml");
    }

    @Override
    public void login() {
        if (isLogined()) {
            UserWrapper.onActionResult(mAdapter, UserWrapper.ACTION_RET_LOGIN_SUCCEED, "Already logined!");
            return;
        }

        // clear the auth code before
        mAuthCode = "";
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                Bundle bundle = new Bundle();
                bundle.putBoolean(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, isLandscape());
                bundle.putBoolean(ProtocolKeys.IS_LOGIN_BG_TRANSPARENT, true);
                bundle.putString(ProtocolKeys.RESPONSE_TYPE, "code");
                bundle.putInt(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_LOGIN);
                Intent intent = new Intent(mContext, ContainerActivity.class);
                intent.putExtras(bundle);
                Matrix.invokeActivity(mContext, intent, new IDispatcherCallback() {
                    @Override
                    public void onFinished(String data) {
                        LogD("Login callback data is " + data);

                        if (null == data) {
                            UserWrapper.onActionResult(mAdapter, UserWrapper.ACTION_RET_LOGIN_FAILED, "User Canceled");
                            return;
                        }

                        try {
                            JSONObject json = new JSONObject(data);
                            int errCode = json.optInt("error_code");
                            switch (errCode) {
                            case 0:
                                {
                                    mLogined = true;
                                    JSONObject content = json.optJSONObject("content");
                                    mAuthCode = content.optString("code");
                                    UserWrapper.onActionResult(mAdapter, UserWrapper.ACTION_RET_LOGIN_SUCCEED, "Login Succeed");
                                }
                                break;
                            default:
                                mLogined = false;
                                UserWrapper.onActionResult(mAdapter, UserWrapper.ACTION_RET_LOGIN_FAILED, "Login Failed");
                                break;
                            }
                        } catch (Exception e) {
                            mLogined = false;
                            e.printStackTrace();
                            UserWrapper.onActionResult(mAdapter, UserWrapper.ACTION_RET_LOGIN_FAILED, "Unknow Error");
                        }
                    }
                });
            }
        });
    }

    @Override
    public void logout() {
        if (! isLogined()) {
            LogD("User not logined!");
            return;
        }

        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                Bundle bundle = new Bundle();
                bundle.putBoolean(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, isLandscape());
                bundle.putInt(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_QUIT);
                Intent intent = new Intent(mContext, ContainerActivity.class);
                intent.putExtras(bundle);
                Matrix.invokeActivity(mContext, intent, new IDispatcherCallback() {
                    @Override
                    public void onFinished(String data) {
                        LogD("Logout callback data is " + data);
                        if (null == data) {
                            mAuthCode = "";
                            mLogined = false;
                            UserWrapper.onActionResult(mAdapter, UserWrapper.ACTION_RET_LOGOUT_SUCCEED, "User Logout");
                        }
                    }
                });
            }
        });
    }

    @Override
    public boolean isLogined() {
        return mLogined;
    }

    @Override
    public String getSessionID() {
        LogD("getSessionID() " + mAuthCode);
        return mAuthCode;
    }

    @Override
    public void setDebugMode(boolean debug) {
        isDebug = debug;
    }

    @Override
    public String getPluginVersion() {
        return "0.2.0";
    }

    @Override
    public String getSDKVersion() {
        return "0.7.6";
    }

    private static boolean isLandscape()
    {
        Configuration config = mContext.getResources().getConfiguration();
        int orientation = config.orientation;

        if (orientation != ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE ||
            orientation != ActivityInfo.SCREEN_ORIENTATION_PORTRAIT)
        {
            orientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE;
        }

        return (orientation == ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
    }
}
