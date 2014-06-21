package org.cocos2dx.utils;

import java.net.HttpURLConnection;
import java.net.URL;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo.State;

public class PSNetwork {
	static ConnectivityManager mConnManager = null;

	public static void init(Context context) {
		mConnManager = (ConnectivityManager) context
				.getSystemService(Context.CONNECTIVITY_SERVICE);
	}

	public static boolean isLocalWiFiAvailable() {
		if (mConnManager == null) {
			return false;
		}
		State state = mConnManager
				.getNetworkInfo(ConnectivityManager.TYPE_WIFI).getState();
		return State.CONNECTED == state;
	}

	public static boolean isInternetConnectionAvailable() {
		if (mConnManager == null) {
			return false;
		}

		if (isLocalWiFiAvailable()) {
			return true;
		} 
		
		try {
			State state = mConnManager.getNetworkInfo(
					ConnectivityManager.TYPE_MOBILE).getState();
			return State.CONNECTED == state;
		} catch (Exception e) { 
			return false;
		}
	}

	public static boolean isHostNameReachable(String hostName) {
		int counts = 0;
		if (hostName == null || hostName.length() <= 0) {
			return false;
		}
		while (counts < 3) {
			try {
				URL url = new URL(hostName);
				int state = ((HttpURLConnection) url.openConnection())
						.getResponseCode();
				if (state == 200) {
					return true;
				}
				return false;
			} catch (Exception ex) {
				counts++;
				continue;
			}
		}
		return false;
	}

	public static int getInternetConnectionStatus() {
		if (isLocalWiFiAvailable()) {
			return 1; // wifi
		}
		if (isInternetConnectionAvailable()) {
			return 2; // gprs
		}
		return 0;
	}
}
