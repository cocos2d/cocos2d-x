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
import android.content.Context;
import android.text.TextUtils;
import android.util.Log;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.FrameLayout;

import com.flurry.android.FlurryAdListener;
import com.flurry.android.FlurryAdSize;
import com.flurry.android.FlurryAdType;
import com.flurry.android.FlurryAds;
import com.flurry.android.FlurryAgent;

public class AdsFlurry implements InterfaceAds, FlurryAdListener {

    private Context mContext = null;
    protected static String TAG = "AdsFlurry";

    private FrameLayout mBannerView = null;
    private WindowManager mWm = null;
    private AdsFlurry mAdapter = null;

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

    public AdsFlurry(Context context) {
        mContext = context;
        mAdapter = this;
    }

    @Override
    public void setDebugMode(boolean isDebugMode) {
        isDebug = isDebugMode;
        final boolean curDebug = isDebug;
        PluginWrapper.runOnMainThread(new Runnable(){
            @Override
            public void run() {
                FlurryAgent.setLogEnabled(curDebug);
                if (curDebug) {
                    FlurryAgent.setLogLevel(Log.DEBUG);
                }
            }
        });
    }

    @Override
    public String getSDKVersion() {
        return "3.2.1";
    }

    @Override
    public String getPluginVersion() {
        return "0.2.0";
    }

    @Override
    public void configDeveloperInfo(Hashtable<String, String> devInfo) {
        final Hashtable<String, String> curInfo = devInfo;
        PluginWrapper.runOnMainThread(new Runnable(){
            @Override
            public void run() {
                try {
                    String appKey = curInfo.get("FlurryAppKey");
                    FlurryAgent.onStartSession(mContext, appKey);
                    FlurryAds.setAdListener(mAdapter);
                    FlurryAds.initializeAds(mContext);
                } catch (Exception e) {
                    LogE("Error during configDeveloperInfo.", e);
                }
            }
        });
    }

    @Override
    public void showAds(Hashtable<String, String> adsInfo, int pos) {
        final Hashtable<String, String> curInfo = adsInfo;
        final int curPos = pos;
        PluginWrapper.runOnMainThread(new Runnable(){
            @Override
            public void run() {
                try
                {
                    String spaceID = curInfo.get("FlurryAdsID");
                    if (null == spaceID || TextUtils.isEmpty(spaceID))
                    {
                        LogD("Value of 'FlurryAdsID' should not be empty");
                        return;
                    }

                    String strSize = curInfo.get("FlurryAdsSize");
                    int size = Integer.parseInt(strSize);
                    if (size != 1 && size != 2 && size != 3) {
                        LogD("Valur of 'FlurryAdsSize' should be one of '1', '2', '3'");
                        return;
                    }

                    FlurryAdSize eSize = FlurryAdSize.BANNER_TOP;
                    switch (size)
                    {
                    case 1:
                        eSize = FlurryAdSize.BANNER_TOP;
                        break;
                    case 2:
                        eSize = FlurryAdSize.BANNER_BOTTOM;
                        break;
                    case 3:
                        eSize = FlurryAdSize.FULLSCREEN;
                        break;
                    default:
                        break;
                    }

                    if (null == mWm) {
                        mWm = (WindowManager) mContext.getSystemService("window");
                    }
                    if (null != mBannerView) {
                        mWm.removeView(mBannerView);
                        mBannerView = null;
                    }
                    mBannerView = new FrameLayout(mContext);
                    AdsWrapper.addAdView(mWm, mBannerView, curPos);

                    FlurryAds.fetchAd(mContext, spaceID, mBannerView, eSize);
                } catch (Exception e) {
                    LogE("Error during showAds", e);
                }
            }
        });
    }

    @Override
    public void hideAds(Hashtable<String, String> adsInfo) {
        final Hashtable<String, String> curInfo = adsInfo;
        PluginWrapper.runOnMainThread(new Runnable(){
            @Override
            public void run() {
                try
                {
                    String spaceID = curInfo.get("FlurryAdsID");
                    if (null == spaceID || TextUtils.isEmpty(spaceID))
                    {
                        LogD("Value of 'FlurryAdsID' should not be empty");
                        return;
                    }

                    FlurryAds.removeAd(mContext, spaceID, (ViewGroup) mBannerView);
                } catch (Exception e) {
                    LogE("Error during hideAds", e);
                }
            }
        });
    }

    @Override
    public void queryPoints() {
        // TODO Auto-generated method stub
        
    }

    @Override
    public void spendPoints(int points) {
        // TODO Auto-generated method stub
        
    }

    @Override
    public void onAdClicked(String arg0) {
        // TODO Auto-generated method stub
        
    }

    @Override
    public void onAdClosed(String arg0) {
        AdsWrapper.onAdsResult(this, AdsWrapper.RESULT_CODE_AdsDismissed, "Ads will be dismissed");
    }

    @Override
    public void onAdOpened(String arg0) {
        // TODO Auto-generated method stub
        
    }

    @Override
    public void onApplicationExit(String arg0) {
        // TODO Auto-generated method stub
        
    }

    @Override
    public void onRenderFailed(String arg0) {
        // TODO Auto-generated method stub
        
    }

    @Override
    public void onVideoCompleted(String arg0) {
        // TODO Auto-generated method stub
        
    }

    @Override
    public boolean shouldDisplayAd(String arg0, FlurryAdType arg1) {
        AdsWrapper.onAdsResult(this, AdsWrapper.RESULT_CODE_AdsShown, "Ads will be shown");
        return true;
    }

    @Override
    public void spaceDidFailToReceiveAd(String arg0) {
        LogD("param : " + arg0);
        AdsWrapper.onAdsResult(this, AdsWrapper.RESULT_CODE_UnknownError, "Failed to receive Ads of flurry");
    }

    @Override
    public void spaceDidReceiveAd(String arg0) {
        AdsWrapper.onAdsResult(this, AdsWrapper.RESULT_CODE_AdsReceived, "Ads of flurry received");
    }
}
