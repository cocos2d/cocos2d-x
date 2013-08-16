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

import com.qihoo.gamecenter.sdk.common.IDispatcherCallback;

import android.content.Context;
import android.text.TextUtils;
import android.util.Log;

public class UserQH360 implements InterfaceUser {

    private static Context mContext = null;
    protected static String TAG = "UserQH360";
    private static InterfaceUser mAdapter = null;

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
                QH360Wrapper.initSDK(mContext);
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

        QH360Wrapper.userLogin(mContext, new IDispatcherCallback() {
            @Override
            public void onFinished(String data) {
                LogD("Login callback data is " + data);

                if (null == data) {
                    UserWrapper.onActionResult(mAdapter, UserWrapper.ACTION_RET_LOGIN_FAILED, "User Canceled");
                } else 
                if (TextUtils.isEmpty(data)) {
                    UserWrapper.onActionResult(mAdapter, UserWrapper.ACTION_RET_LOGIN_SUCCEED, "Login Succeed");
                } else {
                    UserWrapper.onActionResult(mAdapter, UserWrapper.ACTION_RET_LOGIN_FAILED, data);
                }
            }
        });
    }

    @Override
    public void logout() {
        if (! isLogined()) {
            LogD("User not logined!");
            return;
        }

        QH360Wrapper.userLogout(mContext, new IDispatcherCallback() {
            @Override
            public void onFinished(String data) {
                LogD("Logout callback data is " + data);
                if (null == data) {
                    UserWrapper.onActionResult(mAdapter, UserWrapper.ACTION_RET_LOGOUT_SUCCEED, "User Logout");
                }
            }
        });
    }

    @Override
    public boolean isLogined() {
        return QH360Wrapper.isLogined();
    }

    @Override
    public String getSessionID() {
        LogD("getSessionID() " + QH360Wrapper.getAuthCode());
        return QH360Wrapper.getAuthCode();
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
        return QH360Wrapper.getSDKVersion();
    }
}
