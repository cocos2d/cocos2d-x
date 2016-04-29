/****************************************************************************
Copyright (c) 2013 nickflink
Copyright (c) 2014 martell malone <martell malone at  mail dot com>
Copyright (c) 2014 cocos2d-x.org
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

// NB. All Util classes are From google Jan 2014 and a subject to their respective Apache License 
// (We can update to newer versions when they are added)

package org.cocos2dx.plugin;

import java.util.Hashtable;

import org.cocos2dx.plugin.util.IabHelper;
import org.cocos2dx.plugin.util.IabResult;
import org.cocos2dx.plugin.util.Inventory;
import org.cocos2dx.plugin.util.Purchase;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.util.Log;


public class IAPGooglePlay implements InterfaceIAP, PluginListener {

    // Debug tag, for logging
    static final String TAG = "IAPGooglePlay";

    // (arbitrary) request code for the purchase flow
    static final int RC_REQUEST = 10001;

    // The helper object
    IabHelper mHelper;

    static boolean bDebug = false;
    Context mContext;
    static InterfaceIAP mAdapter;

    protected static void LogE(String msg, Exception e) {
        Log.e(TAG, msg, e);
        e.printStackTrace();
    }

    protected static void LogD(String msg) {
        if (bDebug) {
            Log.d(TAG, msg);
        }
    }

    public IAPGooglePlay(Context context) {
        mContext = context;
        mAdapter = this;
    }

    private Context getContext() {
        return mContext;
    }

    private Activity getActivity() {
            return (Activity) mContext;
    }

    @Override
    public void configDeveloperInfo(Hashtable<String, String> cpInfo) {
        LogD("initDeveloperInfo invoked " + cpInfo.toString());
        try {
            //String appId = cpInfo.get("GooglePlayAppId");
            final String appKey = cpInfo.get("GooglePlayAppKey");
            PluginWrapper.runOnMainThread(new Runnable() {
                @Override
                public void run() {
                    initWithKey(appKey);
                }
            });
        } catch (Exception e) {
            LogE("Developer info is wrong!", e);
        }
    }

    @Override
    public void payForProduct(Hashtable<String, String> info) {
        LogD("payForProduct invoked " + info.toString());
        if (! networkReachable()) {
            payResult(IAPWrapper.PAYRESULT_FAIL, "Network Unreachable");
            return;
        }

        final Hashtable<String, String> productInfo = info;
        PluginWrapper.runOnMainThread(new Runnable() {
            @Override
            public void run() {
                String iapId = productInfo.get("IAPId");
                String iapSecKey = productInfo.get("IAPSecKey");
                try{
                	mHelper.launchPurchaseFlow(getActivity(), iapId, RC_REQUEST, mPurchaseFinishedListener, iapSecKey);
                }
                catch(IllegalStateException ex){
                	LogD("Please retry in a few seconds.");
                    mHelper.flagEndAsync();
                }
            }
        });
    }

    @Override
    public void setDebugMode(boolean debug) {
        //TODO: fix this
        //It's possible setDebug don't work at the first time because init was happening on another thread
        bDebug = debug;
        if (mHelper != null) {
            mHelper.enableDebugLogging(debug);
        }
    }

    @Override
    public String getSDKVersion() {
        return "IAPv3Jan2014";
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
        LogD("GooglePlay result : " + ret + " msg : " + msg);
    }

    @Override
    public String getPluginVersion() {
        return "0.3.0";
    }

    /* base64EncodedPublicKey should be YOUR APPLICATION'S PUBLIC KEY
     * (that you got from the Google Play developer console). This is not your
     * developer public key, it's the *app-specific* public key.
     *
     * Instead of just storing the entire literal string here embedded in the
     * program,  construct the key at runtime from pieces or
     * use bit manipulation (for example, XOR with some other string) to hide
     * the actual key.  The key itself is not secret information, but we don't
     * want to make it easy for an attacker to replace the public key with one
     * of their own and then fake messages from the server.
     */
    public void initWithKey(String base64EncodedPublicKey) {
        
        // Create the helper, passing it our context and the public key to verify signatures with
        Log.d(TAG, "Creating IAB helper.");
        //mHelper = new IabHelper(this, base64EncodedPublicKey);
        mHelper = new IabHelper(getContext(), base64EncodedPublicKey);

        // Start setup. This is asynchronous and the specified listener
        // will be called once setup completes.
        Log.d(TAG, "Starting setup.");
        mHelper.startSetup(new IabHelper.OnIabSetupFinishedListener() {
            public void onIabSetupFinished(IabResult result) {
                Log.d(TAG, "Setup finished.");

                if (!result.isSuccess()) {
                    // Oh noes, there was a problem.
                    Log.e(TAG,"Problem setting up in-app billing: " + result);
                    return;
                }

                // Hooray, IAB is fully set up. Now, let's get an inventory of stuff we own.
                Log.d(TAG, "Setup successful. Querying inventory.");
                mHelper.queryInventoryAsync(mGotInventoryListener);
            }
        });
        
        PluginWrapper.addListener(this);
    }



    // Listener that's called when we finish querying the items and subscriptions we own
    IabHelper.QueryInventoryFinishedListener mGotInventoryListener = new IabHelper.QueryInventoryFinishedListener() {
        public void onQueryInventoryFinished(IabResult result, Inventory inventory) {
            Log.d(TAG, "Query inventory finished.");

            // Have we been disposed of in the meantime? If so, quit.
            if (mHelper == null) return;

            // Is it a failure?
            if (result.isFailure()) {
                Log.e(TAG, "Failed to query inventory: " + result);
                return;
            }

            Log.d(TAG, "Query inventory was successful.");

            //start. you can add you own query code here for flushing if you wish

            //end
        }
    };

    public void refreshPurchases() {
        Log.e(TAG, "TODO implement refreshPurchases");
    }

    /** Verifies the developer payload of a purchase. */
    boolean verifyDeveloperPayload(Purchase p) {
        String payload = p.getDeveloperPayload();

        /*
         * TODO: verify that the developer payload of the purchase is correct. It will be
         * the same one that you sent when initiating the purchase.
         *
         * WARNING: Locally generating a random string when starting a purchase and
         * verifying it here might seem like a good approach, but this will fail in the
         * case where the user purchases an item on one device and then uses your app on
         * a different device, because on the other device you will not have access to the
         * random string you originally generated.
         *
         * So a good developer payload has these characteristics:
         *
         * 1. If two different users purchase an item, the payload is different between them,
         *    so that one user's purchase can't be replayed to another user.
         *
         * 2. The payload must be such that you can verify it even when the app wasn't the
         *    one who initiated the purchase flow (so that items purchased by the user on
         *    one device work on other devices owned by the user).
         *
         * Using your own server to store and verify developer payloads across app
         * installations is recommended.
         */

        return true;
    }

    // Callback for when a purchase is finished
    IabHelper.OnIabPurchaseFinishedListener mPurchaseFinishedListener = new IabHelper.OnIabPurchaseFinishedListener() {
        @Override
        public void onIabPurchaseFinished(IabResult result, Purchase purchase) {
        	
            if (result.isFailure()) {
                 Log.d(TAG, "Error purchasing: " + result);

                failPurchase(result.getMessage());
                return;
            }
            else {
                Log.d(TAG,"Success!");
                
                succeedPurchase(result.getMessage());

                //Auto consume the purchase
                mHelper.consumeAsync(purchase, mConsumeFinishedListener);
            }
        }
    };

    // Called when consumption is complete
    IabHelper.OnConsumeFinishedListener mConsumeFinishedListener = new IabHelper.OnConsumeFinishedListener() {
        public void onConsumeFinished(Purchase purchase, IabResult result) {
            Log.d(TAG, "Consumption finished. Purchase: " + purchase + ", result: " + result);

            if (result.isSuccess()) {
                Log.d(TAG, "Consumption successful. Provisioning.");
            }
            else {
                Log.e(TAG,"Error while consuming: " + result);
            }
            setWaitScreen(false);
            Log.d(TAG, "End consumption flow.");
        }
    };

    void succeedPurchase(String msg) {
        IAPWrapper.onPayResult(mAdapter, IAPWrapper.PAYRESULT_SUCCESS, msg);
        
    }

    void failPurchase(String msg) {
        IAPWrapper.onPayResult(mAdapter, IAPWrapper.PAYRESULT_FAIL, msg);
    }

    // Enables or disables the "please wait" screen.
    void setWaitScreen(boolean set) {
        //Log.e(TAG, "ERROR: need to implement setWaitScreen");
        //findViewById(R.id.screen_main).setVisibility(set ? View.GONE : View.VISIBLE);
        //findViewById(R.id.screen_wait).setVisibility(set ? View.VISIBLE : View.GONE);
    }

    void alert(String message) {
        AlertDialog.Builder bld = new AlertDialog.Builder(getContext());
        bld.setMessage(message);
        bld.setNeutralButton("OK", null);
        Log.d(TAG, "Showing alert dialog: " + message);
        bld.create().show();
    }
    
    //@Override
    /**
     * Handle activity result. Call this method from your Activity's
     * onActivityResult callback.
     * @return 
     */
    public boolean onActivityResult(int requestCode, int resultCode, Intent data) {
        LogD("onActivityResult("+requestCode+", "+resultCode+", data)");
        return mHelper.handleActivityResult(requestCode, resultCode, data);
    }
    
	@Override
	public void onResume() {
	}

	@Override
	public void onPause() {
	}

	@Override
	public void onDestroy() {
		PluginWrapper.removeListener(this);
	}
}