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
import java.util.UUID;

import com.nd.commplatform.NdCommplatform;
import com.nd.commplatform.NdErrorCode;
import com.nd.commplatform.NdMiscCallbackListener;
import com.nd.commplatform.entry.NdBuyInfo;

import android.app.Activity;
import android.content.Context;
import android.util.Log;

public class IAPOnlineNd91 implements InterfaceIAP {

    private static final String LOG_TAG = "IAPOnlineNd91";
    private static Activity mContext = null;
    private static IAPOnlineNd91 mNd91 = null;
    private static boolean bDebug = false;
    private static Hashtable<String, String> curProductInfo = null;

    protected static void LogE(String msg, Exception e) {
        Log.e(LOG_TAG, msg, e);
        e.printStackTrace();
    }

    protected static void LogD(String msg) {
        if (bDebug) {
            Log.d(LOG_TAG, msg);
        }
    }

    public IAPOnlineNd91(Context context) {
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
                } catch (Exception e) {
                    LogE("Developer info is wrong!", e);
                }
            }
        });
    }

    @Override
    public void payForProduct(Hashtable<String, String> info) {
        LogD("payForProduct invoked " + info.toString());
        if (! Nd91Wrapper.networkReachable(mContext)) {
            payResult(IAPWrapper.PAYRESULT_FAIL, "网络不可用");
            return;
        }

        curProductInfo = info;
        if (curProductInfo == null) {
            payResult(IAPWrapper.PAYRESULT_FAIL, "商品信息错误");
            return;
        }

        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                if (! Nd91Wrapper.isLogined()) {
                    userLogin();
                } else {
                    addPayment(curProductInfo);
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

    private static void payResult(int ret, String msg) {
        IAPWrapper.onPayResult(mNd91, ret, msg);
        LogD("Nd91 result : " + ret + " msg : " + msg);
    }

    private static String getOrderSerial() {
        UUID guid = UUID.randomUUID(); 
        String text = guid.toString(); 
        text = text.replace("-", "".trim());
        return text;
    }

    private static void userLogin() {
        LogD("User begin login");
        try {
             Nd91Wrapper.userLogin(mContext, new NdMiscCallbackListener.OnLoginProcessListener() {
                @Override
                 public void finishLoginProcess(int code) {
                     if (code == NdErrorCode.ND_COM_PLATFORM_SUCCESS) {
                         addPayment(curProductInfo);
                     } else if (code == NdErrorCode.ND_COM_PLATFORM_ERROR_CANCEL) {
                         payResult(IAPWrapper.PAYRESULT_FAIL, "用户取消登录");
                     } else {
                         payResult(IAPWrapper.PAYRESULT_FAIL, "用户登录失败");
                     }
                 }
             });
        } catch (Exception e) {
            payResult(IAPWrapper.PAYRESULT_FAIL, "用户登录失败");
            LogE("User login error", e);
        }
    }

    private static void addPayment(Hashtable<String, String> productInfo) {
        try {
            do {
                String id = productInfo.get("Nd91ProductId");
                String strPrice = productInfo.get("productPrice");
                String strName = productInfo.get("productName");
                String strDesc = productInfo.get("productDesc");
                String oriPrice = productInfo.get("Nd91OriginalPrice");
                String strCount = productInfo.get("Nd91ProductCount");

                if (id == null || id.length() == 0) {
                    payResult(IAPWrapper.PAYRESULT_FAIL, "商品信息错误");
                    break;
                }

                float price = Float.parseFloat(strPrice);
                float fOriPrice = price;
                if (oriPrice != null && oriPrice.length() > 0) {
                    fOriPrice = Float.parseFloat(oriPrice);
                }
                int count = 1;
                if (strCount != null && strCount.length() > 0) {
                    count = Integer.parseInt(strCount);
                }

                String serial = IAPOnlineNd91.getOrderSerial();
                NdBuyInfo order = new NdBuyInfo();
                order.setSerial(serial);
                order.setProductId(id);
                order.setProductName(strName);
                order.setProductPrice(price);
                order.setProductOrginalPrice(fOriPrice);
                order.setCount(count);
                order.setPayDescription(strDesc);
                
                int aError = NdCommplatform.getInstance().ndUniPayAsyn(order, mContext, new NdMiscCallbackListener.OnPayProcessListener() {

                    @Override
                    public void finishPayProcess(int code) {
                        IAPOnlineNd91.LogD("finishPayProcess code : " + code);
                        switch(code){
                        case NdErrorCode.ND_COM_PLATFORM_SUCCESS:
                            IAPOnlineNd91.payResult(IAPWrapper.PAYRESULT_SUCCESS, "购买成功"); break;
                        case NdErrorCode.ND_COM_PLATFORM_ERROR_PAY_FAILURE:
                            IAPOnlineNd91.payResult(IAPWrapper.PAYRESULT_FAIL, "购买失败"); break;
                        case NdErrorCode.ND_COM_PLATFORM_ERROR_PAY_CANCEL:
                            IAPOnlineNd91.payResult(IAPWrapper.PAYRESULT_CANCEL, "取消购买"); break;
                        case NdErrorCode.ND_COM_PLATFORM_ERROR_PAY_ASYN_SMS_SENT:
                            IAPOnlineNd91.payResult(IAPWrapper.PAYRESULT_SUCCESS, "订单已提交,充值短信已发送"); break;
                        case NdErrorCode.ND_COM_PLATFORM_ERROR_PAY_REQUEST_SUBMITTED:
                            IAPOnlineNd91.payResult(IAPWrapper.PAYRESULT_SUCCESS, "订单已提交"); break;
                        default:
                            IAPOnlineNd91.payResult(IAPWrapper.PAYRESULT_FAIL, "购买失败"); break;
                        }
                    }
                });

                if (aError != 0) {
                    IAPOnlineNd91.payResult(IAPWrapper.PAYRESULT_FAIL, "您输入参数有错,无法提交购买请求");
                }
            } while (false);
        } catch (Exception e) {
            LogE("Error during payment", e);
            IAPOnlineNd91.payResult(IAPWrapper.PAYRESULT_FAIL, "支付失败");
        }
    }

    @Override
    public String getPluginVersion() {
        return Nd91Wrapper.getPluginVersion();
    }
}
