/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2017 Chukong Technologies Inc.

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
package org.cocos2dx.lib;

import android.content.pm.PackageManager;
import android.media.AudioManager;
import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.SharedPreferences;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.res.AssetFileDescriptor;
import android.content.res.AssetManager;
import android.net.Uri;
import android.os.Build;
import android.os.Environment;
import android.os.IBinder;
import android.os.ParcelFileDescriptor;
import android.os.Vibrator;
import android.preference.PreferenceManager.OnActivityResultListener;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Display;
import android.view.WindowManager;

import com.android.vending.expansion.zipfile.APKExpansionSupport;
import com.android.vending.expansion.zipfile.ZipResourceFile;

import com.enhance.gameservice.IGameTuningService;

import java.io.IOException;
import java.io.File;
import java.io.FilenameFilter;
import java.io.UnsupportedEncodingException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.LinkedHashSet;
import java.util.Locale;
import java.util.Map;
import java.util.Set;


public class Cocos2dxHelper {
	// ===========================================================
	// Constants
	// ===========================================================
	private static final String PREFS_NAME = "Cocos2dxPrefsFile";
	private static final int RUNNABLES_PER_FRAME = 5;
	private static final String TAG = Cocos2dxHelper.class.getSimpleName();

	// ===========================================================
	// Fields
	// ===========================================================

	private static Cocos2dxMusic sCocos2dMusic;
	private static Cocos2dxSound sCocos2dSound = null;
	private static AssetManager sAssetManager;
	private static Cocos2dxAccelerometer sCocos2dxAccelerometer = null;
	private static boolean sAccelerometerEnabled;
	private static boolean sCompassEnabled;
	private static boolean sActivityVisible;
	private static String sPackageName;
	private static Activity sActivity = null;
	private static Cocos2dxHelperListener sCocos2dxHelperListener;
	private static Set<OnActivityResultListener> onActivityResultListeners = new LinkedHashSet<OnActivityResultListener>();
	private static Vibrator sVibrateService = null;
	//Enhance API modification begin
	private static IGameTuningService mGameServiceBinder = null;
	private static final int BOOST_TIME = 7;
	//Enhance API modification end

	// The absolute path to the OBB if it exists, else the absolute path to the APK.
	private static String sAssetsPath = "";
    
	// The OBB file
	private static ZipResourceFile sOBBFile = null;

	// ===========================================================
	// Constructors
	// ===========================================================

	/*
	 * @brief Run on GL thread.
	 */
	public static void runOnGLThread(final Runnable r) {
		((Cocos2dxActivity)sActivity).runOnGLThread(r);
	}

