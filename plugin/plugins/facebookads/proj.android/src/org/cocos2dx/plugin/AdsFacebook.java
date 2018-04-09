package org.cocos2dx.plugin;
import java.util.HashSet;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.Set;

import org.cocos2dx.plugin.AdsWrapper;
import org.cocos2dx.plugin.InterfaceAds;
import org.cocos2dx.plugin.PluginWrapper;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.content.Context;
import android.util.Log;
import android.view.Gravity;
import android.view.WindowManager;
import android.widget.LinearLayout;
import android.widget.LinearLayout.LayoutParams;

import com.cocos2dx.plugin.R;
import com.facebook.ads.*;

public class AdsFacebook implements InterfaceAds{

	private static final String LOG_TAG = "AdsFacebook";
	private static Activity mContext = null;
	private static boolean bDebug = false;
	private static AdsFacebook mAdapter = null;

	private String mPublishID = "";
	private Set<String> mTestDevices = null;
//	private WindowManager mWm = null;
	private LinearLayout facebookAdContainer = null;
	
	private AdView adView;
    private InterstitialAd interstitialAd;
    
	private static final int FB_AD_SIZE_DEFAULT = 1;
	private static final int FB_AD_SIZE_HEIGHT_FIXED = 2;
	private static final int FB_AD_SIZE_INTERSTITIAL = 3;
    
    private static final int FB_AD_TYPE_BANNER = 1;
	private static final int FB_AD_TYPE_INTERSTITIAL = 2;
    
	protected static void LogE(String msg, Exception e) {
		Log.e(LOG_TAG, msg, e);
		e.printStackTrace();
	}

	protected static void LogD(String msg) {
		if (bDebug) {
			Log.d(LOG_TAG, msg);
		}
	}

	public AdsFacebook(Context context) {
		mContext = (Activity) context;
		mAdapter = this;
	}
	
    @Override
	public void setDebugMode(boolean debug) {
		bDebug = debug;
	}

	@Override
	public String getSDKVersion() {
		return "3.17.2";
	}

	@Override
	public void configDeveloperInfo(Hashtable<String, String> devInfo) {
		try {
			mPublishID = devInfo.get("FacebookAdID");
			LogD("init AppInfo : " + mPublishID);
		} catch (Exception e) {
			LogE("initAppInfo, The format of appInfo is wrong", e);
		}
	}
	
	private void loadInterstitial() {
		
		PluginWrapper.runOnMainThread(new Runnable() {
			
			@Override
			public void run() {
					
				interstitialAd = new InterstitialAd(mContext, mPublishID);
				
		        // Set a listener to get notified on changes or when the user interact with the ad.
		        interstitialAd.setAdListener(new FacebookAdsListener());
		
		        if(mTestDevices != null)
					AdSettings.addTestDevices(mTestDevices);
				else if(bDebug == true)
					LogD("You must specify hash id, see the log");
		        
		        // Load a new interstitial.
		        interstitialAd.loadAd();
			} 
		});
		
	}
	
	@Override
	public void showAds(Hashtable<String, String> info, int pos) {
	    try
	    {
	        String strType = info.get("FBAdType");
	        int adsType = Integer.parseInt(strType);

	        switch (adsType) {
	        case FB_AD_TYPE_BANNER:
	            {
	                String strSize = info.get("FBAdSizeEnum");
	                int sizeEnum = Integer.parseInt(strSize);
    	            showBannerAd(sizeEnum, pos);
                    break;
	            }
	        case FB_AD_TYPE_INTERSTITIAL:
	            loadInterstitial();
	            break;
	        default:
	            break;
	        }
	    } catch (Exception e) {
	        LogE("Error when show Ads ( " + info.toString() + " )", e);
	    }
	}

	@Override
	public void spendPoints(int points) {
		LogD("Admob not support spend points!");
	}
	
	@Override
	public void hideAds(Hashtable<String, String> info) {
	    try
        {
            String strType = info.get("FBAdType");
            int adsType = Integer.parseInt(strType);

            switch (adsType) {
            case FB_AD_TYPE_BANNER:
                hideBannerAd();
                break;
            case FB_AD_TYPE_INTERSTITIAL:
                LogD("Not Necessary");
                break;
            default:
                break;
            }
        } catch (Exception e) {
            LogE("Error when hide Ads ( " + info.toString() + " )", e);
        }
	}
	
