package org.cocos2dx.lib;

import java.io.File;
import java.io.FileOutputStream;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import org.json.JSONArray;
import org.json.JSONObject;
import org.apache.http.Header;

import com.loopj.android.http.AsyncHttpClient;
import com.loopj.android.http.FileAsyncHttpResponseHandler;
import com.loopj.android.http.JsonHttpResponseHandler;

import dalvik.system.DexClassLoader;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothClass;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.net.Uri;
import android.os.Environment;
import android.util.Log;
import android.util.SparseIntArray;
import android.view.InputDevice;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.widget.Toast;

public class GameControllerHelper {

	private final static String TAG = GameControllerHelper.class.getSimpleName();
	
	public static final String StandardControllerName = "Standard";	
	public static final String[] DRIVERS_NAME = {"nibiru","moga","ouya",StandardControllerName};
	
	public static final int DRIVERTYPE_NIBIRU = 0;
	public static final int DRIVERTYPE_MOGA = 1;
	public static final int DRIVERTYPE_OUYA = 2;
	public static final int DRIVERTYPE_STANDARD = 3;
	public static final int DRIVERTYPE_UNKNOWN = 4;
	
	public static final String SPP_UUID = "00001101-0000-1000-8000-00805F9B34FB";
	
	SparseIntArray ControllerKeyMap;
	
	private static final String COCOS_CONTROLLER_URL = "http://115.28.134.83:9000/download/cocoscontroller/";
	private static final String COCOS_CONTROLLER_CONFIG = "controller.json";
	
	private static final String NIBIRU_DEP_PACKAGE = "com.nibiru";
	private static final String MOGA__DEP_PACKAGE = "com.bda.pivot.mogapgp";
	//private static final String OUYA_FRAMEWORK_PACKAGE = "tv.ouya";
	//private static final String OUYA_LAUNCHER_PACKAGE = "tv.ouya.console";
	
	private static Cocos2dxActivity sCocos2dxActivity;
	private static GameControllerHelper sControllerHelper;
	
	private List<String>  mNibiruSupportedDrives;
	private String  mNibiruDepFileName;
	private String  mNibiruLibFileName;
	private int mNibiruLibFileSize;
	private int mNibiruDepFileSize;
	
	private List<String> mMogaSupportedDrives;
	private String  mMogaDepFileName;
	private String  mMogaLibFileName;
	private int mMogaLibFileSize;
	private int mMogaDepFileSize;
	
	private List<String> mOuyaSupportedDrives;
	//private String  mOuyaFrameworkFileName;
	//private String  mOuyaLauncherFileName;
	private String  mOuyaLibFileName;
	private int mOuyaLibFileSize;
	
	private AsyncHttpClient mDownDepsHttpClient = null;	
	
	private BluetoothAdapter mBluetoothAdapter = null;
	private ArrayList<BluetoothDevice> mBluetoothDevices = null;
	private SparseIntArray mDevicesDriver;
	private int mClearDevices = 0;
	
	private String mConfigFilePath;
	private String mLocalSavePath = null;
	
	private boolean mLazyInit = true;
	private boolean mLazyConfigInit = true;
	private static ControllerListener mControllerListener = null;
	
	public static interface ControllerListener{
		void onDownloadConfigStarted();
		void onDownloadConfigFinished(boolean isSuccess);
		
		void onControllerDiscoveryStarted();
		//
		void onControllerDiscoveryFinish(ArrayList<BluetoothDevice> devices);
		
		void onDownloadDepsStarted();
		void onDownloadDepsProgress(int bytesWritten, int totalSize);
		void onDownloadDepsFinished(boolean isSuccess);
		
		void onInstallDriver(String filePath);
		void onConnectController();
	}
	
	public void setControllerListener(ControllerListener listener){
		mControllerListener = listener;
	}
	