	private static boolean sInited = false;
	/*
	 * @brief Initialize class Cocos2dxHelper.
	 */
	public static void init(final Activity activity) {
		sActivity = activity;
		Cocos2dxHelper.sCocos2dxHelperListener = (Cocos2dxHelperListener)activity;
		if (!sInited) {

			PackageManager pm = activity.getPackageManager();
			boolean isSupportLowLatency = pm.hasSystemFeature(PackageManager.FEATURE_AUDIO_LOW_LATENCY);

			Log.d(TAG, "isSupportLowLatency:" + isSupportLowLatency);

			int sampleRate = 44100;
			int bufferSizeInFrames = 192;
	
			if (Build.VERSION.SDK_INT >= 17) {
				AudioManager am = (AudioManager) activity.getSystemService(Context.AUDIO_SERVICE);
				// use reflection to remove dependence of API 17 when compiling

				// AudioManager.getProperty(AudioManager.PROPERTY_OUTPUT_SAMPLE_RATE);
				final Class audioManagerClass = AudioManager.class;
				Object[] parameters = new Object[]{Cocos2dxReflectionHelper.<String>getConstantValue(audioManagerClass, "PROPERTY_OUTPUT_SAMPLE_RATE")};
				final String strSampleRate = Cocos2dxReflectionHelper.<String>invokeInstanceMethod(am, "getProperty", new Class[]{String.class}, parameters);

				// AudioManager.getProperty(AudioManager.PROPERTY_OUTPUT_FRAMES_PER_BUFFER);
				parameters = new Object[]{Cocos2dxReflectionHelper.<String>getConstantValue(audioManagerClass, "PROPERTY_OUTPUT_FRAMES_PER_BUFFER")};
				final String strBufferSizeInFrames = Cocos2dxReflectionHelper.<String>invokeInstanceMethod(am, "getProperty", new Class[]{String.class}, parameters);

				try {
					sampleRate = Integer.parseInt(strSampleRate);
					bufferSizeInFrames = Integer.parseInt(strBufferSizeInFrames);
				} catch (NumberFormatException e) {
					Log.e(TAG, "parseInt failed", e);
				}
				Log.d(TAG, "sampleRate: " + sampleRate + ", framesPerBuffer: " + bufferSizeInFrames);
			} else {
				Log.d(TAG, "android version is lower than 17");
			}

		nativeSetAudioDeviceInfo(isSupportLowLatency, sampleRate, bufferSizeInFrames);

		final ApplicationInfo applicationInfo = activity.getApplicationInfo();
            
		Cocos2dxHelper.sPackageName = applicationInfo.packageName;

		Cocos2dxHelper.sCocos2dMusic = new Cocos2dxMusic(activity);
		Cocos2dxHelper.sAssetManager = activity.getAssets();
		Cocos2dxHelper.nativeSetContext((Context)activity, Cocos2dxHelper.sAssetManager);
    
		Cocos2dxBitmap.setContext(activity);

		Cocos2dxHelper.sVibrateService = (Vibrator)activity.getSystemService(Context.VIBRATOR_SERVICE);

		sInited = true;
            
		//Enhance API modification begin
		Intent serviceIntent = new Intent(IGameTuningService.class.getName());
		serviceIntent.setPackage("com.enhance.gameservice");
		boolean suc = activity.getApplicationContext().bindService(serviceIntent, connection, Context.BIND_AUTO_CREATE);
		//Enhance API modification end
		}
	}
    
	/*
	 * @brief Get assets path.
	 * @return The absolute path to the OBB if it exists; otherwise the absolute path to the APK
	 */
	public static String getAssetsPath()
	{
		if (Cocos2dxHelper.sAssetsPath.equals("")) {
	
			String pathToOBB = Environment.getExternalStorageDirectory().getAbsolutePath() + "/Android/obb/" + Cocos2dxHelper.sPackageName;

				// Listing all files inside the folder (pathToOBB) where OBB files are expected to be found.
            		String[] fileNames = new File(pathToOBB).list(new FilenameFilter() { // Using filter to pick up only main OBB file name.
                		public boolean accept(File dir, String name) {
                    			return name.startsWith("main.") && name.endsWith(".obb");  // It's possible to filter only by extension here to get path to patch OBB file also.
				}
			});

			String fullPathToOBB = "";
			if (fileNames != null && fileNames.length > 0)  // If there is at least 1 element inside the array with OBB file names, then we may think fileNames[0] will have desired main OBB file name.
				fullPathToOBB = pathToOBB + "/" + fileNames[0];  // Composing full file name for main OBB file.

			File obbFile = new File(fullPathToOBB);
			if (obbFile.exists())
				Cocos2dxHelper.sAssetsPath = fullPathToOBB;
			else
				Cocos2dxHelper.sAssetsPath = Cocos2dxHelper.sActivity.getApplicationInfo().sourceDir;
		}
        
		return Cocos2dxHelper.sAssetsPath;
	}
    
