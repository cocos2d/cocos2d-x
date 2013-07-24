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
import cn.uc.gamesdk.info.OrderInfo;
import cn.uc.gamesdk.info.PaymentInfo;
import android.app.Activity;
import android.content.Context;
import android.text.TextUtils;
import android.util.Log;

public class IAPOnlineUC implements InterfaceIAP {

    private static final String LOG_TAG = "IAPOnlineUC";
    private static Activity mContext = null;
    private static IAPOnlineUC mAdapter = null;
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

    public IAPOnlineUC(Context context) {
        mContext = (Activity) context;
        mAdapter = this;
    }

    @Override
    public void configDeveloperInfo(Hashtable<String, String> cpInfo) {
        final Hashtable<String, String> curInfo = cpInfo;
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                UCWrapper.initSDK(mContext, curInfo, bDebug, null);
            }
        });
    }

    @Override
    public void payForProduct(Hashtable<String, String> info) {
        LogD("payForProduct invoked " + info.toString());
        final Hashtable<String, String> curInfo = info;
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                if (UCWrapper.isLogined()) {
                    addPayment(curInfo);
                } else {
                    UCWrapper.userLogin(mContext, new UCCallbackListener<String>() {
                        @Override
                        public void callback(int code, String msg) {
                            switch(code) {
                            case UCGameSDKStatusCode.SUCCESS:
                                addPayment(curInfo);
                                break;
                            default:
                                payResult(IAPWrapper.PAYRESULT_FAIL, msg);
                                break;
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
        return UCWrapper.getSDKVersion();
    }

    private static void payResult(int ret, String msg) {
        IAPWrapper.onPayResult(mAdapter, ret, msg);
        LogD("IAPOnlineUC result : " + ret + " msg : " + msg);
    }

    @Override
    public String getPluginVersion() {
        return "0.2.0";
    }

    private static boolean paying = false;
    private void addPayment(Hashtable<String, String> curInfo) {
        try {
            paying = true;
            PaymentInfo payInfo = new PaymentInfo();

            String customInfo = curInfo.get("UCCustomInfo");
            if (null != customInfo && ! TextUtils.isEmpty(customInfo)) {
                payInfo.setCustomInfo(customInfo);
            }

            String strServerID = curInfo.get("UCServerID");
            if (null != strServerID && ! TextUtils.isEmpty(strServerID)) {
                int serverID = Integer.parseInt(strServerID);
                payInfo.setServerId(serverID);
            }

            String roleID = curInfo.get("UCRoleID");
            if (null != roleID && ! TextUtils.isEmpty(roleID)) {
                payInfo.setRoleId(roleID);
            }

            String strRoleName = curInfo.get("UCRoleName");
            if (null != strRoleName && ! TextUtils.isEmpty(strRoleName)) {
                payInfo.setRoleName(strRoleName);
            }

            String strRoleLevel = curInfo.get("UCRoleLevel");
            if (null != strRoleLevel && ! TextUtils.isEmpty(strRoleLevel)) {
                payInfo.setGrade(strRoleLevel);
            }

            String strPrice = curInfo.get("productPrice");
            float fPrice = Float.parseFloat(strPrice);
            payInfo.setAmount(fPrice);

            UCGameSDK.defaultSDK().pay(mContext, payInfo, new UCCallbackListener<OrderInfo>(){
                @Override
                public void callback(int arg0, OrderInfo arg1) {
                    if (! paying) {
                        return;
                    }

                    switch (arg0) {
                    case UCGameSDKStatusCode.SUCCESS:
                        IAPOnlineUC.payResult(IAPWrapper.PAYRESULT_SUCCESS, "Pay Succeed");
                        break;
                    default:
                        IAPOnlineUC.payResult(IAPWrapper.PAYRESULT_FAIL, "Unknown Error");
                        break;
                    }

                    paying = false;
                }
            });
        } catch (Exception e) {
            paying = false;
            IAPOnlineUC.payResult(IAPWrapper.PAYRESULT_FAIL, "Unknown Error");
            LogE("Unknown Error", e);
        }
    }
}
