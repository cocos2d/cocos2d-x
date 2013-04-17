package org.cocos2dx.plugin;

import java.util.Hashtable;
import java.util.UUID;

import org.cocos2dx.plugin.InterfaceIAP.IAPAdapter;

import com.nd.commplatform.NdCommplatform;
import com.nd.commplatform.NdErrorCode;
import com.nd.commplatform.NdMiscCallbackListener;
import com.nd.commplatform.entry.NdAppInfo;
import com.nd.commplatform.entry.NdBuyInfo;

import android.app.Activity;
import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.util.Log;

public class IAPNd91 implements IAPAdapter {

	private static final String LOG_TAG = "IAPNd91";
	private static Activity mContext = null;
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

	public IAPNd91(Context context) {
		mContext = (Activity) context;
	}

	@Override
	public void initDeveloperInfo(Hashtable<String, String> cpInfo) {
		LogD("initDeveloperInfo invoked " + cpInfo.toString());
		final Hashtable<String, String> curCPInfo = cpInfo;
		PluginWrapper.runOnMainThread(new Runnable() {
			@Override
			public void run() {
				try {
					String appId = curCPInfo.get("Nd91AppId");
					String appKey = curCPInfo.get("Nd91AppKey");
					int id = Integer.parseInt(appId);

					NdAppInfo appInfo = new NdAppInfo();
					appInfo.setCtx(mContext);

					appInfo.setAppId(id);
					appInfo.setAppKey(appKey);
					
					NdCommplatform.getInstance().initial(0, appInfo);

					String orientation = curCPInfo.get("Nd91Orientation");
					if (null != orientation) {
						if (orientation.equals("landscape")) {
							NdCommplatform.getInstance().ndSetScreenOrientation(NdCommplatform.SCREEN_ORIENTATION_LANDSCAPE);
						} else
						if (orientation.equals("auto")) {
							NdCommplatform.getInstance().ndSetScreenOrientation(NdCommplatform.SCREEN_ORIENTATION_AUTO);
						}
					}
				} catch (Exception e) {
					LogE("Developer info is wrong!", e);
				}
			}
		});
	}

	@Override
	public void payForProduct(Hashtable<String, String> info) {
		LogD("payForProduct invoked " + info.toString());
		if (! networkReachable()) {
			payResult(InterfaceIAP.PAYRESULT_FAIL, "网络不可用");
			return;
		}

		curProductInfo = info;
		if (curProductInfo == null) {
			payResult(InterfaceIAP.PAYRESULT_FAIL, "商品信息错误");
			return;
		}

		PluginWrapper.runOnMainThread(new Runnable() {
			@Override
			public void run() {
				if (! isLogin()) {
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
		return "Unknown version";
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
		InterfaceIAP.payResult(ret, msg);
		LogD("Nd91 result : " + ret + " msg : " + msg);
	}

	private static String getOrderSerial() {
		UUID guid = UUID.randomUUID(); 
		String text = guid.toString(); 
		text = text.replace("-", "".trim());
		return text;
	}

	private static boolean isLogin() {
		boolean bRet = NdCommplatform.getInstance().isLogined();
		LogD("isLogin : " + bRet);
		return bRet;
	}

	private static void userLogin() {
		LogD("User begin login");
		try {
	 		NdCommplatform.getInstance().ndLogin(mContext, new NdMiscCallbackListener.OnLoginProcessListener() {
    			@Override
	 			public void finishLoginProcess(int code) {
	 				if (code == NdErrorCode.ND_COM_PLATFORM_SUCCESS) {
	 					addPayment(curProductInfo);
	 				} else if (code == NdErrorCode.ND_COM_PLATFORM_ERROR_CANCEL) {
	 					payResult(InterfaceIAP.PAYRESULT_FAIL, "用户取消登录");
	 				} else {
	 					payResult(InterfaceIAP.PAYRESULT_FAIL, "用户登录失败");
	 				}
	 			}
	 		});
		} catch (Exception e) {
			payResult(InterfaceIAP.PAYRESULT_FAIL, "用户登录失败");
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
					payResult(InterfaceIAP.PAYRESULT_FAIL, "商品信息错误");
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

				String serial = IAPNd91.getOrderSerial();
				NdBuyInfo order = new NdBuyInfo();
				order.setSerial(serial);
    			order.setProductId(id);
    			order.setProductName(strName);
    			order.setProductPrice(price);
    			order.setProductOrginalPrice(fOriPrice);
    			order.setCount(count);
    			order.setPayDescription(strDesc);
    			
    			int aError = NdCommplatform.getInstance().ndUniPay(order, mContext, new NdMiscCallbackListener.OnPayProcessListener() {

					@Override
					public void finishPayProcess(int code) {
						IAPNd91.LogD("finishPayProcess code : " + code);
						switch(code){
						case NdErrorCode.ND_COM_PLATFORM_SUCCESS:
							IAPNd91.payResult(InterfaceIAP.PAYRESULT_SUCCESS, "购买成功");
						case NdErrorCode.ND_COM_PLATFORM_ERROR_PAY_FAILURE:
							IAPNd91.payResult(InterfaceIAP.PAYRESULT_FAIL, "购买失败"); break;
						case NdErrorCode.ND_COM_PLATFORM_ERROR_PAY_CANCEL:
							IAPNd91.payResult(InterfaceIAP.PAYRESULT_CANCEL, "取消购买"); break;
						default:
							IAPNd91.payResult(InterfaceIAP.PAYRESULT_FAIL, "购买失败"); break;
						}
					}
    			});

				if (aError != 0) {
					IAPNd91.payResult(InterfaceIAP.PAYRESULT_FAIL, "您输入参数有错,无法提交购买请求");
				}
			} while (false);
		} catch (Exception e) {
			LogE("Error during payment", e);
			IAPNd91.payResult(InterfaceIAP.PAYRESULT_FAIL, "支付失败");
		}
	}
}
