/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

import com.nd.commplatform.NdCallbackListener;
import com.nd.commplatform.NdCommplatform;
import com.nd.commplatform.NdErrorCode;
import com.nd.commplatform.NdMiscCallbackListener.OnLoginProcessListener;
import com.nd.commplatform.entry.NdAchieveUnlockInfo;

import android.app.Activity;
import android.content.Context;
import android.text.TextUtils;
import android.util.Log;

public class SocialNd91 implements InterfaceSocial {

    private static final String LOG_TAG = "UserNd91";
    private static Activity mContext = null;
    private static SocialNd91 mNd91 = null;
    private static boolean bDebug = false;
    private static NdCallbackListener<Object> submitListener = null;
    private static NdCallbackListener<Object> unlockListener = null;
    
    protected static void LogE(String msg, Exception e) {
        Log.e(LOG_TAG, msg, e);
        e.printStackTrace();
    }

    protected static void LogD(String msg) {
        if (bDebug) {
            Log.d(LOG_TAG, msg);
        }
    }

    public SocialNd91(Context context) {
        mContext = (Activity) context;
        mNd91 = this;

        submitListener = new NdCallbackListener<Object>(){
            @Override
            public void callback(int arg0, Object arg1) {
                int nRet = SocialWrapper.SOCIAL_SUBMITSCORE_FAILED;
                String msg = "Unknow Error";
                switch (arg0) {
                case NdCommplatform.SCORE_SUBMIT_SUCCESS:
                    nRet = SocialWrapper.SOCIAL_SUBMITSCORE_SUCCESS;
                    msg = "Submit Success";
                    break;
                case NdCommplatform.SCORE_SAVE_LOCAL:
                    nRet = SocialWrapper.SOCIAL_SUBMITSCORE_FAILED;
                    msg = "Score saved locally";
                    break;
                case NdCommplatform.LEADERBOARD_NOT_EXIST:
                    nRet = SocialWrapper.SOCIAL_SUBMITSCORE_FAILED;
                    msg = "The leaderboard not exist";
                    break;
                default:
                    nRet = SocialWrapper.SOCIAL_SUBMITSCORE_FAILED;
                    break;
                }
                SocialWrapper.onSocialResult(mNd91, nRet, msg);
            }
        };

        unlockListener = new NdCallbackListener<Object>(){
            @Override
            public void callback(int arg0, Object arg1) {
                int nRet = SocialWrapper.SOCIAL_UNLOCKACH_FAILED;
                String msg = "Unknow Error";
                switch (arg0) {
                case NdErrorCode.ND_COM_PLATFORM_SUCCESS:
                    nRet = SocialWrapper.SOCIAL_UNLOCKACH_SUCCESS;
                    msg = "Unlock Success";
                    break;
                case NdErrorCode.ND_COM_PLATFORM_ERROR_SERVER_RETURN_ERROR:
                    nRet = SocialWrapper.SOCIAL_UNLOCKACH_FAILED;
                    msg = "Server return error";
                    break;
                case NdErrorCode.ND_COM_PLATFORM_ERROR_ACHIEVEMENT_NO_EXIST:
                    nRet = SocialWrapper.SOCIAL_UNLOCKACH_FAILED;
                    msg = "Achievement not exist";
                    break;
                default:
                    nRet = SocialWrapper.SOCIAL_UNLOCKACH_FAILED;
                    break;
                }
                SocialWrapper.onSocialResult(mNd91, nRet, msg);
            }
        };
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

                } catch (Exception e) {
                    LogE("Developer info is wrong!", e);
                }
            }
        });
    }

    @Override
    public void submitScore(String leaderboardID, long score) {
        final String curID = leaderboardID;
        final long curScore = score;
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                NdCommplatform.getInstance().ndSubmitScore(curID, (int) curScore, null, (Activity) mContext, submitListener);
            }
        });
    }

    @Override
    public void showLeaderboard(String leaderboardID) {
        final String curID = leaderboardID;
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                if (Nd91Wrapper.isLogined()) {
                    NdCommplatform.getInstance().ndOpenLeaderBoard(mContext, curID, 0);
                } else {
                    Nd91Wrapper.userLogin(mContext, new OnLoginProcessListener() {
                        @Override
                        public void finishLoginProcess(int code) {
                            if (code == NdErrorCode.ND_COM_PLATFORM_SUCCESS) {
                                NdCommplatform.getInstance().ndOpenLeaderBoard(mContext, curID, 0);
                            } else {
                                LogD("User should login first");
                            }
                        }
                    });
                }
            }
        });
    }

    @Override
    public void unlockAchievement(Hashtable<String, String> achInfo) {
        final Hashtable<String, String> curInfo = achInfo;
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                try {
                    String achID = curInfo.get("AchievementID");
                    if (achID == null || TextUtils.isEmpty(achID))
                    {
                        SocialWrapper.onSocialResult(mNd91, SocialWrapper.SOCIAL_UNLOCKACH_FAILED, "Achievement info error");
                        return;
                    }

                    String displayText = curInfo.get("NDDisplayText");
                    String strScore = curInfo.get("NDScore");
                    long score = Long.parseLong(strScore);
                    NdAchieveUnlockInfo info = new NdAchieveUnlockInfo();
                    info.setAchievementId(achID);
                    info.setCurrentValue(score);
                    info.setDisplayText(displayText);

                    NdCommplatform.getInstance().ndUnlockAchievement(info, mContext, unlockListener);
                } catch (Exception e) {
                    LogE("Unknown Error!", e);
                }
            }
        });
    }

    @Override
    public void showAchievements() {
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                if (Nd91Wrapper.isLogined()) {
                    NdCommplatform.getInstance().ndOpenAchievement(mContext, 0);
                } else {
                    Nd91Wrapper.userLogin(mContext, new OnLoginProcessListener() {
                        @Override
                        public void finishLoginProcess(int code) {
                            if (code == NdErrorCode.ND_COM_PLATFORM_SUCCESS) {
                                NdCommplatform.getInstance().ndOpenAchievement(mContext, 0);
                            } else {
                                LogD("User should login first");
                            }
                        }
                    });
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
}
