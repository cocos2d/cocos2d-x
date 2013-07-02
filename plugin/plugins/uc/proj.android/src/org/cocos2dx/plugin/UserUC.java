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

import cn.uc.gamesdk.UCCallbackListener;
import cn.uc.gamesdk.UCGameSDK;
import cn.uc.gamesdk.UCGameSDKStatusCode;
import cn.uc.gamesdk.UCLogLevel;
import cn.uc.gamesdk.UCOrientation;
import cn.uc.gamesdk.info.GameParamInfo;

import android.content.Context;
import android.content.pm.ActivityInfo;
import android.content.res.Configuration;
import android.util.Log;

public class UserUC implements InterfaceUser {

    private static Context mContext = null;
    protected static String TAG = "UserUC";
    private static InterfaceUser mAdapter = null;
    private boolean mLogined = false;

    protected static void LogE(String msg, Exception e) {
        Log.e(TAG, msg, e);
        e.printStackTrace();
    }

    private static boolean isDebug = false;
    private boolean isInited = false;
    protected static void LogD(String msg) {
        if (isDebug) {
            Log.d(TAG, msg);
        }
    }

    public UserUC(Context context) {
        mContext = context;
        mAdapter = this;
    }

    @Override
    public void configDeveloperInfo(Hashtable<String, String> cpInfo) {
        final Hashtable<String, String> curInfo = cpInfo;
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                try {
                    String strCpId = curInfo.get("UCCpId");
                    String strGameId = curInfo.get("UCGameId");
                    String strServerId = curInfo.get("UCServerId");

                    int cpId = Integer.parseInt(strCpId);
                    int gameId = Integer.parseInt(strGameId);
                    int serverId = Integer.parseInt(strServerId);
                    GameParamInfo gpi = new GameParamInfo();
                    gpi.setCpId(cpId);
                    gpi.setGameId(gameId);
                    gpi.setServerId(serverId);

                    UCGameSDK.defaultSDK().setLogoutNotifyListener(new UCCallbackListener<String>() {
                        @Override
                        public void callback(int statuscode, String data) {
                            switch (statuscode) {
                            case UCGameSDKStatusCode.SUCCESS:
                                UserWrapper.onActionResult(mAdapter, UserWrapper.ACTION_RET_LOGOUT_SUCCEED, "User Logout!");
                                mLogined = false;
                                break;
                            default:
                                break;
                            }
                        }
                    });

                    if (isLandscape()) {
                        UCGameSDK.defaultSDK().setOrientation(UCOrientation.LANDSCAPE);
                    }

                    UCGameSDK.defaultSDK().initSDK(mContext, UCLogLevel.ERROR, isDebug, gpi, new UCCallbackListener<String>() {
                        @Override
                        public void callback(int code, String msg) {
                            System.out.println("msg:" + msg); 
                            switch (code) {
                                case UCGameSDKStatusCode.SUCCESS:
                                    isInited = true;
                                    break;
                                case UCGameSDKStatusCode.INIT_FAIL:
                                default:
                                    isInited = false;
                                    break;
                            }
                        }
                    });
                } catch(Exception e) {
                    isInited = false;
                    LogE("Init SDK failed", e);
                }
            }
        });
    }

    private static boolean waitHandle = true;
    @Override
    public void login() {
        if (! isInited) {
            UserWrapper.onActionResult(mAdapter, UserWrapper.ACTION_RET_LOGIN_FAILED, "SDK init failed");
            return;
        }

        if (isLogined()) {
            UserWrapper.onActionResult(mAdapter, UserWrapper.ACTION_RET_LOGIN_SUCCEED, "Already logined!");
            return;
        }

        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                try {
                    waitHandle = true;
                    UCGameSDK.defaultSDK().login(mContext, new UCCallbackListener<String>() {
                        @Override
                        public void callback(int code, String msg) {
                            LogD("login ret : " + code + " , msg : " + msg);
                            if (! waitHandle) {
                                return;
                            }

                            switch(code) {
                            case UCGameSDKStatusCode.SUCCESS:
                                mLogined = true;
                                UserWrapper.onActionResult(mAdapter, UserWrapper.ACTION_RET_LOGIN_SUCCEED, msg);
                                break;
                            default:
                                mLogined = false;
                                UserWrapper.onActionResult(mAdapter, UserWrapper.ACTION_RET_LOGIN_FAILED, msg);
                                break;
                            }

                            waitHandle = false;
                        }
                    });
                } catch (Exception e) {
                    mLogined = false;
                    LogE("Login failed", e);
                    UserWrapper.onActionResult(mAdapter, UserWrapper.ACTION_RET_LOGIN_FAILED, "Login Failed!");
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

        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                try {
                    UCGameSDK.defaultSDK().logout();
                } catch (Exception e) {
                    LogE("User logout failed", e);
                }
            }
        });
    }

    @Override
    public boolean isLogined() {
        return mLogined;
    }

    @Override
    public String getSessionID() {
        LogD("getSessionID() invoked!");
        return UCGameSDK.defaultSDK().getSid();
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
        return "2.3.4";
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
