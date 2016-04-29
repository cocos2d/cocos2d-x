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

import java.net.URLEncoder;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Hashtable;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.KeyEvent;

public class IAPAlipay implements InterfaceIAP {

	private static final String LOG_TAG = "IAPAlipay";
	private static Activity mContext = null;
	private static boolean bDebug = false;
	private static Handler mHandler = null;
	private static IAPAlipay mAdapter = null;

	protected static void LogE(String msg, Exception e) {
		Log.e(LOG_TAG, msg, e);
		e.printStackTrace();
	}

	protected static void LogD(String msg) {
		if (bDebug) {
			Log.d(LOG_TAG, msg);
		}
	}

	public IAPAlipay(Context context) {
		mContext = (Activity) context;
		mAdapter = this;

		PluginWrapper.runOnMainThread(new Runnable() {

			@Override
			public void run() {
				initUIHandle();
			}
		});
	}

	@Override
	public void configDeveloperInfo(Hashtable<String, String> cpInfo) {
		LogD("initDeveloperInfo invoked " + cpInfo.toString());
		try {
			PartnerConfig.PARTNER = cpInfo.get("AlipayPartner");
			PartnerConfig.SELLER = cpInfo.get("AlipaySeller");
			PartnerConfig.RSA_PRIVATE = cpInfo.get("AlipayRsaPrivate");
			PartnerConfig.RSA_ALIPAY_PUBLIC = cpInfo.get("AlipayPublic");
			PartnerConfig.ALIPAY_PLUGIN_NAME = cpInfo.get("AlipayPluginName");

			strPayAccount = cpInfo.get("AlipayRoyPayAccount");
			strReceiveAccount = cpInfo.get("AlipayRoyReceiveAccount");
			fPayPercent = ((cpInfo.get("AlipayRoyPercent") == null) ? 0.0f : Float.parseFloat(cpInfo.get("AlipayRoyPercent")));
			strRoyTip = cpInfo.get("AlipayRoyTip");
			strNotifyUrl = ((null == cpInfo.get("AlipayNotifyUrl")) ? "" : cpInfo.get("AlipayNotifyUrl"));
		} catch (Exception e) {
			LogE("Developer info is wrong!", e);
		}
	}