	/*
	 * @brief Get OBB file.
	 * @return Value from Java static ZipResourceFile method
	 */
	public static ZipResourceFile getObbFile() {
		if (null == sOBBFile) {
			int versionCode = 1;
			try {
				versionCode = Cocos2dxActivity.getContext().getPackageManager().getPackageInfo(Cocos2dxHelper.getCocos2dxPackageName(), 0).versionCode;
			} catch (NameNotFoundException e) {
				e.printStackTrace();
			}

			try {
				sOBBFile = APKExpansionSupport.getAPKExpansionZipFile(Cocos2dxActivity.getContext(), versionCode, 0);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		return sOBBFile;
	}
    
	//Enhance API modification begin
	private static ServiceConnection connection = new ServiceConnection() {
		public void onServiceConnected(ComponentName name, IBinder service) {
			mGameServiceBinder = IGameTuningService.Stub.asInterface(service);
			fastLoading(BOOST_TIME);
		}

		public void onServiceDisconnected(ComponentName name) {
			sActivity.getApplicationContext().unbindService(connection);
		}
	};
	//Enhance API modification end
    
	/*
	 * @brief Get activity.
	 * @return Value from Java static Activity method
	 */
	public static Activity getActivity() {
		return sActivity;
	}
    
	/*
	 * @brief Add OnActivityResultListener.
	 */
	public static void addOnActivityResultListener(OnActivityResultListener listener) {
		onActivityResultListeners.add(listener);
	}
    
	/*
	 * @brief Get OnActivityResultListener.
	 * @return Value from Java static Set<OnActivityResultListener> method
	 */
	public static Set<OnActivityResultListener> getOnActivityResultListeners() {
		return onActivityResultListeners;
	}
    
	/*
	 * @brief Indicates whether the Activity is visible.
	 * @return Value from Java static boolean method
	 */
	public static boolean isActivityVisible(){
		return sActivityVisible;
	}

	// ===========================================================
	// Getter & Setter
	// ===========================================================

	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================

	// ===========================================================
	// Methods
	// ===========================================================

	private static native void nativeSetEditTextDialogResult(final byte[] pBytes);

	private static native void nativeSetContext(final Context pContext, final AssetManager pAssetManager);

	private static native void nativeSetAudioDeviceInfo(boolean isSupportLowLatency, int deviceSampleRate, int audioBufferSizeInFames);

	public static String getCocos2dxPackageName() {
		return Cocos2dxHelper.sPackageName;
	}
	
	public static String getCocos2dxWritablePath() {
		return sActivity.getFilesDir().getAbsolutePath();
	}

	public static String getCurrentLanguage() {
		return Locale.getDefault().getLanguage();
	}
    
	public static String getDeviceModel(){
		return Build.MODEL;
	}

	public static AssetManager getAssetManager() {
		return Cocos2dxHelper.sAssetManager;
	}

	/*
	 * @brief Enable accelerometer.
	 */
	public static void enableAccelerometer() {
		Cocos2dxHelper.sAccelerometerEnabled = true;
		Cocos2dxHelper.getAccelerometer().enableAccel();
	}

	/*
	 * @brief Enable compass.
	 */
	public static void enableCompass() {
		Cocos2dxHelper.sCompassEnabled = true;
		Cocos2dxHelper.getAccelerometer().enableCompass();
	}

	/*
	 * @brief Set accelerometer interval.
	 * @param interval Adjust sensitivity of accelerometer interval
	 */
	public static void setAccelerometerInterval(float interval) {
		Cocos2dxHelper.getAccelerometer().setInterval(interval);
	}

	/*
	 * @brief Disable accelerometer.
	 */
	public static void disableAccelerometer() {
		Cocos2dxHelper.sAccelerometerEnabled = false;
		Cocos2dxHelper.getAccelerometer().disable();
	}

	/*
	 * @brief Set keep screen on or not.
	 * @param value Determines whether to keep screen on or not.
	 */
	public static void setKeepScreenOn(boolean value) {
		((Cocos2dxActivity)sActivity).setKeepScreenOn(value);
	}

	/*
	 * @brief Vibrate for duration.
	 * @param duration Indicates how long it will vibrate.
	 */
	public static void vibrate(float duration) {
		sVibrateService.vibrate((long)(duration * 1000));
    	}

	/*
         * @brief Get version of operating system.
         * @return Version of operating system from Java static string method
         */
 	public static String getVersion() {
 		try {
 			String version = Cocos2dxActivity.getContext().getPackageManager().getPackageInfo(Cocos2dxActivity.getContext().getPackageName(), 0).versionName;
 			return version;
 		} catch(Exception e) {
 			return "";
 		}
 	}

	/*
 	 * @brief Check of the url opened or not.
	 * @param url address of the website.
	 * @return Value of url opened or not from Java static boolean method
	 */
	public static boolean openURL(String url) { 
        	boolean ret = false;
       		try {
            	Intent i = new Intent(Intent.ACTION_VIEW);
            	i.setData(Uri.parse(url));
            	sActivity.startActivity(i);
            	ret = true;
        	} catch (Exception e) {
        	}
        	return ret;
	}
    
	/*
	 * @brief Get OBB asset file descriptor.
	 * @param path The absolute path to the OBB asset file descriptor
	 */
	public static long[] getObbAssetFileDescriptor(final String path) {
		long[] array = new long[3];
		if (Cocos2dxHelper.getObbFile() != null) {
			AssetFileDescriptor descriptor = Cocos2dxHelper.getObbFile().getAssetFileDescriptor(path);
			if (descriptor != null) {
				try {
					ParcelFileDescriptor parcel = descriptor.getParcelFileDescriptor();
					Method method = parcel.getClass().getMethod("getFd", new Class[] {});
					array[0] = (Integer)method.invoke(parcel);
					array[1] = descriptor.getStartOffset();
					array[2] = descriptor.getLength();
				} catch (NoSuchMethodException e) {
					Log.e(Cocos2dxHelper.TAG, "Accessing file descriptor directly from the OBB is only supported from Android 3.1 (API level 12) and above.");
				} catch (IllegalAccessException e) {
					Log.e(Cocos2dxHelper.TAG, e.toString());
				} catch (InvocationTargetException e) {
					Log.e(Cocos2dxHelper.TAG, e.toString());
				}
			}
		}
        	return array;
	}

	/*
	 * @brief Preload background music.
	 * @param pPath The path of the background music file.
	 */
	public static void preloadBackgroundMusic(final String pPath) {
		Cocos2dxHelper.sCocos2dMusic.preloadBackgroundMusic(pPath);
	}

	/*
 	 * @brief Play background music
	 * @param pPath The path of the background music file
	 * @param isLoop Whether the background music loop or not.
	 */
	public static void playBackgroundMusic(final String pPath, final boolean isLoop) {
		Cocos2dxHelper.sCocos2dMusic.playBackgroundMusic(pPath, isLoop);
	}

	/*
	 * @brief Resume playing background music.
	 */
	public static void resumeBackgroundMusic() {
		Cocos2dxHelper.sCocos2dMusic.resumeBackgroundMusic();
	}

	/*
 	 * @brief Pause playing background music.
	 */
	public static void pauseBackgroundMusic() {
		Cocos2dxHelper.sCocos2dMusic.pauseBackgroundMusic();
	}

	/*
	 * @brief Stop playing background music.
	 */
	public static void stopBackgroundMusic() {
		Cocos2dxHelper.sCocos2dMusic.stopBackgroundMusic();
	}

	/*
	 * @brief Rewind playing background music.
	 */
	public static void rewindBackgroundMusic() {
		Cocos2dxHelper.sCocos2dMusic.rewindBackgroundMusic();
	}

	/*
	 * @brief Indicates whether any background music can be played or not.
	 * @return true if background music can be played; otherwise false.
	 */
	public static boolean willPlayBackgroundMusic() {
		return Cocos2dxHelper.sCocos2dMusic.willPlayBackgroundMusic();
	}

	/*
	 * @brief Indicates whether the background music is playing.
	 * @return true if the background music is playing; otherwise false.
	 */
	public static boolean isBackgroundMusicPlaying() {
		return Cocos2dxHelper.sCocos2dMusic.isBackgroundMusicPlaying();
	}

	/*
	 * @brief Get the volume of the background music.
	 * @return the range of 0.0 as the minimum and 1.0 as the maximum.
	 */
	public static float getBackgroundMusicVolume() {
		return Cocos2dxHelper.sCocos2dMusic.getBackgroundVolume();
	}

	/*
	 * @brief Set the volume of the background music.
	 * @param volume must be range of 0.0 as the minimum and 1.0 as the maximum.
	 */
	public static void setBackgroundMusicVolume(final float volume) {
		Cocos2dxHelper.sCocos2dMusic.setBackgroundVolume(volume);
	}

	/*
	 * @brief Preload a compressed audio file.
	 * @param path The path of the effect file.
	 */
	public static void preloadEffect(final String path) {
		Cocos2dxHelper.getSound().preloadEffect(path);
	}

	/*
	 * @brief Play sound effect with a path, pitch, pan, and gain.
	 * @param path The path of the effect file.
	 * @param isLoop Determines whether to loop the effect playing or not.
	 * @param pitch Fequency, normal value is 1.0. will also change effect play time.
	 * @param pan Stereo effect, in the range of [-1..1] where -1 enables only left channel.
	 * @param gain Volume, in the range of [0..1]. The normal value is 1.
	 * @return Value of streamID from Java int method if it can preload effect; otherwise invalid soundId.
	 */
	public static int playEffect(final String path, final boolean isLoop, final float pitch, final float pan, final float gain) {
		return Cocos2dxHelper.getSound().playEffect(path, isLoop, pitch, pan, gain);
	}

	/*
	 * @brief Resume playing sound effect.
	 * @param soundId The return value of function playEffect.
	 */
	public static void resumeEffect(final int soundId) {
		Cocos2dxHelper.getSound().resumeEffect(soundId);
	}

	/*
 	 * @brief Pause playing sound effect.
	 * @param soundId The return value of function playEffect.
	 */
	public static void pauseEffect(final int soundId) {
		Cocos2dxHelper.getSound().pauseEffect(soundId);
	}

	/*
	 * @brief Stop playing sound effect.
	 * @param soundId The return value of function playEffect.
	 */
	public static void stopEffect(final int soundId) {
		Cocos2dxHelper.getSound().stopEffect(soundId);
	}

	/*
 	 * @brief Get the volume of the effects.
	 * @return the range of 0.0 as the minimum and 1.0 as the maximum.
	 */
	public static float getEffectsVolume() {
		return Cocos2dxHelper.getSound().getEffectsVolume();
	}

	/*
	 * @brief Set the volume of sound effects.
	 * @param volume must be range of 0.0 as the minimum and 1.0 as the maximum.
	 */
	public static void setEffectsVolume(final float volume) {
		Cocos2dxHelper.getSound().setEffectsVolume(volume);
	}

	/*
	 * @brief Unload the preloaded effect from internal buffer.
	 * @param path The path of the effect file.
	 */
	public static void unloadEffect(final String path) {
		Cocos2dxHelper.getSound().unloadEffect(path);
	}

	/*
	 * @brief Pause all playing sound effect.
	 */
	public static void pauseAllEffects() {
		Cocos2dxHelper.getSound().pauseAllEffects();
	}

	/*
 	 * @brief Resume all playing sound effects.
	 */
	public static void resumeAllEffects() {
		Cocos2dxHelper.getSound().resumeAllEffects();
	}

	/*
	 * @brief Stop all playing sound effects.
	 */
	public static void stopAllEffects() {
		Cocos2dxHelper.getSound().stopAllEffects();
	}

	/*
	 * @brief Set audio focus.
 	 * @param isAudioFocus Determines whether to set audio focused or not.
	 */
	static void setAudioFocus(boolean isAudioFocus) {
		sCocos2dMusic.setAudioFocus(isAudioFocus);
		getSound().setAudioFocus(isAudioFocus);
	}

	public static void end() {
		Cocos2dxHelper.sCocos2dMusic.end();
		Cocos2dxHelper.getSound().end();
	}

	/*
	 * @brief Enable accelerometer, and compass.
	 */
	public static void onResume() {
		sActivityVisible = true;
		if (Cocos2dxHelper.sAccelerometerEnabled) {
			Cocos2dxHelper.getAccelerometer().enableAccel();
		}
		if (Cocos2dxHelper.sCompassEnabled) {
			Cocos2dxHelper.getAccelerometer().enableCompass();
		}
	}

	/*
	 * @brief Disable accelerometer
	 */
	public static void onPause() {
		sActivityVisible = false;
		if (Cocos2dxHelper.sAccelerometerEnabled) {
			Cocos2dxHelper.getAccelerometer().disable();
		}
	}

	public static void onEnterBackground() {
		getSound().onEnterBackground();
		sCocos2dMusic.onEnterBackground();
	}
    
	public static void onEnterForeground() {
		getSound().onEnterForeground();
		sCocos2dMusic.onEnterForeground();
	}
    
	/*
	 * @brief Kill process.
	 */
	public static void terminateProcess() {
		android.os.Process.killProcess(android.os.Process.myPid());
	}

	/*
	 * @brief Show dialog.
	 */
	private static void showDialog(final String pTitle, final String pMessage) {
		Cocos2dxHelper.sCocos2dxHelperListener.showDialog(pTitle, pMessage);
	}

	/*
	 * @brief Set edit text dialog result.
	 */
	public static void setEditTextDialogResult(final String pResult) {
		try {
			final byte[] bytesUTF8 = pResult.getBytes("UTF8");

			Cocos2dxHelper.sCocos2dxHelperListener.runOnGLThread(new Runnable() {
			@Override
			public void run() {
				Cocos2dxHelper.nativeSetEditTextDialogResult(bytesUTF8);
			}
			});
		} catch (UnsupportedEncodingException pUnsupportedEncodingException) {
			/* Nothing. */
		}
	}

	/*
	 * @brief Get display DPI
	 * @return Value of DPI from Java static int method if it exists; otherwise -1.
	 */
	public static int getDPI()
	{
		if (sActivity != null)
		{
			DisplayMetrics metrics = new DisplayMetrics();
			WindowManager wm = sActivity.getWindowManager();
			if (wm != null)
			{
				Display d = wm.getDefaultDisplay();
				if (d != null)
				{
					d.getMetrics(metrics);
					return (int)(metrics.density*160.0f);
				}
			}
		}
		return -1;
	}
    
	// ===========================================================
	// Functions for CCUserDefault
	// ===========================================================
    
	public static boolean getBoolForKey(String key, boolean defaultValue) {
		SharedPreferences settings = sActivity.getSharedPreferences(Cocos2dxHelper.PREFS_NAME, 0);
		try {
			return settings.getBoolean(key, defaultValue);
		}
		catch (Exception ex) {
			ex.printStackTrace();

			Map allValues = settings.getAll();
			Object value = allValues.get(key);
			if ( value instanceof String)
			{
				return  Boolean.parseBoolean(value.toString());
			}
			else if (value instanceof Integer)
			{
				int intValue = ((Integer) value).intValue();
				return (intValue !=  0) ;
			}
			else if (value instanceof Float)
			{
				float floatValue = ((Float) value).floatValue();
				return (floatValue != 0.0f);
			}
		}

		return defaultValue;
	}
    
	public static int getIntegerForKey(String key, int defaultValue) {
		SharedPreferences settings = sActivity.getSharedPreferences(Cocos2dxHelper.PREFS_NAME, 0);
		try {
			return settings.getInt(key, defaultValue);
		}
		catch (Exception ex) {
			ex.printStackTrace();

			Map allValues = settings.getAll();
			Object value = allValues.get(key);
			if ( value instanceof String) {
				return  Integer.parseInt(value.toString());
			}
			else if (value instanceof Float)
			{
				return ((Float) value).intValue();
			}
			else if (value instanceof Boolean)
			{
				boolean booleanValue = ((Boolean) value).booleanValue();
				if (booleanValue)
					return 1;
			}
		}

		return defaultValue;
	}
    
	public static float getFloatForKey(String key, float defaultValue) {
		SharedPreferences settings = sActivity.getSharedPreferences(Cocos2dxHelper.PREFS_NAME, 0);
		try {
			return settings.getFloat(key, defaultValue);
		}
		catch (Exception ex) {
			ex.printStackTrace();

			Map allValues = settings.getAll();
			Object value = allValues.get(key);
			if ( value instanceof String) {
				return  Float.parseFloat(value.toString());
			}
			else if (value instanceof Integer)
			{
				return ((Integer) value).floatValue();
			}
			else if (value instanceof Boolean)
			{
				boolean booleanValue = ((Boolean) value).booleanValue();
				if (booleanValue)
					return 1.0f;
			}
		}

		return defaultValue;
	}
    
	public static double getDoubleForKey(String key, double defaultValue) {
		// SharedPreferences doesn't support saving double value
		return getFloatForKey(key, (float) defaultValue);
	}
    
	public static String getStringForKey(String key, String defaultValue) {
		SharedPreferences settings = sActivity.getSharedPreferences(Cocos2dxHelper.PREFS_NAME, 0);
		try {
			return settings.getString(key, defaultValue);
		}
		catch (Exception ex) {
			ex.printStackTrace();
            
		return settings.getAll().get(key).toString();
		}
	}
    
	public static void setBoolForKey(String key, boolean value) {
		SharedPreferences settings = sActivity.getSharedPreferences(Cocos2dxHelper.PREFS_NAME, 0);
		SharedPreferences.Editor editor = settings.edit();
		editor.putBoolean(key, value);
		editor.apply();
	}
    
	public static void setIntegerForKey(String key, int value) {
		SharedPreferences settings = sActivity.getSharedPreferences(Cocos2dxHelper.PREFS_NAME, 0);
		SharedPreferences.Editor editor = settings.edit();
		editor.putInt(key, value);
		editor.apply();
	}
    
	public static void setFloatForKey(String key, float value) {
		SharedPreferences settings = sActivity.getSharedPreferences(Cocos2dxHelper.PREFS_NAME, 0);
		SharedPreferences.Editor editor = settings.edit();
		editor.putFloat(key, value);
		editor.apply();
	}
    
	public static void setDoubleForKey(String key, double value) {
		// SharedPreferences doesn't support recording double value
		SharedPreferences settings = sActivity.getSharedPreferences(Cocos2dxHelper.PREFS_NAME, 0);
		SharedPreferences.Editor editor = settings.edit();
		editor.putFloat(key, (float)value);
		editor.apply();
	}
    
	public static void setStringForKey(String key, String value) {
		SharedPreferences settings = sActivity.getSharedPreferences(Cocos2dxHelper.PREFS_NAME, 0);
		SharedPreferences.Editor editor = settings.edit();
		editor.putString(key, value);
		editor.apply();
	}
    
	public static void deleteValueForKey(String key) {
		SharedPreferences settings = sActivity.getSharedPreferences(Cocos2dxHelper.PREFS_NAME, 0);
		SharedPreferences.Editor editor = settings.edit();
		editor.remove(key);
		editor.apply();
	}

	public static byte[] conversionEncoding(byte[] text, String fromCharset,String newCharset)
	{
		try {
			String str = new String(text,fromCharset);
			return str.getBytes(newCharset);
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		}

		return null;
	}
    
	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================

	public static interface Cocos2dxHelperListener {
		public void showDialog(final String pTitle, final String pMessage);

		public void runOnGLThread(final Runnable pRunnable);
	}

	//Enhance API modification begin
	public static int setResolutionPercent(int per) {
		try {
			if (mGameServiceBinder != null) {
				return mGameServiceBinder.setPreferredResolution(per);
			}
			return -1;
		} catch (Exception e) {
			e.printStackTrace();
			return -1;
		}
	}

	public static int setFPS(int fps) {
		try {
			if (mGameServiceBinder != null) {
				return mGameServiceBinder.setFramePerSecond(fps);
			}
			return -1;
		} catch (Exception e) {
			e.printStackTrace();
			return -1;
		}
	}

	public static int fastLoading(int sec) {
		try {
			if (mGameServiceBinder != null) {
				return mGameServiceBinder.boostUp(sec);
			}
			return -1;
		} catch (Exception e) {
			e.printStackTrace();
			return -1;
		}
	}

	/*
	 * @brief Get temperature.
	 * @return Value of temperature from Java static int method if it exists; otherwise -1
	 */
	public static int getTemperature() {
		try {
			if (mGameServiceBinder != null) {
				return mGameServiceBinder.getAbstractTemperature();
			}
			return -1;
		} catch (Exception e) {
			e.printStackTrace();
			return -1;
		}
	}

	public static int setLowPowerMode(boolean enable) {
		try {
			if (mGameServiceBinder != null) {
				return mGameServiceBinder.setGamePowerSaving(enable);
			}
			return -1;
		} catch (Exception e) {
			e.printStackTrace();
			return -1;
		}
	}

	//Enhance API modification end     
	public static float[] getAccelValue() {
		return Cocos2dxHelper.getAccelerometer().accelerometerValues;
	}

	public static float[] getCompassValue() {
		return Cocos2dxHelper.getAccelerometer().compassFieldValues;
	}

	public static int getSDKVersion() {
		return Build.VERSION.SDK_INT;
	}

	/*
	 * @brief Get cocos2dx accelerometer.
	 * @return Value of Cocos2dx accelerometer from Java static Cocos2dxAccelerometer method
	 */
	private static Cocos2dxAccelerometer getAccelerometer() {
		if (null == sCocos2dxAccelerometer)
			Cocos2dxHelper.sCocos2dxAccelerometer = new Cocos2dxAccelerometer(sActivity);

		return sCocos2dxAccelerometer;
	}

	/*
	 * @brief Get cocos2dx sound.
	 * @return Value of Cocos2dx sound from Java static Cocos2dxSound method
 	 */
	private static Cocos2dxSound getSound() {
		if (null == sCocos2dSound)
			sCocos2dSound = new Cocos2dxSound(sActivity);

		return sCocos2dSound;
	}
}
