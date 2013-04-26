package org.cocos2dx.cocosplayer;

import java.io.IOException;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.concurrent.Semaphore;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.net.nsd.NsdManager;
import android.net.nsd.NsdManager.RegistrationListener;
import android.net.nsd.NsdManager.ResolveListener;
import android.net.nsd.NsdServiceInfo;
import android.os.Build;
import android.os.Handler;
import android.os.IBinder;
import android.util.Log;
import android.widget.Toast;

public class CocosPlayerPresence extends Service {
	private static boolean conn = false;
	private static boolean running = false;

	protected static String SERVICE_TYPE_AUTO = "_CocosPlayer._tcp.";
	protected static String SERVICE_TYPE = "_CocosP-35._tcp.";
	protected static String SERVICE_TYPE_PART1 = "_CocosP-";
	protected static String SERVICE_TYPE_PART2 = "._tcp.";

	protected static final String TAG = "CocosPlayerSocket";

	private static RegistrationListener mRegistrationListener;
	private static NsdManager.DiscoveryListener mDiscoveryListener;
	private static ResolveListener mResolveListener;

	protected static String mServiceName;
	private static NsdManager mNsdManager;
	protected static NsdServiceInfo mService;
	private static Context cw;
	private static int port = -1;

	public static void setContext(Context c) {
		cw = c;
	}

	public static void setPortAndPairing(int p, int pairingCode) {
		running = true;
		setPairing(pairingCode);
		port = p;
	}

	public static void setPairing(int code) {
		if (code == -1) {
			SERVICE_TYPE = SERVICE_TYPE_AUTO;
		} else {
			SERVICE_TYPE = SERVICE_TYPE_PART1 + Integer.toString(code)
					+ SERVICE_TYPE_PART2;
		}
	}

	public void create() {

	}

	public static int startPresence() {

		if (port < 0 || running)
			return -1;

		Log.i(TAG, "Starting NSD Service");
		running = true;
		mNsdManager = (NsdManager) cw.getSystemService(Context.NSD_SERVICE);

		initializeRegistrationListener();
		initializeResolveListener();

		registerService(port);

		return 1;
	}

	@Override
	public void onDestroy() {
		running = false;
		mNsdManager.unregisterService(mRegistrationListener);
		// mNsdManager.stopServiceDiscovery(mDiscoveryListener);
		super.onDestroy();
	}

	public static void destroy() {
		try {
			running = false;
			Log.i(TAG, "Stopping NSD Service");
			mNsdManager.unregisterService(mRegistrationListener);
		} catch(Exception e) {
			Log.e(TAG, "Error: NSD service stopped before being registered");
		}
	}

	public static void unregisterService() {
		mNsdManager.unregisterService(mRegistrationListener);
	}

	private static void registerService(int port) {
		NsdServiceInfo serviceInfo = new NsdServiceInfo();

		serviceInfo.setServiceName(Build.SERIAL + "TEST-TEST"
				+ new Date().getTime());
		serviceInfo.setServiceType(SERVICE_TYPE);
		serviceInfo.setPort(port);

		mNsdManager.registerService(serviceInfo, NsdManager.PROTOCOL_DNS_SD,
				mRegistrationListener);
	}

	@Override
	public IBinder onBind(Intent intent) {
		return null;
	}

	public static void initializeRegistrationListener() {
		mRegistrationListener = new NsdManager.RegistrationListener() {

			@Override
			public void onServiceRegistered(NsdServiceInfo NsdServiceInfo) {
				Log.i(TAG, "Service Registered");
				mServiceName = NsdServiceInfo.getServiceName();
			}

			@Override
			public void onRegistrationFailed(NsdServiceInfo serviceInfo,
					int errorCode) {
				Log.i(TAG, "Service Registeration failed" + errorCode);
			}

			@Override
			public void onServiceUnregistered(NsdServiceInfo arg0) {
			}

			@Override
			public void onUnregistrationFailed(NsdServiceInfo serviceInfo,
					int errorCode) {
			}
		};
	}

	public static void initializeDiscoveryListener() {

		mDiscoveryListener = new NsdManager.DiscoveryListener() {

			@Override
			public void onDiscoveryStarted(String regType) {
				Log.d(TAG, "Service discovery started");
			}

			@Override
			public void onServiceFound(NsdServiceInfo service) {
				Log.d(TAG, "Service discovery success");
				Log.d(TAG, String.format("%s %s %s %d",
						service.getServiceName(), service.getServiceType(),
						service.getHost(), service.getPort()));
				if (!service.getServiceType().contains(SERVICE_TYPE)) {
					Log.d(TAG,
							"Unknown Service Type: " + service.getServiceType());
				} else if (service.getServiceName().equals(mServiceName)) {
					Log.d(TAG, "Same machine: " + mServiceName);
				} else {
					mNsdManager.resolveService(service, mResolveListener);
				}
			}

			@Override
			public void onServiceLost(NsdServiceInfo service) {
				Log.e(TAG, "service lost" + service);
			}

			@Override
			public void onDiscoveryStopped(String serviceType) {
				Log.i(TAG, serviceType + " Discovery stopped: " + serviceType);
			}

			@Override
			public void onStartDiscoveryFailed(String serviceType, int errorCode) {
				Log.e(TAG, serviceType + " Discovery failed: Error code:"
						+ errorCode);
				mNsdManager.stopServiceDiscovery(this);
			}

			@Override
			public void onStopDiscoveryFailed(String serviceType, int errorCode) {
				Log.e(TAG, serviceType + " Discovery failed: Error code:"
						+ errorCode);
				mNsdManager.stopServiceDiscovery(this);
			}
		};
	}

	public static void initializeResolveListener() {
		mResolveListener = new NsdManager.ResolveListener() {

			@Override
			public void onResolveFailed(NsdServiceInfo serviceInfo,
					int errorCode) {
				Log.i(TAG, "Resolve failed" + errorCode);
			}

			@Override
			public void onServiceResolved(NsdServiceInfo serviceInfo) {
				Log.i(TAG, "Resolve Succeeded. " + serviceInfo);

				if (serviceInfo.getServiceName().equals(mServiceName)) {
					Log.d(TAG, "Same IP.");
					return;
				}
				mService = serviceInfo;

			}
		};
	}
}