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
import com.nd.commplatform.NdCommplatform;
import com.nd.commplatform.NdErrorCode;
import com.nd.commplatform.NdMiscCallbackListener;
import com.nd.commplatform.NdMiscCallbackListener.OnSwitchAccountListener;

import android.app.Activity;
import android.content.Context;
import android.util.Log;

public class UserNd91 implements InterfaceUser {

	private static final String LOG_TAG = "UserNd91";
	private static Activity mContext = null;
	private static UserNd91 mNd91 = null;
	private static boolean bDebug = false;

	protected static void LogE(String msg, Exception e) {
		Log.e(LOG_TAG, msg, e);
		e.printStackTrace();
	}

	protected static void LogD(String msg) {
		if (bDebug) {
			Log.d(LOG_TAG, msg);
		}
	}

	public UserNd91(Context context) {
		mContext = (Activity) context;
		mNd91 = this;
	}

	@Override
	public void configDeveloperInfo(Hashtable<String, String> cpInfo) {
		LogD("initDeveloperInfo invoked " + cpInfo.toString());
		final Hashtable<String, String> curCPInfo = cpInfo;
		PluginWrapper.runOnMainThread(new Runnable() {
			@Override
			public void run() {
				try {
					String appId = curCPInfo.get("Nd91AppId");
					String appKey = curCPInfo.get("Nd91AppKey");
					int id = Integer.parseInt(appId);

					String orientation = curCPInfo.get("Nd91Orientation");
					Nd91Wrapper.initSDK(mContext, id, appKey, orientation);

					NdCommplatform.getInstance().setOnSwitchAccountListener(new OnSwitchAccountListener() {
                        @Override
                        public void onSwitchAccount(int arg0) {
                            switch (arg0) {
                            case NdErrorCode.ND_COM_PLATFORM_ERROR_USER_RESTART:
                                break;
                            case NdErrorCode.ND_COM_PLATFORM_ERROR_USER_SWITCH_ACCOUNT:
                                break;
                            case NdErrorCode.ND_COM_PLATFORM_SUCCESS:
                                UserWrapper.onActionResult(mNd91, UserWrapper.ACTION_RET_LOGIN_SUCCEED, "User login succeed");
                                break;
                            case NdErrorCode.ND_COM_PLATFORM_ERROR_CANCEL:
                                break;
                            default:
                                UserWrapper.onActionResult(mNd91, UserWrapper.ACTION_RET_LOGOUT_SUCCEED, "User logout");
                                break;
                            }
                        }
					});
				} catch (Exception e) {
					LogE("Developer info is wrong!", e);
				}
			}
		});
	}

	@Override
	public void setDebugMode(boolean debug) {
		bDebug = debug;
	}

	@Override
	public String getSDKVersion() {
		return Nd91Wrapper.getSDKVersion();
	}

	@Override
	public String getPluginVersion() {
		return Nd91Wrapper.getPluginVersion();
	}

    @Override
    public void login() {
        if (isLogined()) {
            UserWrapper.onActionResult(mNd91, UserWrapper.ACTION_RET_LOGIN_SUCCEED, "Already logined!");
            return;
        }

        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                Nd91Wrapper.userLogin(mContext, new NdMiscCallbackListener.OnLoginProcessListener() {
                    @Override
                    public void finishLoginProcess(int code) {
                        if (code == NdErrorCode.ND_COM_PLATFORM_SUCCESS) {
                            UserWrapper.onActionResult(mNd91, UserWrapper.ACTION_RET_LOGIN_SUCCEED, "User login succeed");
                        } else if (code == NdErrorCode.ND_COM_PLATFORM_ERROR_CANCEL) {
                            UserWrapper.onActionResult(mNd91, UserWrapper.ACTION_RET_LOGIN_FAILED, "User canceled");
                        } else {
                            UserWrapper.onActionResult(mNd91, UserWrapper.ACTION_RET_LOGIN_FAILED, "User login failed");
                        }
                    }
                });
            }
        });
    }

    @Override
    public void logout() {
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                NdCommplatform.getInstance().ndLogout(NdCommplatform.LOGOUT_TO_NON_RESET_AUTO_LOGIN_CONFIG, mContext);
                UserWrapper.onActionResult(mNd91, UserWrapper.ACTION_RET_LOGOUT_SUCCEED, "User logout");
            }
        });
    }

    @Override
    public boolean isLogined() {
        return Nd91Wrapper.isLogined();
    }

    @Override
    public String getSessionID() {
        String strRet = "";
        if (isLogined()) {
            strRet = NdCommplatform.getInstance().getSessionId();
        }
        return strRet;
    }
}