	private void showBannerAd(int sizeEnum, int pos) {
		final int curPos = pos;
		final int curSize = sizeEnum;

		PluginWrapper.runOnMainThread(new Runnable() {

			@Override
			public void run() {
				// destory the ad view before
//				if (null != adView) {
//					if (null != mWm) {
//						mWm.removeView(adView);
//					}
//					adView.destroy();
//					adView = null;
//				}
				
				if(null != adView){
					if(null != facebookAdContainer){
						facebookAdContainer.removeView(adView);
					}
					adView.destroy();
					adView = null;
				}

				AdSize size = AdSize.BANNER_320_50;
				switch (curSize) {
				case AdsFacebook.FB_AD_SIZE_DEFAULT:
					size = AdSize.BANNER_320_50;
					break;
				case AdsFacebook.FB_AD_SIZE_HEIGHT_FIXED:
				case AdsFacebook.FB_AD_SIZE_INTERSTITIAL:
				{
					 boolean isTablet = mContext.getResources().getBoolean(R.bool.is_tablet);
				     size = isTablet ? AdSize.BANNER_HEIGHT_90 : AdSize.BANNER_HEIGHT_50;
				}
					break;
				default:
					break;
				}
				
				adView = new AdView(mContext, mPublishID, size);				
//				try {
//					if (mTestDevices != null) {
//						Iterator<String> ir = mTestDevices.iterator();
//						while(ir.hasNext())
//						{
//							addTestDevice(ir.next());
//						}
//					}
//				} catch (Exception e) {
//					LogE("Error during add test device", e);
//				}
				
				if(mTestDevices != null)
					AdSettings.addTestDevices(mTestDevices);
				else if(bDebug == true)
					LogD("You must specify hash id, see the log");
				
				adView.setAdListener(new FacebookAdsListener());
				adView.loadAd();

//				if (null == mWm) {
//					mWm = (WindowManager) mContext.getSystemService("window");
//				}
				
				//AdsWrapper.addAdView(mWm, adView, curPos);
				
				facebookAdContainer = new LinearLayout(mContext);
				facebookAdContainer.setGravity(Gravity.BOTTOM);
				facebookAdContainer.addView(adView);
			        mContext.addContentView(facebookAdContainer, new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT));
			}
		});
	}
	
	private void hideBannerAd() {
		PluginWrapper.runOnMainThread(new Runnable() {
			@Override
			public void run() {
//				if (null != adView) {
//					if (null != mWm) {
//						mWm.removeView(adView);
//					}
//					adView.destroy();
//					adView = null;
//				}
				if (null != adView) {
					if (null != facebookAdContainer) {
						facebookAdContainer.removeView(adView);
					}
					adView.destroy();
					adView = null;
				}
			}
		});
	}

	protected void addTestDevice(String deviceID) {
		LogD("addTestDevice invoked:" + deviceID);
		if (null == mTestDevices) {
			mTestDevices = new HashSet<String>();
		}
			mTestDevices.add(deviceID);
		
	}

	private class FacebookAdsListener implements InterstitialAdListener {
	
		 @Override
		    public void onError(Ad ad, AdError error) {
		     
		    }
	
		    @Override
		    public void onAdLoaded(Ad ad) {
		    	 if (ad == adView) {
		         } else if (ad == interstitialAd) {
		        	 
//		        	 PluginWrapper.runOnMainThread(new Runnable() {
//						
//						@Override
//						public void run() {
//							 
//						}
//					});
		        	
			    	 interstitialAd.show();
		         }
		    	 
		    }
	
		    @Override
		    public void onInterstitialDisplayed(Ad ad) {
		    	LogD("onPresentScreen invoked");
				AdsWrapper.onAdsResult(mAdapter, AdsWrapper.RESULT_CODE_AdsShown, "Ads view shown!");
		    }
	
		    @Override
		    public void onInterstitialDismissed(Ad ad) {
		        // Cleanup.
		        ad.destroy();
		        ad = null;
		    }
	
		    @Override
		    public void onAdClicked(Ad ad) {
		    	
		    }
	}

	@Override
	public String getPluginVersion() {
		return "1.0";
	}
	
	@Override
	public void queryPoints() {
	}
}
