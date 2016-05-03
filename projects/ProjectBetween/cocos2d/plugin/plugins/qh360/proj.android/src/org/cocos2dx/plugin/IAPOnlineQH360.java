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

import com.qihoo.gamecenter.sdk.common.IDispatcherCallback;
import com.qihoo.gamecenter.sdk.protocols.pay.ProtocolConfigs;
import com.qihoo.gamecenter.sdk.protocols.pay.ProtocolKeys;
import com.qihoopay.insdk.activity.ContainerActivity;
import com.qihoopay.insdk.matrix.Matrix;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;

public class IAPOnlineQH360 implements InterfaceIAP {

    private static final String LOG_TAG = "IAPOnlineQH360";
    private static Activity mContext = null;
    private static IAPOnlineQH360 mAdapter = null;
    private static boolean bDebug = false;

    private static String mAppName = null;
    private static String mExchangeRate = null;

    protected static void LogE(String msg, Exception e) {
        Log.e(LOG_TAG, msg, e);
        e.printStackTrace();
    }

    protected static void LogD(String msg) {
        if (bDebug) {
            Log.d(LOG_TAG, msg);
        }
    }

    public IAPOnlineQH360(Context context) {
        mContext = (Activity) context;
        mAdapter = this;
    }

    @Override
    public void configDeveloperInfo(Hashtable<String, String> cpInfo) {
        try {
            mAppName = cpInfo.get("QHAppName");
            mExchangeRate = cpInfo.get("QHExchangeRate");
        } catch (Exception e) {
            LogE("Developer info error", e);
        }

        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                QH360Wrapper.initSDK(mContext);
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
                try {
                    Intent intent = getPayIntent(curInfo);
                    Matrix.invokeActivity(mContext, intent, new IDispatcherCallback() {
                        @Override
                        public void onFinished(String data) {
                            LogD("mPayCallback, data is " + data);
                            JSONObject jsonRes;
                            try {
                                jsonRes = new JSONObject(data);
                                int errorCode = jsonRes.getInt("error_code");
                                String errorMsg = jsonRes.getString("error_msg");
                                int retCode = IAPWrapper.PAYRESULT_FAIL;
                                switch (errorCode) {
                                case 0:
                                    // Success 
                                    retCode = IAPWrapper.PAYRESULT_SUCCESS;
                                    break;
                                case 1:
                                    // Fail 
                                    retCode = IAPWrapper.PAYRESULT_FAIL;
                                    break;
                                case -1:
                                    // cancel 
                                    retCode = IAPWrapper.PAYRESULT_CANCEL;
                                    break;
                                case -2:
                                    // paying 
                                    retCode = IAPWrapper.PAYRESULT_SUCCESS;
                                    break;
                                default:
                                    break;
                                }

                                IAPOnlineQH360.payResult(retCode, errorMsg);
                            } catch (Exception e) {
                                IAPOnlineQH360.payResult(IAPWrapper.PAYRESULT_FAIL, "Unkonw Error");
                                LogE("Error when parse the result data!", e);
                            }
                        }
                    });
                } catch (Exception e) {
                    IAPOnlineQH360.payResult(IAPWrapper.PAYRESULT_FAIL, "Unkonw Error");
                    LogE("Unknow Error!", e);
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
        return QH360Wrapper.getSDKVersion();
    }

    private static void payResult(int ret, String msg) {
        IAPWrapper.onPayResult(mAdapter, ret, msg);
        LogD("IAPOnlineQH360 result : " + ret + " msg : " + msg);
    }

    @Override
    public String getPluginVersion() {
        return "0.2.0";
    }

    private Intent getPayIntent(Hashtable<String, String> pInfo) {
        Bundle bundle = new Bundle();
        bundle.putBoolean(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, QH360Wrapper.isLandscape(mContext));

        // required params : accesstoken, userid, 
        bundle.putString(ProtocolKeys.ACCESS_TOKEN, pInfo.get("QHAccessToken")); 
        bundle.putString(ProtocolKeys.QIHOO_USER_ID, pInfo.get("QHUserId"));

        String strPrice = pInfo.get("productPrice");
        float fPrice = Float.parseFloat(strPrice);
        int nPrice = (int) (fPrice * 100);
        bundle.putString(ProtocolKeys.AMOUNT, "" + nPrice);
        bundle.putString(ProtocolKeys.RATE, mExchangeRate);
        bundle.putString(ProtocolKeys.PRODUCT_NAME, pInfo.get("productName"));
        bundle.putString(ProtocolKeys.PRODUCT_ID, pInfo.get("QHProductID"));
        bundle.putString(ProtocolKeys.NOTIFY_URI, pInfo.get("QHNotifyUri"));
        bundle.putString(ProtocolKeys.APP_NAME, mAppName);
        bundle.putString(ProtocolKeys.APP_USER_NAME, pInfo.get("QHUserName"));
        bundle.putString(ProtocolKeys.APP_USER_ID, pInfo.get("QHAppUserID"));

        // optional params : ext, app order id, pay type
        String ext1 = pInfo.get("QHExtra1");
        if (null != ext1 && ! TextUtils.isEmpty(ext1)) {
            bundle.putString(ProtocolKeys.APP_EXT_1, ext1);
        }
        String ext2 = pInfo.get("QHExtra2");
        if (null != ext2 && ! TextUtils.isEmpty(ext2)) {
            bundle.putString(ProtocolKeys.APP_EXT_2, ext2);
        }
        String appOrderId = pInfo.get("QHAppOrderID");
        if (null != appOrderId && ! TextUtils.isEmpty(appOrderId)) {
            bundle.putString(ProtocolKeys.APP_ORDER_ID, appOrderId);
        }

        bundle.putInt(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_PAY); 
        Intent intent = new Intent(mContext, ContainerActivity.class); intent.putExtras(bundle);
        return intent;
    }
}