	@Override
	public void payForProduct(Hashtable<String, String> info) {
		LogD("payForProduct invoked " + info.toString());
		if (! networkReachable()) {
			payResult(IAPWrapper.PAYRESULT_FAIL, "网络不可用");
			return;
		}

		final Hashtable<String, String> productInfo = info;
		PluginWrapper.runOnMainThread(new Runnable() {
			@Override
			public void run() {
				MobileSecurePayHelper mspHelper = new MobileSecurePayHelper(mContext);
				boolean bInstalled = mspHelper.detectMobile_sp();
				if (! bInstalled) {
					payResult(IAPWrapper.PAYRESULT_FAIL, "未安装支付宝插件");
					return;
				}

				// start pay for this order.
				// 根据订单信息开始进行支付
				try {
					// prepare the order info.
					// 准备订单信息
					String orderInfo = getOrderInfo(productInfo);
					// 这里根据签名方式对订单信息进行签名
					String signType = getSignType();
					String strsign = sign(signType, orderInfo);
					// 对签名进行编码
					strsign = URLEncoder.encode(strsign);
					// 组装好参数
					String info = orderInfo + "&sign=" + "\"" + strsign + "\"" + "&" + getSignType();
					LogD("pay info : " + info);
					// start the pay.
					// 调用pay方法进行支付
					MobileSecurePayer msp = new MobileSecurePayer();
					boolean bRet = msp.pay(info, mHandler, AlixId.RQF_PAY, mContext);

					if (bRet) {
						// show the progress bar to indicate that we have started
						// paying.
						// 显示“正在支付”进度条
						closeProgress();
						mProgress = BaseHelper.showProgress(mContext, null, "正在支付", false, true);
					} else {
						payResult(IAPWrapper.PAYRESULT_FAIL, "支付失败");
						return;
					}
				} catch (Exception ex) {
					LogE("Remote call failed", ex);
					payResult(IAPWrapper.PAYRESULT_FAIL, "remote call failed");
					return;
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
		return "Unknown version";
	}

	static class AlixOnCancelListener implements DialogInterface.OnCancelListener {
		Activity mcontext;
		AlixOnCancelListener(Activity context) {
			mcontext = context;
		}

		public void onCancel(DialogInterface dialog) {
			mcontext.onKeyDown(KeyEvent.KEYCODE_BACK, null);
		}
	}

	private static void initUIHandle() {
		//
		// the handler use to receive the pay result.
		// 这里接收支付结果，支付宝手机端同步通知
		mHandler = new Handler() {
			public void handleMessage(Message msg) {
				try {
					String strRet = (String) msg.obj;
					LogD("handle msg : " + msg.toString());

					switch (msg.what) {
					case AlixId.RQF_PAY: {
						LogD("msg.what is RQF_PAY");
						mAdapter.closeProgress();

						// 从通知中获取参数
						try {
							// 获取交易状态，具体状态代码请参看文档
							String memo = "memo=";
							int imemoStart = strRet.indexOf("memo=");
							imemoStart += memo.length();
							int imemoEnd = strRet.indexOf(";result=");
							memo = strRet.substring(imemoStart, imemoEnd);
							// 对通知进行验签
							ResultChecker resultChecker = new ResultChecker(strRet);

							int retVal = resultChecker.checkSign();
							// 返回验签结果以及交易状态
							if (retVal == ResultChecker.RESULT_CHECK_SIGN_FAILED) {
								payResult(IAPWrapper.PAYRESULT_FAIL, "签名验证失败");
							} else if (retVal == ResultChecker.RESULT_CHECK_SIGN_SUCCEED && resultChecker.isPayOk()) {
								payResult(IAPWrapper.PAYRESULT_SUCCESS, "支付成功");
							} else {
								payResult(IAPWrapper.PAYRESULT_FAIL, "支付失败");
							}
						} catch (Exception e) {
							e.printStackTrace();
							payResult(IAPWrapper.PAYRESULT_FAIL, "结果解析失败");
						}
					}
						break;
					default:
						mAdapter.closeProgress();
						payResult(IAPWrapper.PAYRESULT_FAIL, "支付失败");
						break;
					}

					super.handleMessage(msg);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		};
	}
	/**
	 * get the selected order info for pay. 获取商品订单信息
	 * 
	 * @param position
	 *            商品在列表中的位置
	 * @return
	 */
	private static String strPayAccount = "";
	private static String strReceiveAccount = "";
	private static float fPayPercent = 0.0f;
	private static String strRoyTip = "";
	private static String strNotifyUrl = "";
	private String getOrderInfo(Hashtable<String, String> info) {
		String strRet = null;
		try {
			float price = Float.parseFloat(info.get("productPrice"));//IAPProducts.getProductPrice(productID);
			String productName = info.get("productName");
			String productDesc = info.get("productDesc");
			String royParam = "";
			if (fPayPercent > 0 ) {
				float royValue = fPayPercent * price;
				royParam = strPayAccount + "^" + strReceiveAccount + "^" + royValue + "^"+ strRoyTip;
				royParam = "&royalty_parameters=\""+ royParam + "\"" + "&royalty_type=\"10" + "\"";
			}

			strRet = "partner=\"" + PartnerConfig.PARTNER + "\""
						+ "&seller=\"" + PartnerConfig.SELLER + "\""
						+ "&out_trade_no=\"" + getOutTradeNo() + "\""
						+ "&subject=\"" + productName + "\""
						+ "&body=\"" + productDesc + "\""
						+ "&total_fee=\"" + price + "\""
						+ "&notify_url=\"" + strNotifyUrl + "\""
						+ royParam;
		} catch (Exception e) {
			LogE("Product info parse error", e);
		}

		LogD("order info : " + strRet);
		return strRet;
	}

	/**
	 * get the out_trade_no for an order.
	 * 获取外部订单号
	 * 
	 * @return
	 */
	String getOutTradeNo() {
		SimpleDateFormat format = new SimpleDateFormat("yyyyMMddHHmmss");
		Date date = new Date();
		String strKey = format.format(date);

		java.util.Random r = new java.util.Random();
		strKey = strKey + r.nextInt(10000);
		return strKey;
	}

	//
	//
	/**
	 *  sign the order info.
	 *  对订单信息进行签名
	 *  
	 * @param signType	签名方式 
	 * @param content		待签名订单信息
	 * @return
	 */
	private String sign(String signType, String content) {
		LogD("sign params :");
		LogD("type : " + signType + ", content : " + content + ", private : " + PartnerConfig.RSA_PRIVATE);
		return Rsa.sign(content, PartnerConfig.RSA_PRIVATE);
	}

	/**
	 * get the sign type we use.
	 * 获取签名方式
	 * 
	 * @return
	 */
	private String getSignType() {
		String getSignType = "sign_type=" + "\"" + "RSA" + "\"";
		return getSignType;
	}
	
	private ProgressDialog mProgress = null;
	void closeProgress() {
		try {
			if (mProgress != null) {
				mProgress.dismiss();
				mProgress = null;
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private boolean networkReachable() {
		boolean bRet = false;
		try {
			ConnectivityManager conn = (ConnectivityManager)mContext.getSystemService(Context.CONNECTIVITY_SERVICE);
			NetworkInfo netInfo = conn.getActiveNetworkInfo();
			bRet = (null == netInfo) ? false : netInfo.isAvailable();
		} catch (Exception e) {
			LogE("Fail to check network status", e);
		}
		LogD("NetWork reachable : " + bRet);
		return bRet;
	}

	private static void payResult(int ret, String msg) {
		IAPWrapper.onPayResult(mAdapter, ret, msg);
		LogD("Alipay result : " + ret + " msg : " + msg);
	}

	@Override
	public String getPluginVersion() {
		return "0.2.0";
	}
}
