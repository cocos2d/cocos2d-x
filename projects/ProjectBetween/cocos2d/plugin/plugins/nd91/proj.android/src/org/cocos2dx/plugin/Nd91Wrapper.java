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

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;

import com.nd.commplatform.NdCommplatform;
import com.nd.commplatform.NdMiscCallbackListener.OnLoginProcessListener;
import com.nd.commplatform.entry.NdAppInfo;

public class Nd91Wrapper {

    private static boolean isInited = false;

    public static void initSDK(Context ctx, int appId, String appKey, String orientation) {
        if (isInited) {
            return;
        }

        NdAppInfo appInfo = new NdAppInfo();
        appInfo.setCtx(ctx);

        appInfo.setAppId(appId);
        appInfo.setAppKey(appKey);
        
        NdCommplatform.getInstance().initial(0, appInfo);

        if (null != orientation) {
            if (orientation.equals("landscape")) {
                NdCommplatform.getInstance().ndSetScreenOrientation(NdCommplatform.SCREEN_ORIENTATION_LANDSCAPE);
            } else
            if (orientation.equals("auto")) {
                NdCommplatform.getInstance().ndSetScreenOrientation(NdCommplatform.SCREEN_ORIENTATION_AUTO);
            }
        }

        isInited = true;
    }

    public static boolean isLogined() {
        boolean bRet = NdCommplatform.getInstance().isLogined();
        return bRet;
    }

    public static void userLogin(Context ctx, OnLoginProcessListener listener) {
        NdCommplatform.getInstance().ndLogin(ctx, listener);
    }

    public static String getSDKVersion() {
        return "20130607_3.2.5.1";
    }

    public static String getPluginVersion() {
        return "0.2.0";
    }

    public static boolean networkReachable(Context ctx) {
        boolean bRet = false;
        try {
            ConnectivityManager conn = (ConnectivityManager)ctx.getSystemService(Context.CONNECTIVITY_SERVICE);
            NetworkInfo netInfo = conn.getActiveNetworkInfo();
            bRet = (null == netInfo) ? false : netInfo.isAvailable();
        } catch (Exception e) {
            e.printStackTrace();
        }

        return bRet;
    }
}