	public GameControllerHelper(Cocos2dxActivity activity){
		sCocos2dxActivity = activity;
		sControllerHelper = this;
		
		ControllerKeyMap = new SparseIntArray(25);
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_A, GameControllerDelegate.BUTTON_A);
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_B, GameControllerDelegate.BUTTON_B);
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_C, GameControllerDelegate.BUTTON_C);
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_X, GameControllerDelegate.BUTTON_X);
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_Y, GameControllerDelegate.BUTTON_Y);
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_Z, GameControllerDelegate.BUTTON_Z);
		
		ControllerKeyMap.put(KeyEvent.KEYCODE_DPAD_UP, GameControllerDelegate.BUTTON_DPAD_UP);
		ControllerKeyMap.put(KeyEvent.KEYCODE_DPAD_DOWN, GameControllerDelegate.BUTTON_DPAD_DOWN);
		ControllerKeyMap.put(KeyEvent.KEYCODE_DPAD_LEFT, GameControllerDelegate.BUTTON_DPAD_LEFT);
		ControllerKeyMap.put(KeyEvent.KEYCODE_DPAD_RIGHT, GameControllerDelegate.BUTTON_DPAD_RIGHT);
		ControllerKeyMap.put(KeyEvent.KEYCODE_DPAD_CENTER, GameControllerDelegate.BUTTON_DPAD_CENTER);
		
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_THUMBL, GameControllerDelegate.BUTTON_LEFT_THUMBSTICK);
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_THUMBR, GameControllerDelegate.BUTTON_RIGHT_THUMBSTICK);
		
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_L1, GameControllerDelegate.BUTTON_LEFT_SHOULDER);
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_R1, GameControllerDelegate.BUTTON_RIGHT_SHOULDER);
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_L2, GameControllerDelegate.BUTTON_LEFT_TRIGGER);
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_R2, GameControllerDelegate.BUTTON_RIGHT_TRIGGER);
				
		ControllerKeyMap.put(MotionEvent.AXIS_X, GameControllerDelegate.THUMBSTICK_LEFT_X);
		ControllerKeyMap.put(MotionEvent.AXIS_Y, GameControllerDelegate.THUMBSTICK_LEFT_Y);
		ControllerKeyMap.put(MotionEvent.AXIS_RX, GameControllerDelegate.THUMBSTICK_RIGHT_X);
		ControllerKeyMap.put(MotionEvent.AXIS_RY, GameControllerDelegate.THUMBSTICK_RIGHT_Y);
		
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_START, GameControllerDelegate.BUTTON_START);
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_SELECT, GameControllerDelegate.BUTTON_SELECT);
		//KEYCODE_BUTTON_MODE
	}
	
	public void connectController(){
		if (mLazyInit) {
			mLazyInit = false;
			mNibiruSupportedDrives = new ArrayList<String>(30);
			mMogaSupportedDrives = new ArrayList<String>(5);
			mOuyaSupportedDrives = new ArrayList<String>(5);
			
			mLocalSavePath = Environment.getExternalStorageDirectory() + File.separator + "CocosGameController" + File.separator;
			mConfigFilePath = sCocos2dxActivity.getFilesDir().getAbsolutePath() + File.separator + COCOS_CONTROLLER_CONFIG;
			mDownDepsHttpClient = new AsyncHttpClient();
			mDownDepsHttpClient.setTimeout(360 * 1000);
		}
		
		if (mControllerListener != null) {
			mControllerListener.onDownloadConfigStarted();
		}
		if (mLazyConfigInit) {
			if (mDownDepsHttpClient != null) {
				mDownDepsHttpClient.cancelRequests(sCocos2dxActivity, true);
			}
			requestControllerConfig();
		}
		else {
			scanBluetoothDrive();
		}
	}
	
	public Set<BluetoothDevice> getBondedDevices(){
		if (mBluetoothAdapter == null) {
			mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
			if (mBluetoothAdapter == null) {
				return null;
			}
		}
		
		return mBluetoothAdapter.getBondedDevices();
	}
	
	public void destrory(){
		if (mDownDepsHttpClient != null) {
			mDownDepsHttpClient.cancelRequests(sCocos2dxActivity, true);
		}
	}
	
	private boolean scanBluetoothDrive(){
		if (mControllerListener != null) {
			mControllerListener.onDownloadConfigFinished(true);
		}
		
		if (mBluetoothAdapter == null) {
			mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
			if (mBluetoothAdapter == null) {
				return false;
			}
			
			if (mBluetoothDevices == null) {
				mBluetoothDevices = new ArrayList<BluetoothDevice>(5);
				mDevicesDriver = new SparseIntArray();
			}
			
			IntentFilter filter = new IntentFilter(BluetoothDevice.ACTION_FOUND);
			//filter.addAction(BluetoothDevice.ACTION_BOND_STATE_CHANGED);
			//filter.addAction(BluetoothAdapter.ACTION_SCAN_MODE_CHANGED);
			//filter.addAction(BluetoothAdapter.ACTION_STATE_CHANGED);
			filter.addAction(BluetoothAdapter.ACTION_DISCOVERY_FINISHED);
			filter.addAction(BluetoothAdapter.ACTION_DISCOVERY_STARTED);
			sCocos2dxActivity.registerReceiver(mBluetoothReceiver, filter);	
			
			IntentFilter appFilter = new IntentFilter();
			appFilter.addAction("android.intent.action.PACKAGE_ADDED");
			appFilter.addDataScheme("package");
			sCocos2dxActivity.registerReceiver(mAppReceiver, appFilter);
		}
		
		if (!mBluetoothAdapter.isEnabled()) {
			mBluetoothAdapter.enable();
		}
		
		if (mBluetoothAdapter.isDiscovering()) {
			mBluetoothAdapter.cancelDiscovery();
		}
		
		mBluetoothAdapter.startDiscovery();
		
		return true;
	}

	public int checkDriverType(BluetoothDevice device){
		String deviceName = device.getName();
		
		if (mNibiruSupportedDrives.contains(deviceName)) {			
			return DRIVERTYPE_NIBIRU;
		}
		else if (mMogaSupportedDrives.contains(deviceName)) {
			return DRIVERTYPE_MOGA;
		}
		else if (mOuyaSupportedDrives.contains(deviceName)) {
			return DRIVERTYPE_OUYA;
		}
		else {
			
		}
		
		return DRIVERTYPE_UNKNOWN;
	}
	
	public static void installApplication(String filePath){
		if (sCocos2dxActivity != null) {
			Intent intent = new Intent();
			intent.setAction(Intent.ACTION_VIEW);
			intent.setDataAndType(Uri.parse("file://" + filePath), "application/vnd.android.package-archive");
			intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
			sCocos2dxActivity.startActivity(intent);
		}
	}
	
	public static boolean checkApplication(String packName){
		try {
			ApplicationInfo applicationInfo = sCocos2dxActivity.getPackageManager().getApplicationInfo(packName, PackageManager.GET_UNINSTALLED_PACKAGES);
			Log.d(TAG, applicationInfo.toString());
			return true;
		} catch (NameNotFoundException e) {
			return false;
		}
	}
		
	private BroadcastReceiver mBluetoothReceiver = new BroadcastReceiver() {
		
		@Override
		public void onReceive(Context context, Intent intent) {
			String action = intent.getAction();
			
			if (BluetoothDevice.ACTION_FOUND.equals(action)) {				
				BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
				if (mBluetoothDevices.contains(device)) {
					return;
				}
				
				String deviceName = device.getName();
				
				if(device.getBluetoothClass().getMajorDeviceClass() == BluetoothClass.Device.Major.COMPUTER 
						|| device.getBluetoothClass().getMajorDeviceClass() == BluetoothClass.Device.Major.PHONE)
				{
					Log.w(TAG, "Remote device discovered :" + deviceName + " is computer or phone.");
					return;
				}
				
				mBluetoothDevices.add(device);
				int type = checkDriverType(device);
				if (type != DRIVERTYPE_UNKNOWN) {
					mClearDevices += 1;
				}
				mDevicesDriver.append(mBluetoothDevices.size() - 1, type);
			}
			else if (BluetoothAdapter.ACTION_DISCOVERY_FINISHED.equals(action)) {
				Log.d(TAG, "The local Bluetooth adapter has finished the device discovery process.");
				
				if (mControllerListener != null) {
					mControllerListener.onControllerDiscoveryFinish(mBluetoothDevices);
				}
				else {
					if (mBluetoothDevices.size() == 0) {
						Log.w(TAG, "Not found any supported bluetooth game controller!");
					}else {
						if (mClearDevices == 1) {
							for (int i = 0; i < mDevicesDriver.size(); i++) {
								if (mDevicesDriver.valueAt(i) != DRIVERTYPE_UNKNOWN) {
									Log.w(TAG, "downControllerDeps:" + i);
									downControllerDeps(mDevicesDriver.valueAt(i));
									break;
								}
							}
						}
						else {
							Log.i(TAG, "More than one device");
							//todo:show sel
						}
					}					
				}				
			}
			else if (BluetoothAdapter.ACTION_DISCOVERY_STARTED.equals(action)) {
				Log.d(TAG, "The local Bluetooth adapter has started the remote device discovery process.");
				if(mControllerListener != null){
					mControllerListener.onControllerDiscoveryStarted();
				}
				
				mBluetoothDevices.clear();
				mDevicesDriver.clear();
				mClearDevices = 0;
				
				Iterator<BluetoothDevice> it = mBluetoothAdapter.getBondedDevices().iterator();
				while (it.hasNext()) {
					BluetoothDevice device = it.next();
					if(device.getBluetoothClass().getMajorDeviceClass() != BluetoothClass.Device.Major.COMPUTER 
							&& device.getBluetoothClass().getMajorDeviceClass() != BluetoothClass.Device.Major.PHONE)
					{
						if (!mBluetoothDevices.contains(device)) {
							mBluetoothDevices.add(device);
							int type = checkDriverType(device);
							if (type != DRIVERTYPE_UNKNOWN) {
								mClearDevices += 1;
							}
							mDevicesDriver.append(mBluetoothDevices.size() - 1, type);
						}
					}
				}
			}
		}
	};
	
	private static int depsCount = 0;
	private static int mTargetDriver = DRIVERTYPE_UNKNOWN;
	
	private static int mDownloadTotalSize;
	private static int mDownloadLibSize;
	private static int mLibDownloadCompletedSize;
	private static int mDepDownloadCompletedSize;
	
	public void downControllerDeps(int driverType){
		if (driverType == DRIVERTYPE_STANDARD || driverType == DRIVERTYPE_UNKNOWN) {
			
			return;
		}
		if (mControllerListener != null) {
			mControllerListener.onDownloadDepsStarted();
		}
		mDownloadTotalSize = 0;
		mLibDownloadCompletedSize = 0;
		mDepDownloadCompletedSize = 0;
		
		mTargetDriver = driverType;
		depsCount = 1;
		
		GameControllerUtils.ensureDirectoryExist(mLocalSavePath);
		
		String remoteDir = COCOS_CONTROLLER_URL + DRIVERS_NAME[driverType] + File.separator;
		
		if (driverType == DRIVERTYPE_NIBIRU) {
			mDownloadLibSize = mNibiruLibFileSize;
			mDownloadTotalSize += mNibiruLibFileSize;
			if (!checkApplication(NIBIRU_DEP_PACKAGE)) {
				depsCount += 1;
				mDownloadTotalSize += mNibiruDepFileSize;
				mDownDepsHttpClient.get(remoteDir + mNibiruDepFileName, new MyDepsAsyncHandler(
						new File(mLocalSavePath + mNibiruDepFileName), MyDepsAsyncHandler.FILETYPE_DEP_APK));
			}
			
			mDownDepsHttpClient.get(remoteDir + mNibiruLibFileName, new MyDepsAsyncHandler(
					new File(mLocalSavePath + mNibiruLibFileName), MyDepsAsyncHandler.FILETYPE_JAR));
		}
		else if (driverType == DRIVERTYPE_MOGA) {
			mDownloadLibSize = mMogaLibFileSize;
			mDownloadTotalSize += mMogaLibFileSize;
			if (!checkApplication(MOGA__DEP_PACKAGE)) {
				mDownloadTotalSize += mMogaDepFileSize;
				depsCount += 1;
				mDownDepsHttpClient.get(remoteDir + mMogaDepFileName, new MyDepsAsyncHandler(
						new File(mLocalSavePath + mMogaDepFileName), MyDepsAsyncHandler.FILETYPE_DEP_APK));
			}
			
			mDownDepsHttpClient.get(remoteDir + mMogaLibFileName, new MyDepsAsyncHandler(
					new File(mLocalSavePath + mMogaLibFileName), MyDepsAsyncHandler.FILETYPE_JAR));	
		}
		else if(driverType == DRIVERTYPE_OUYA){
			mDownloadLibSize = mOuyaLibFileSize;
			mDownloadTotalSize += mOuyaLibFileSize;
			/*if (!checkApplication(OUYA_FRAMEWORK_PACKAGE)) {
				depsCount += 1;
				mDownDepsHttpClient.get(remoteDir + mOuyaFrameworkFileName, new MyDepsAsyncHandler(
						new File(mLocalSavePath + mOuyaFrameworkFileName),MyDepsAsyncHandler.FILETYPE_DEP_APK));
			}
			if (!checkApplication(OUYA_LAUNCHER_PACKAGE)) {
				depsCount += 1;
				mDownDepsHttpClient.get(remoteDir + mOuyaLauncherFileName, new MyDepsAsyncHandler(
						new File(mLocalSavePath + mOuyaLauncherFileName),MyDepsAsyncHandler.FILETYPE_DEP_APK));
			}*/
			
			mDownDepsHttpClient.get(remoteDir + mOuyaLibFileName, new MyDepsAsyncHandler(
					new File(mLocalSavePath + mOuyaLibFileName), MyDepsAsyncHandler.FILETYPE_JAR));
		}
	}
	
	static class MyDepsAsyncHandler extends FileAsyncHttpResponseHandler{

		public static final int FILETYPE_DEP_APK = 0;
		public static final int FILETYPE_JAR = 1;
		
		private int mFileType = FILETYPE_DEP_APK;
		
		public MyDepsAsyncHandler(File file, int fileType) {
			super(file);
			mFileType = fileType;
		}
		
		@Override
		public void onFailure(int statusCode, Header[] headers,
				Throwable e, File file) {
			if (mFileType == FILETYPE_JAR) {
				if (file.exists() && file.length() == mDownloadLibSize) {										
					depsCount -= 1;
					if (depsCount == 0) {
						if (mControllerListener != null) {
							mControllerListener.onDownloadDepsFinished(true);
						}
						sControllerHelper.onDepsReady();
					}
				}
			}
			else if (mFileType == FILETYPE_DEP_APK) {
				if (mControllerListener != null) {
					mControllerListener.onDownloadDepsFinished(false);
				}
			}
			
			Log.e(TAG,"Failed to download:" + file.getName());
		}
		
		@Override
		public void onSuccess(File file) {
			Log.d(TAG, "Down file success:" + file.getName());
			
			depsCount -= 1;
			if (depsCount == 0) {
				if (mControllerListener != null) {
					mControllerListener.onDownloadDepsFinished(true);
				}
				sControllerHelper.onDepsReady();
			}
		}
		
		@Override
		public void onProgress(int bytesWritten, int totalSize) {
			if (mFileType == FILETYPE_JAR) {
				mLibDownloadCompletedSize = bytesWritten;
			} else {
				mDepDownloadCompletedSize = bytesWritten;
			}
			if (mControllerListener != null) {
				
				mControllerListener.onDownloadDepsProgress(mLibDownloadCompletedSize + mDepDownloadCompletedSize, mDownloadTotalSize);
			}
			Log.d(TAG, "totalSize:" + totalSize + ", bytesWritten:" + bytesWritten);
		}
	}
	
	private void onDepsReady(){
		Log.d(TAG, "onDepsReady:" + mTargetDriver);
		
		if (mTargetDriver == DRIVERTYPE_NIBIRU) {
			if (checkApplication(NIBIRU_DEP_PACKAGE)) {
				createControllerInstance(mLocalSavePath + mNibiruLibFileName, mTargetDriver);
			}
			else {
				if (mControllerListener != null) {
					mControllerListener.onInstallDriver(mLocalSavePath + mMogaDepFileName);
				}
				installApplication(mLocalSavePath + mNibiruDepFileName);
			}
		}
		else if (mTargetDriver == DRIVERTYPE_MOGA) {
			if (checkApplication(MOGA__DEP_PACKAGE)) {
				createControllerInstance(mLocalSavePath + mMogaLibFileName, mTargetDriver);
			}
			else {
				if (mControllerListener != null) {
					mControllerListener.onInstallDriver(mLocalSavePath + mMogaDepFileName);
				}
				installApplication(mLocalSavePath + mMogaDepFileName);
			}
		} 
		else if (mTargetDriver == DRIVERTYPE_OUYA) {
			/*if (checkApplication(OUYA_FRAMEWORK_PACKAGE)) {
				if (checkApplication(OUYA_LAUNCHER_PACKAGE)) {
					createControllerInstance(mLocalSavePath + mOuyaLibFileName, mTargetSDK);
				}
				else {
					installApplication(mLocalSavePath + mOuyaLauncherFileName);
				}
			}
			else {
				installApplication(mLocalSavePath + mOuyaFrameworkFileName);
			}*/
			createControllerInstance(mLocalSavePath + mOuyaLibFileName, mTargetDriver);
		}
	}
	
	private static final String CONFIGKEY_DRIVES = "drives";
	private static final String CONFIGKEY_LIB_FILENAME = "lib";
	private static final String CONFIGKEY_LIB_FILESIZE = "lib-size";
	private static final String CONFIGKEY_DEP_FILENAME = "dep-apk";
	private static final String CONFIGKEY_DEP_FILESIZE = "dep-size";
	
	private boolean parseConfig(String jsonString){
		mMogaSupportedDrives.clear();
		mNibiruSupportedDrives.clear();
		mOuyaSupportedDrives.clear();
		
		try {
			JSONObject configObject = new JSONObject(jsonString);
			
			JSONObject nibiruObject = configObject.getJSONObject("nibiru");
			JSONArray drives = nibiruObject.getJSONArray(CONFIGKEY_DRIVES);
			int count = drives.length();
			for (int i = 0; i < count; i++) {
				mNibiruSupportedDrives.add(drives.getString(i));
			}
			mNibiruDepFileName = nibiruObject.getString(CONFIGKEY_DEP_FILENAME);
			mNibiruDepFileSize = nibiruObject.getInt(CONFIGKEY_DEP_FILESIZE);
			mNibiruLibFileName = nibiruObject.getString(CONFIGKEY_LIB_FILENAME);
			mNibiruLibFileSize = nibiruObject.getInt(CONFIGKEY_LIB_FILESIZE);
			
			JSONObject mogaObject = configObject.getJSONObject("moga");
			drives = mogaObject.getJSONArray(CONFIGKEY_DRIVES);
			count = drives.length();
			for (int i = 0; i < count; i++) {
				mMogaSupportedDrives.add(drives.getString(i));
			}
			mMogaDepFileName = mogaObject.getString(CONFIGKEY_DEP_FILENAME);
			mMogaDepFileSize = mogaObject.getInt(CONFIGKEY_DEP_FILESIZE);
			mMogaLibFileName = mogaObject.getString(CONFIGKEY_LIB_FILENAME);
			mMogaLibFileSize = mogaObject.getInt(CONFIGKEY_LIB_FILESIZE);
			
			JSONObject ouyaObject = configObject.getJSONObject("ouya");
			drives = ouyaObject.getJSONArray(CONFIGKEY_DRIVES);
			count = drives.length();
			for (int i = 0; i < count; i++) {
				mOuyaSupportedDrives.add(drives.getString(i));
			}
			mOuyaLibFileName = ouyaObject.getString(CONFIGKEY_LIB_FILENAME);
			mOuyaLibFileSize = ouyaObject.getInt(CONFIGKEY_LIB_FILESIZE);
			//mOuyaFrameworkFileName = ouyaObject.getString("dep-framework");
			//mOuyaLauncherFileName = ouyaObject.getString("dep-launcher");
			mLazyConfigInit = false;
			return true;
		} catch (Exception e1) {
			e1.printStackTrace();			
			return false;
		}
	}
	
	private void requestControllerConfig() {
		
		final JsonHttpResponseHandler configResponseHandler = new JsonHttpResponseHandler() {

			@Override
			public void onFailure(int statusCode, Header[] headers,
					String responseBody, Throwable e) {

				Log.e(TAG, "Failed to download game controller config!");
				
				String configJSON = GameControllerUtils.readJsonFile(mConfigFilePath);
				if (configJSON != null) {
					if (parseConfig(configJSON)) {
						scanBluetoothDrive();
						return;
					}
				}
				if (mControllerListener != null) {
					mControllerListener.onDownloadConfigFinished(false);
				}
				/*new AlertDialog.Builder(sCocos2dxActivity)
				.setTitle("Loading controller config failed!")
				.setMessage(
						"Please make sure internet connection works ok!")
				.setPositiveButton("Retry",
						new DialogInterface.OnClickListener() {
							public void onClick(DialogInterface dialog,
									int which) {
								dialog.dismiss();
								requestControllerConfig();
							}
						}).setCancelable(false).show();*/
			}

			@Override
			public void onSuccess(int statusCode, Header[] headers,
					String responseBody) {
				
				String jsonString = responseBody.trim();
				
				try {
					if (parseConfig(jsonString)) {
						scanBluetoothDrive();
						showToast("Get controller config succeed!");
						
						File configFile = new File(mConfigFilePath);
						FileOutputStream outputStream = new FileOutputStream(configFile);
						byte[] contentString = jsonString.getBytes();
						outputStream.write(contentString, 0, contentString.length);
						outputStream.flush();
						outputStream.close();				
						return;
					}
					else {						
						String jsonStr = GameControllerUtils.readJsonFile(mConfigFilePath);
						if (jsonStr != null) {
							if (parseConfig(jsonStr)) {								
								scanBluetoothDrive();
								showToast("Get controller config succeed!");
								return;
							}
						}
					}
				} catch (Exception e1) {
					e1.printStackTrace();
				}
				
				if (mControllerListener != null) {
					mControllerListener.onDownloadConfigFinished(false);
				}
				Log.e(TAG, "Failed to download controller config!");
			}
		};
		
		mDownDepsHttpClient.get(COCOS_CONTROLLER_URL + COCOS_CONTROLLER_CONFIG, configResponseHandler);
	}
	
	private static void showToast(String message){
		Toast.makeText(sCocos2dxActivity, message, Toast.LENGTH_SHORT).show();
	}
	
	private static void createControllerInstance(String apkFilePath,int sdkType) {
		File apkFile = new File(apkFilePath);
		if (! apkFile.exists()) {
			Log.w(TAG, apkFile.toString() + "not exist!");
			return;
		}
		
		DexClassLoader classLoader = null;
		
		try {
			File dexOutputDir = sCocos2dxActivity.getDir("dex", Context.MODE_PRIVATE);
	        
			classLoader = new DexClassLoader(apkFile.getCanonicalPath(), dexOutputDir.getCanonicalPath(), 
					null, sCocos2dxActivity.getClassLoader());  
		} catch (Exception e1) {
			e1.printStackTrace();
		}
        		
		try {
			Class<?> controllerDelegate = null;
			if (sdkType == DRIVERTYPE_MOGA) {
		        controllerDelegate = classLoader.loadClass("org.cocos2dx.lib.GameControllerMoga");
			} else if (sdkType == DRIVERTYPE_NIBIRU) {
		        controllerDelegate = classLoader.loadClass("org.cocos2dx.lib.GameControllerNibiru");
			} else if (sdkType == DRIVERTYPE_OUYA) {
		        controllerDelegate = classLoader.loadClass("org.cocos2dx.lib.GameControllerOuya");
			}
			
			GameControllerDelegate instance = (GameControllerDelegate)controllerDelegate.newInstance();
			
			if (mControllerListener != null) {
				mControllerListener.onConnectController();
			}
			sCocos2dxActivity.setGameControllerInstance(instance);
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	private BroadcastReceiver mAppReceiver = new BroadcastReceiver() {
		
		@Override
		public void onReceive(Context context, Intent intent) {
			String packageName = intent.getDataString();
			if (packageName.equals(NIBIRU_DEP_PACKAGE)) {
				createControllerInstance(mLocalSavePath + mNibiruLibFileName, DRIVERTYPE_NIBIRU);
			}
			else if (packageName.equals(MOGA__DEP_PACKAGE)) {
				createControllerInstance(mLocalSavePath + mMogaLibFileName, DRIVERTYPE_MOGA);
			}
			//
			/*else if (packageName.equals(OUYA_FRAMEWORK_PACKAGE)) {
				installApplication(mLocalSavePath + mOuyaLauncherFileName);
			}
			else if (packageName.equals(OUYA_LAUNCHER_PACKAGE)) {
				createControllerInstance(mLocalSavePath + mOuyaLibFileName, DRIVERTYPE_OUYA);
			}*/
		}
	};
	
	private float mOldLeftThumbstickX = 0.0f;
	private float mOldLeftThumbstickY = 0.0f;
	private float mOldRightThumbstickX = 0.0f;
	private float mOldRightThumbstickY = 0.0f;
	
	private float mOldLeftTrigger = 0.0f;
	private float mOldRightTrigger = 0.0f;
	private float mOldThrottle = 0.0f;
	private float mOldBrake = 0.0f;
	
	private boolean mDpadLeftIsPressed = false;
	private boolean mDpadRightIsPressed = false;
	private boolean mDpadUpIsPressed = false;
	private boolean mDpadDownIsPressed = false;
	
	public boolean onGenericMotionEvent(MotionEvent event) {		
		boolean handled = false;
		
		int eventSource = event.getSource();
		
        if ( ((eventSource & InputDevice.SOURCE_GAMEPAD)  == InputDevice.SOURCE_GAMEPAD) 
        		|| ((eventSource & InputDevice.SOURCE_JOYSTICK) == InputDevice.SOURCE_JOYSTICK) )
        {       	
        	if (event.getAction() == MotionEvent.ACTION_MOVE) {
        		int devicedId = event.getDeviceId();
        		
        		float newAXIS_LX = event.getAxisValue(MotionEvent.AXIS_X);
        		if (newAXIS_LX != mOldLeftThumbstickX) {
					GameControllerAdapter.onAxisEvent(StandardControllerName, devicedId, GameControllerDelegate.THUMBSTICK_LEFT_X, newAXIS_LX, true);
					mOldLeftThumbstickX = newAXIS_LX;
					handled = true;
				}
        		
        		float newAXIS_LY = event.getAxisValue(MotionEvent.AXIS_Y);
        		if (newAXIS_LY != mOldLeftThumbstickY) {
					GameControllerAdapter.onAxisEvent(StandardControllerName, devicedId, GameControllerDelegate.THUMBSTICK_LEFT_Y, newAXIS_LY, true);
					mOldLeftThumbstickY = newAXIS_LY;
					handled = true;
				}
        		
        		float newAXIS_RX = event.getAxisValue(MotionEvent.AXIS_RX);
        		if (newAXIS_RX != mOldRightThumbstickX) {
					GameControllerAdapter.onAxisEvent(StandardControllerName, devicedId, GameControllerDelegate.THUMBSTICK_RIGHT_X, newAXIS_RX, true);
					mOldRightThumbstickX = newAXIS_RX;
					handled = true;
				}
        		
        		float newAXIS_RY = event.getAxisValue(MotionEvent.AXIS_RY);
        		if (newAXIS_RY != mOldRightThumbstickY) {
					GameControllerAdapter.onAxisEvent(StandardControllerName, devicedId, GameControllerDelegate.THUMBSTICK_RIGHT_Y, newAXIS_RY, true);
					mOldRightThumbstickY = newAXIS_RY;
					handled = true;
				}
        		
        		float newAXIS_LTRIGGER = event.getAxisValue(MotionEvent.AXIS_LTRIGGER);
        		if (newAXIS_LTRIGGER != mOldLeftTrigger) {					
					if (Float.compare(newAXIS_LTRIGGER, 0.0f) == 0) {
						GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_LEFT_TRIGGER, false, 0.0f, true);
					}else {
						GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_LEFT_TRIGGER, true, newAXIS_LTRIGGER, true);
					}
					mOldLeftTrigger = newAXIS_LTRIGGER;
					handled = true;
				}
        		
        		float newAXIS_RTRIGGER = event.getAxisValue(MotionEvent.AXIS_RTRIGGER);
        		if (newAXIS_RTRIGGER != mOldRightTrigger) {
        			if (Float.compare(newAXIS_RTRIGGER, 0.0f) == 0) {
						GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_RIGHT_TRIGGER, false, 0.0f, true);
					}else {
						GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_RIGHT_TRIGGER, true, newAXIS_RTRIGGER, true);
					}
					mOldRightTrigger = newAXIS_RTRIGGER;
					handled = true;
				}
        		
        		float newAXIS_BRAKE = event.getAxisValue(MotionEvent.AXIS_BRAKE);
        		if (newAXIS_BRAKE != mOldBrake) {
        			if (Float.compare(newAXIS_BRAKE, 0.0f) == 0) {
						GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_LEFT_TRIGGER, false, 0.0f, true);
					}else {
						GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_LEFT_TRIGGER, true, newAXIS_BRAKE, true);
					}
					mOldBrake = newAXIS_BRAKE;
					handled = true;
				}
        		
        		float newAXIS_THROTTLE = event.getAxisValue(MotionEvent.AXIS_THROTTLE);
        		if (newAXIS_THROTTLE != mOldThrottle) {
        			if (Float.compare(newAXIS_THROTTLE, 0.0f) == 0) {
						GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_RIGHT_TRIGGER, false, 0.0f, true);
					}else {
						GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_RIGHT_TRIGGER, true, newAXIS_THROTTLE, true);
					}
					mOldThrottle = newAXIS_THROTTLE;
					handled = true;
				}
        		
        		if (!handled) {
        			float dx = event.getAxisValue(MotionEvent.AXIS_HAT_X);
        			float dy = event.getAxisValue(MotionEvent.AXIS_HAT_Y);

					if (dx == -1.0f) {
						if (mDpadRightIsPressed) {
							mDpadRightIsPressed = false;
							GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_DPAD_RIGHT, false, 0.0f, false);
						}
						if (!mDpadLeftIsPressed) {
							mDpadLeftIsPressed = true;
							GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_DPAD_LEFT, true, 1.0f, false);								
						}
					} else if(dx == 0.0f){
						if (mDpadLeftIsPressed) {
							mDpadLeftIsPressed = false;
							GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_DPAD_LEFT, false, 0.0f, false);
						}
						if (mDpadRightIsPressed) {
							mDpadRightIsPressed = false;
							GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_DPAD_RIGHT, false, 0.0f, false);
						}
					}else {
						if (mDpadLeftIsPressed) {
							mDpadLeftIsPressed = false;
							GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_DPAD_LEFT, false, 0.0f, false);
						}
						if (!mDpadRightIsPressed) {
							mDpadRightIsPressed = true;
							GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_DPAD_RIGHT, true, 1.0f, false);
						}
					}
					
					if (dy == -1.0f) {
						if (mDpadDownIsPressed) {
							mDpadDownIsPressed = false;
							GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_DPAD_DOWN, false, 0.0f, false);
						}
						if (!mDpadUpIsPressed) {
							mDpadUpIsPressed = true;
							GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_DPAD_UP, true, 1.0f, false);
						}
					} else if(dy == 0.0f){
						if (mDpadUpIsPressed) {
							mDpadUpIsPressed = false;
							GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_DPAD_UP, false, 0.0f, false);
						}
						if (mDpadDownIsPressed) {
							mDpadDownIsPressed = false;
							GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_DPAD_DOWN, false, 0.0f, false);
						}
					}else {
						if (mDpadUpIsPressed) {
							mDpadUpIsPressed = false;
							GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_DPAD_UP, false, 0.0f, false);
						}
						if (!mDpadDownIsPressed) {
							mDpadDownIsPressed = true;
							GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_DPAD_DOWN, true, 1.0f, false);
						}
					}
				}
			} 	
        }
        
		return handled;
	}
	
	public boolean onKeyDownEvent(int keyCode, KeyEvent event) {
		boolean handled = false;
		int eventSource = event.getSource();
		int controllerKey = ControllerKeyMap.get(keyCode);
		
		if (controllerKey != 0 && (((eventSource & InputDevice.SOURCE_GAMEPAD) == InputDevice.SOURCE_GAMEPAD)
						|| ((eventSource & InputDevice.SOURCE_JOYSTICK) == InputDevice.SOURCE_JOYSTICK) 
						|| ((eventSource & InputDevice.SOURCE_DPAD) == InputDevice.SOURCE_DPAD))) 
		{
			GameControllerAdapter.onButtonEvent(StandardControllerName,event.getDeviceId(), controllerKey,true, 1.0f, false);
			handled = true;
		}

		return handled;
	}
	
	public boolean onKeyUpEvent(int keyCode, KeyEvent event) {
		boolean handled = false;
		int eventSource = event.getSource();
		int controllerKey = ControllerKeyMap.get(keyCode);
		
		if (controllerKey != 0  && ( ((eventSource & InputDevice.SOURCE_GAMEPAD) == InputDevice.SOURCE_GAMEPAD)
				|| ((eventSource & InputDevice.SOURCE_JOYSTICK) == InputDevice.SOURCE_JOYSTICK)
				|| ((eventSource & InputDevice.SOURCE_DPAD) == InputDevice.SOURCE_DPAD) ) ) 
		{
			GameControllerAdapter.onButtonEvent(StandardControllerName, event.getDeviceId(), controllerKey, false, 0.0f, false);
			handled = true;
		}
		
		return handled;
	}
}
