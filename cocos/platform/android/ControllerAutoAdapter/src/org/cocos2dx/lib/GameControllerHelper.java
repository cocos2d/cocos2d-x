package org.cocos2dx.lib;

import java.io.File;
import java.io.FileOutputStream;
import java.lang.reflect.Method;
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
	
	public static final String SPP_UUID = "00001101-0000-1000-8000-00805F9B34FB";
	
	SparseIntArray ControllerKeyMap;
	
	private static final String COCOS_CONTROLLER_URL = "http://115.28.134.83:9000/download/cocoscontroller/";
	private static final String COCOS_CONTROLLER_CONFIG = "controller.json";
	
	private static final String NIBIRU_DEP_PACKAGE = "com.nibiru";
	private static final String MOGA__DEP_PACKAGE = "com.bda.pivot.mogapgp";
	
	private static GameControllerActivity sGameControllerActivity;
	private static GameControllerHelper sControllerHelper;
	
	private String mLibAdapterFileName;
	private int mLibAdapterFileSize;
	
	private List<String>  mNibiruSupportedDrives;
	private String  mNibiruDepFileName;
	private int mNibiruDepFileSize;
	
	private List<String> mMogaSupportedDrives;
	private String  mMogaDepFileName;
	private int mMogaDepFileSize;
	
	private List<String> mOuyaSupportedDrives;
	
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
	
	private static final int AXIS_X = 0;
	private static final int AXIS_Y = 1;
	private static final int AXIS_Z = 11;
	private static final int AXIS_RZ = 14;
	public static final int AXIS_LTRIGGER = 17;
	public static final int AXIS_RTRIGGER = 18;
	public static final int AXIS_BRAKE = 23;
	public static final int AXIS_THROTTLE = 19;
	
	public GameControllerHelper(GameControllerActivity activity){
		sGameControllerActivity = activity;
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
				
		ControllerKeyMap.put(AXIS_X, GameControllerDelegate.THUMBSTICK_LEFT_X);
		ControllerKeyMap.put(AXIS_Y, GameControllerDelegate.THUMBSTICK_LEFT_Y);
		ControllerKeyMap.put(AXIS_Z, GameControllerDelegate.THUMBSTICK_RIGHT_X);
		ControllerKeyMap.put(AXIS_RZ, GameControllerDelegate.THUMBSTICK_RIGHT_Y);
		
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_START, GameControllerDelegate.BUTTON_START);
		ControllerKeyMap.put(KeyEvent.KEYCODE_BUTTON_SELECT, GameControllerDelegate.BUTTON_SELECT);
		//KEYCODE_BUTTON_MODE
		mDownDepsHttpClient = new AsyncHttpClient();
		mDownDepsHttpClient.setTimeout(360 * 1000);
	}
	
	public void connectController(){
		if (mLazyInit) {
			mLazyInit = false;
			mNibiruSupportedDrives = new ArrayList<String>(30);
			mMogaSupportedDrives = new ArrayList<String>(5);
			mOuyaSupportedDrives = new ArrayList<String>(5);
			
			mLocalSavePath = Environment.getExternalStorageDirectory() + File.separator + "CocosGameController" + File.separator;
			Log.i(TAG, "mLocalSavePath:" + mLocalSavePath);
			mConfigFilePath = sGameControllerActivity.getFilesDir().getAbsolutePath() + File.separator + COCOS_CONTROLLER_CONFIG;
			Log.i(TAG, "mConfigFilePath:" + mConfigFilePath);
			
		}
		
		if (mControllerListener != null) {
			mControllerListener.onDownloadConfigStarted();
		}
		if (mLazyConfigInit) {
			//if (mDownDepsHttpClient != null) {
			//	mDownDepsHttpClient.cancelRequests(sGameControllerActivity, true);
			//}
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
			mDownDepsHttpClient.cancelRequests(sGameControllerActivity, true);
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
			sGameControllerActivity.registerReceiver(mBluetoothReceiver, filter);	
			
			IntentFilter appFilter = new IntentFilter();
			appFilter.addAction("android.intent.action.PACKAGE_ADDED");
			appFilter.addDataScheme("package");
			sGameControllerActivity.registerReceiver(mAppReceiver, appFilter);
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
			return GameControllerActivity.DRIVERTYPE_NIBIRU;
		}
		else if (mMogaSupportedDrives.contains(deviceName)) {
			return GameControllerActivity.DRIVERTYPE_MOGA;
		}
		else if (mOuyaSupportedDrives.contains(deviceName)) {
			return GameControllerActivity.DRIVERTYPE_OUYA;
		}
		else {
			
		}
		
		return GameControllerActivity.DRIVERTYPE_UNKNOWN;
	}
	
	public static void installApplication(String filePath){
		if (sGameControllerActivity != null) {
			Intent intent = new Intent();
			intent.setAction(Intent.ACTION_VIEW);
			intent.setDataAndType(Uri.parse("file://" + filePath), "application/vnd.android.package-archive");
			intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
			sGameControllerActivity.startActivity(intent);
		}
	}
	
	public static boolean checkApplication(String packName){
		try {
			ApplicationInfo applicationInfo = sGameControllerActivity.getPackageManager().getApplicationInfo(packName, PackageManager.GET_UNINSTALLED_PACKAGES);
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
				Log.d(TAG, "Remote device discovered :" + device.getName());
				//We can't ensure non-controller can be filtered out.Some game controller marked with computer class.
				/*String deviceName = device.getName();
				
				if(device.getBluetoothClass().getMajorDeviceClass() == BluetoothClass.Device.Major.COMPUTER 
						|| device.getBluetoothClass().getMajorDeviceClass() == BluetoothClass.Device.Major.PHONE)
				{
					Log.w(TAG, "Remote device discovered :" + deviceName + " is computer or phone." + device.getBluetoothClass().getMajorDeviceClass());
					return;
				}*/
				
				mBluetoothDevices.add(device);
				int type = checkDriverType(device);
				if (type != GameControllerActivity.DRIVERTYPE_UNKNOWN) {
					mTargetDriverType = type;
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
						if (checkApplication(NIBIRU_DEP_PACKAGE)) {
							downControllerDeps(GameControllerActivity.DRIVERTYPE_NIBIRU);
						}
						Log.w(TAG, "Not found any supported bluetooth game controller!");
					}else {
						if (mClearDevices == 1 ) {
							downControllerDeps(mTargetDriverType);
						}
						else {
							Log.i(TAG, "Not clear target!");
							if (checkApplication(NIBIRU_DEP_PACKAGE)) {
								downControllerDeps(GameControllerActivity.DRIVERTYPE_NIBIRU);
							}
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
				mTargetDriverType = GameControllerActivity.DRIVERTYPE_UNKNOWN;
				
				//check moga controller
				Iterator<BluetoothDevice> it = mBluetoothAdapter.getBondedDevices().iterator();
				while (it.hasNext()) {
					BluetoothDevice device = it.next();
					//if(device.getBluetoothClass().getMajorDeviceClass() != BluetoothClass.Device.Major.COMPUTER 
					//		&& device.getBluetoothClass().getMajorDeviceClass() != BluetoothClass.Device.Major.PHONE)
					{
						if (!mBluetoothDevices.contains(device)) {
							mBluetoothDevices.add(device);
							int type = checkDriverType(device);
							Log.d(TAG, "BluetoothDevice objects that are bonded (paired) to the local adapter :" + device.getName());
							if (type != GameControllerActivity.DRIVERTYPE_UNKNOWN) {
								mClearDevices += 1;
								mTargetDriverType = type;
							}
							mDevicesDriver.append(mBluetoothDevices.size() - 1, type);
						}
					}
				}
			}
		}
	};
	
	private static int depsCount = 0;
	private static int mTargetDriverType = GameControllerActivity.DRIVERTYPE_UNKNOWN;
	
	private static int mDownloadTotalSize;
	private static int mDownloadLibSize;
	private static int mLibDownloadCompletedSize;
	private static int mDepDownloadCompletedSize;
	
	public void downControllerDeps(int driverType){
		if (driverType != GameControllerActivity.DRIVERTYPE_NIBIRU 
				&& driverType != GameControllerActivity.DRIVERTYPE_MOGA 
				&& driverType != GameControllerActivity.DRIVERTYPE_OUYA) {			
			return;
		}
		
		if (mControllerListener != null) {
			mControllerListener.onDownloadDepsStarted();
		}
		
		mDownloadTotalSize = 0;
		mLibDownloadCompletedSize = 0;
		mDepDownloadCompletedSize = 0;
		
		mTargetDriverType = driverType;
		depsCount = 1;
		
		GameControllerUtils.ensureDirectoryExist(mLocalSavePath);
		
		String remoteDir = COCOS_CONTROLLER_URL + DRIVERS_NAME[driverType] + File.separator;
		
		if (driverType == GameControllerActivity.DRIVERTYPE_NIBIRU) {
			if (!checkApplication(NIBIRU_DEP_PACKAGE)) {
				depsCount += 1;
				mDownloadTotalSize += mNibiruDepFileSize;
				mDownDepsHttpClient.get(remoteDir + mNibiruDepFileName, new MyDepsAsyncHandler(
						new File(mLocalSavePath + mNibiruDepFileName), MyDepsAsyncHandler.FILETYPE_DEP_APK));
			}
		}
		else if (driverType == GameControllerActivity.DRIVERTYPE_MOGA) {
			if (!checkApplication(MOGA__DEP_PACKAGE)) {
				mDownloadTotalSize += mMogaDepFileSize;
				depsCount += 1;
				mDownDepsHttpClient.get(remoteDir + mMogaDepFileName, new MyDepsAsyncHandler(
						new File(mLocalSavePath + mMogaDepFileName), MyDepsAsyncHandler.FILETYPE_DEP_APK));
			}
		}
		else if(driverType == GameControllerActivity.DRIVERTYPE_OUYA){
			
		}
		
		File libFile = new File(mLocalSavePath + mLibAdapterFileName);
		if (libFile.exists() && libFile.length() == mLibAdapterFileSize) {
			depsCount -= 1;
			if (depsCount == 0) {
				onDepsReady();
			}
		}else {
			mDownloadLibSize = mLibAdapterFileSize;
			mDownloadTotalSize += mDownloadLibSize;
			mDownDepsHttpClient.get(COCOS_CONTROLLER_URL + mLibAdapterFileName, new MyDepsAsyncHandler(
					new File(mLocalSavePath + mLibAdapterFileName), MyDepsAsyncHandler.FILETYPE_JAR));
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

		
		public void onSuccess(File file) {
			Log.d(TAG, "11Down file success:" + file.getName());
			
			depsCount -= 1;
			if (depsCount == 0) {
				if (mControllerListener != null) {
					mControllerListener.onDownloadDepsFinished(true);
				}
				sControllerHelper.onDepsReady();
			}
			super.onSuccess(file);
		}
		
		/*@Override
		public void onSuccess(int arg0, Header[] arg1, File file) {
			Log.d(TAG, "22Down file success:" + file.getName());
			
			depsCount -= 1;
			if (depsCount == 0) {
				if (mControllerListener != null) {
					mControllerListener.onDownloadDepsFinished(true);
				}
				sControllerHelper.onDepsReady();
			}
		}*/
	}
	
	private void onDepsReady(){
		Log.d(TAG, "onDepsReady:" + mTargetDriverType);
		
		if (mTargetDriverType == GameControllerActivity.DRIVERTYPE_NIBIRU) {
			if (checkApplication(NIBIRU_DEP_PACKAGE)) {
				createControllerInstance(mLocalSavePath + mLibAdapterFileName, mTargetDriverType);
			}
			else {
				if (mControllerListener != null) {
					mControllerListener.onInstallDriver(mLocalSavePath + mMogaDepFileName);
				}
				installApplication(mLocalSavePath + mNibiruDepFileName);
			}
		}
		else if (mTargetDriverType == GameControllerActivity.DRIVERTYPE_MOGA) {
			if (checkApplication(MOGA__DEP_PACKAGE)) {
				createControllerInstance(mLocalSavePath + mLibAdapterFileName, mTargetDriverType);
			}
			else {
				if (mControllerListener != null) {
					mControllerListener.onInstallDriver(mLocalSavePath + mMogaDepFileName);
				}
				installApplication(mLocalSavePath + mMogaDepFileName);
			}
		}
		else if (mTargetDriverType == GameControllerActivity.DRIVERTYPE_OUYA) {
			createControllerInstance(mLocalSavePath + mLibAdapterFileName, mTargetDriverType);
		}
	}
	
	private static final String CONFIGKEY_DRIVES = "drives";
	private static final String CONFIGKEY_LIBADAPTER_FILENAME = "adapter-file";
	private static final String CONFIGKEY_LIBADAPTER_FILESIZE = "adapter-filesize";
	private static final String CONFIGKEY_DEP_FILENAME = "dep-apk";
	private static final String CONFIGKEY_DEP_FILESIZE = "dep-size";
	
	private boolean parseConfig(String jsonString){
		mMogaSupportedDrives.clear();
		mNibiruSupportedDrives.clear();
		mOuyaSupportedDrives.clear();
		
		try {
			int tint = 9879;
			JSONObject jsonObject = new JSONObject();
			jsonObject.put("intvalue",tint);
			Log.w(TAG, "intJson:" + jsonObject);
			
			JSONObject configObject = new JSONObject(jsonString);
			mLibAdapterFileName = configObject.getString(CONFIGKEY_LIBADAPTER_FILENAME);
			mLibAdapterFileSize = configObject.getInt(CONFIGKEY_LIBADAPTER_FILESIZE);
			
			JSONObject nibiruObject = configObject.getJSONObject("nibiru");
			JSONArray drives = nibiruObject.getJSONArray(CONFIGKEY_DRIVES);
			int count = drives.length();
			for (int i = 0; i < count; i++) {
				mNibiruSupportedDrives.add(drives.getString(i));
			}
			mNibiruDepFileName = nibiruObject.getString(CONFIGKEY_DEP_FILENAME);
			mNibiruDepFileSize = nibiruObject.getInt(CONFIGKEY_DEP_FILESIZE);
			
			JSONObject mogaObject = configObject.getJSONObject("moga");
			drives = mogaObject.getJSONArray(CONFIGKEY_DRIVES);
			count = drives.length();
			for (int i = 0; i < count; i++) {
				mMogaSupportedDrives.add(drives.getString(i));
			}
			mMogaDepFileName = mogaObject.getString(CONFIGKEY_DEP_FILENAME);
			mMogaDepFileSize = mogaObject.getInt(CONFIGKEY_DEP_FILESIZE);
			
			JSONObject ouyaObject = configObject.getJSONObject("ouya");
			drives = ouyaObject.getJSONArray(CONFIGKEY_DRIVES);
			count = drives.length();
			for (int i = 0; i < count; i++) {
				mOuyaSupportedDrives.add(drives.getString(i));
			}
			
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
			}
		};
		
		mDownDepsHttpClient.get(COCOS_CONTROLLER_URL + COCOS_CONTROLLER_CONFIG, configResponseHandler);
	}
	
	private static void showToast(String message){
		Toast.makeText(sGameControllerActivity, message, Toast.LENGTH_SHORT).show();
	}
	
	private static void createControllerInstance(String libFilePath,int driveType) {
		//if (sGameControllerActivity.getGameControllerDelegate(driveType) != null) {
		//	return;
		//}
		
		File libFile = new File(libFilePath);
		if (! libFile.exists()) {
			Log.w(TAG, libFile.toString() + "not exist!");
			return;
		}
		
		DexClassLoader classLoader = null;
		
		try {
			File dexOutputDir = sGameControllerActivity.getDir("dex", Context.MODE_PRIVATE);
			classLoader = new DexClassLoader(libFile.getCanonicalPath(), dexOutputDir.getCanonicalPath(), 
					null, sGameControllerActivity.getClassLoader());  
		} catch (Exception e1) {
			e1.printStackTrace();
		}
        
		try {
			Class<?> controllerDelegate = null;
			if (driveType == GameControllerActivity.DRIVERTYPE_MOGA) {
		        controllerDelegate = classLoader.loadClass("org.cocos2dx.lib.GameControllerMoga");
			} else if (driveType == GameControllerActivity.DRIVERTYPE_NIBIRU) {
		        controllerDelegate = classLoader.loadClass("org.cocos2dx.lib.GameControllerNibiru");
			} else if (driveType == GameControllerActivity.DRIVERTYPE_OUYA) {
		        controllerDelegate = classLoader.loadClass("org.cocos2dx.lib.GameControllerOuya");
			}
			
			GameControllerDelegate instance = (GameControllerDelegate)controllerDelegate.newInstance();
			
			if (mControllerListener != null) {
				mControllerListener.onConnectController();
			}
			sGameControllerActivity.setGameControllerInstance(instance, driveType);
			if (driveType == GameControllerActivity.DRIVERTYPE_NIBIRU) {
				Method method = controllerDelegate.getDeclaredMethod("onResume");
				method.invoke(instance);
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	private BroadcastReceiver mAppReceiver = new BroadcastReceiver() {
		
		@Override
		public void onReceive(Context context, Intent intent) {
			String packageName = intent.getDataString();
			Log.d(TAG, "mAppReceiver:" + intent);
			if (packageName.contains(NIBIRU_DEP_PACKAGE)) {
				createControllerInstance(mLocalSavePath + mLibAdapterFileName, GameControllerActivity.DRIVERTYPE_NIBIRU);
			}
			else if (packageName.contains(MOGA__DEP_PACKAGE)) {
				createControllerInstance(mLocalSavePath + mLibAdapterFileName, GameControllerActivity.DRIVERTYPE_MOGA);
			}
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
	
	public boolean dispatchGenericMotionEvent(MotionEvent event) {		
		boolean handled = false;
		
		int eventSource = event.getSource();
		
        if ( ((eventSource & InputDevice.SOURCE_GAMEPAD)  == InputDevice.SOURCE_GAMEPAD) 
        		|| ((eventSource & InputDevice.SOURCE_JOYSTICK) == InputDevice.SOURCE_JOYSTICK) )
        {       	
        	if (event.getAction() == MotionEvent.ACTION_MOVE) {
        		int devicedId = event.getDeviceId();
        		
        		float newAXIS_LX = event.getAxisValue(AXIS_X);
        		if (Float.compare(newAXIS_LX , mOldLeftThumbstickX) != 0) {
					GameControllerAdapter.onAxisEvent(StandardControllerName, devicedId, GameControllerDelegate.THUMBSTICK_LEFT_X, newAXIS_LX, true);
					mOldLeftThumbstickX = newAXIS_LX;
					handled = true;
				}
        		
        		float newAXIS_LY = event.getAxisValue(AXIS_Y);
        		if (Float.compare(newAXIS_LY , mOldLeftThumbstickY) != 0) {
					GameControllerAdapter.onAxisEvent(StandardControllerName, devicedId, GameControllerDelegate.THUMBSTICK_LEFT_Y, newAXIS_LY, true);
					mOldLeftThumbstickY = newAXIS_LY;
					handled = true;
				}
        		
        		float newAXIS_RX = event.getAxisValue(AXIS_Z);
        		if (Float.compare(newAXIS_RX , mOldRightThumbstickX) != 0) {
					GameControllerAdapter.onAxisEvent(StandardControllerName, devicedId, GameControllerDelegate.THUMBSTICK_RIGHT_X, newAXIS_RX, true);
					mOldRightThumbstickX = newAXIS_RX;
					handled = true;
				}
        		
        		float newAXIS_RY = event.getAxisValue(AXIS_RZ);
        		if (Float.compare(newAXIS_RY , mOldRightThumbstickY) != 0) {
					GameControllerAdapter.onAxisEvent(StandardControllerName, devicedId, GameControllerDelegate.THUMBSTICK_RIGHT_Y, newAXIS_RY, true);
					mOldRightThumbstickY = newAXIS_RY;
					handled = true;
				}
        		
        		float newAXIS_LTRIGGER = event.getAxisValue(AXIS_LTRIGGER);
        		if (Float.compare(newAXIS_LTRIGGER , mOldLeftTrigger) != 0) {					
					if (Float.compare(newAXIS_LTRIGGER, 0.0f) == 0) {
						GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_LEFT_TRIGGER, false, 0.0f, true);
					}else {
						GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_LEFT_TRIGGER, true, newAXIS_LTRIGGER, true);
					}
					mOldLeftTrigger = newAXIS_LTRIGGER;
					handled = true;
				}
        		
        		float newAXIS_RTRIGGER = event.getAxisValue(AXIS_RTRIGGER);
        		if (Float.compare(newAXIS_RTRIGGER , mOldRightTrigger) != 0) {
        			if (Float.compare(newAXIS_RTRIGGER, 0.0f) == 0) {
						GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_RIGHT_TRIGGER, false, 0.0f, true);
					}else {
						GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_RIGHT_TRIGGER, true, newAXIS_RTRIGGER, true);
					}
					mOldRightTrigger = newAXIS_RTRIGGER;
					handled = true;
				}
        		
        		float newAXIS_BRAKE = event.getAxisValue(AXIS_BRAKE);
        		if (Float.compare(newAXIS_BRAKE , mOldBrake) != 0) {
        			if (Float.compare(newAXIS_BRAKE, 0.0f) == 0) {
						GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_LEFT_TRIGGER, false, 0.0f, true);
					}else {
						GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_LEFT_TRIGGER, true, newAXIS_BRAKE, true);
					}
					mOldBrake = newAXIS_BRAKE;
					handled = true;
				}
        		
        		float newAXIS_THROTTLE = event.getAxisValue(AXIS_THROTTLE);
        		if (Float.compare(newAXIS_THROTTLE , mOldThrottle) != 0) {
        			if (Float.compare(newAXIS_THROTTLE, 0.0f) == 0) {
						GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_RIGHT_TRIGGER, false, 0.0f, true);
					}else {
						GameControllerAdapter.onButtonEvent(StandardControllerName, devicedId, GameControllerDelegate.BUTTON_RIGHT_TRIGGER, true, newAXIS_THROTTLE, true);
					}
					mOldThrottle = newAXIS_THROTTLE;
					handled = true;
				}
			} 	
        }
        
		return handled;
	}
	
	public boolean dispatchKeyEvent(KeyEvent event) {
    	boolean handled = false;
    	
    	int eventSource = event.getSource();
		int controllerKey = ControllerKeyMap.get(event.getKeyCode());
		
		if (controllerKey != 0 && (((eventSource & InputDevice.SOURCE_GAMEPAD) == InputDevice.SOURCE_GAMEPAD)
				|| ((eventSource & InputDevice.SOURCE_JOYSTICK) == InputDevice.SOURCE_JOYSTICK) 
				|| ((eventSource & InputDevice.SOURCE_DPAD) == InputDevice.SOURCE_DPAD))) 
		{
			int action = event.getAction();
			if (action == KeyEvent.ACTION_DOWN) {
				handled = true;
				GameControllerAdapter.onButtonEvent(StandardControllerName,event.getDeviceId(), controllerKey,true, 1.0f, false);
			}else if (action == KeyEvent.ACTION_UP) {
				handled = true;
				GameControllerAdapter.onButtonEvent(StandardControllerName,event.getDeviceId(), controllerKey,false, 0.0f, false);
			}
		}
		
    	return handled;
    }
}
