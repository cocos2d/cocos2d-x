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

import org.json.JSONObject;

import com.qihoo.gamecenter.sdk.common.IDispatcherCallback;
import com.qihoo.gamecenter.sdk.protocols.pay.ProtocolConfigs;
import com.qihoo.gamecenter.sdk.protocols.pay.ProtocolKeys;
import com.qihoopay.insdk.activity.ContainerActivity;
import com.qihoopay.insdk.matrix.Matrix;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.res.Configuration;
import android.os.Bundle;

public class QH360Wrapper {

    private static boolean mInited = false;
    public static void initSDK(Context ctx) {
        if (mInited) {
            return;
        }

        Matrix.init((Activity) ctx, isLandscape(ctx), new IDispatcherCallback() {
            @Override
            public void onFinished(String data) {
                mInited = true;
            }
        });
    }

    public static String getSDKVersion() {
        return "0.7.6";
    }

    public static boolean isLandscape(Context ctx)
    {
        Configuration config = ctx.getResources().getConfiguration();
        int orientation = config.orientation;

        if (orientation != Configuration.ORIENTATION_LANDSCAPE &&
            orientation != Configuration.ORIENTATION_PORTRAIT)
        {
            orientation = Configuration.ORIENTATION_PORTRAIT;
        }

        return (orientation == Configuration.ORIENTATION_LANDSCAPE);
    }

    private static boolean mLogined = false;
    private static String mAuthCode = "";
    public static void userLogin(Context ctx, IDispatcherCallback callback) {
        if (mLogined) {
            return;
        }

        final Context curCtx = ctx;
        final IDispatcherCallback curCallback = callback;
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                Bundle bundle = new Bundle();
                bundle.putBoolean(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, isLandscape(curCtx));
                bundle.putBoolean(ProtocolKeys.IS_LOGIN_BG_TRANSPARENT, true);
                bundle.putString(ProtocolKeys.RESPONSE_TYPE, "code");
                bundle.putInt(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_LOGIN);
                Intent intent = new Intent(curCtx, ContainerActivity.class);
                intent.putExtras(bundle);

                Matrix.invokeActivity(curCtx, intent, new IDispatcherCallback() {
                    @Override
                    public void onFinished(String data) {
                        if (null == data) {
                            mLogined = false;
                            mAuthCode = "";
                            curCallback.onFinished(data);
                            return;
                        }
        
                        String retStr = "Unknown Error";
                        try {
                            JSONObject json = new JSONObject(data);
                            int errCode = json.optInt("error_code");
                            switch (errCode) {
                            case 0:
                                {
                                    mLogined = true;
                                    JSONObject content = json.optJSONObject("data");
                                    mAuthCode = content.optString("code");
                                    retStr = "";
                                }
                                break;
                            default:
                                mLogined = false;
                                mAuthCode = "";
                                retStr = "Login Failed";
                                break;
                            }
                        } catch (Exception e) {
                            mLogined = false;
                            mAuthCode = "";
                            retStr = "Unknow Error";
                            e.printStackTrace();
                        } finally {
                            curCallback.onFinished(retStr);
                        }
                    }
                });
            }
        });
    }

    public static void userLogout(Context ctx, IDispatcherCallback callback) {
        final Context curCtx = ctx;
        final IDispatcherCallback curCallback = callback;
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                Bundle bundle = new Bundle();
                bundle.putBoolean(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, isLandscape(curCtx));
                bundle.putInt(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_QUIT);
                Intent intent = new Intent(curCtx, ContainerActivity.class);
                intent.putExtras(bundle);

                Matrix.invokeActivity(curCtx, intent, new IDispatcherCallback() {
                    @Override
                    public void onFinished(String data) {
                        if (null == data) {
                            mAuthCode = "";
                            mLogined = false;
                        }
                        curCallback.onFinished(data);
                    }
                });
            }
        });
    }

    public static boolean isLogined() {
        return mLogined;
    }

    public static String getAuthCode() {
        return mAuthCode;
    }
}
