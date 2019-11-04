/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

import android.annotation.SuppressLint;
import android.content.pm.PackageManager;
import android.graphics.Rect;
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
import android.view.DisplayCutout;
import android.view.KeyCharacterMap;
import android.view.KeyEvent;
import android.view.ViewConfiguration;
import android.view.Window;
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
import java.util.List;
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

    public static void runOnGLThread(final Runnable r) {
        ((Cocos2dxActivity)sActivity).runOnGLThread(r);
    }

    private static boolean sInited = false;
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
    
    // This function returns the absolute path to the OBB if it exists,
    // else it returns the absolute path to the APK.
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

    //remove directory 
    public static boolean removeDirectory(final String directory)
    {
        try{
            File file = new File(directory);
            recursionDeleteFile(file);
            return true;
        }catch(Exception ex){
            ex.printStackTrace();
            return false;
        }
    }


    private static void recursionDeleteFile(File file)
    {
        if (file.isFile()) {
            file.delete();
            return;
        }
        if (file.isDirectory()) {
            File[] childrenFile = file.listFiles();
            if (childrenFile == null || childrenFile.length == 0) {
                file.delete();
                return;
            }
            for (File f : childrenFile) {
                recursionDeleteFile(f);
            }
            file.delete();
        }
    }
    
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
    
    public static Activity getActivity() {
        return sActivity;
    }
    
    public static void addOnActivityResultListener(OnActivityResultListener listener) {
        onActivityResultListeners.add(listener);
    }
    
    public static Set<OnActivityResultListener> getOnActivityResultListeners() {
        return onActivityResultListeners;
    }
    
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

    public static void enableAccelerometer() {
        Cocos2dxHelper.sAccelerometerEnabled = true;
        Cocos2dxHelper.getAccelerometer().enableAccel();
    }

    public static void enableCompass() {
        Cocos2dxHelper.sCompassEnabled = true;
        Cocos2dxHelper.getAccelerometer().enableCompass();
    }

    public static void setAccelerometerInterval(float interval) {
        Cocos2dxHelper.getAccelerometer().setInterval(interval);
    }

    public static void disableAccelerometer() {
        Cocos2dxHelper.sAccelerometerEnabled = false;
        Cocos2dxHelper.getAccelerometer().disable();
    }

    public static void setKeepScreenOn(boolean value) {
        ((Cocos2dxActivity)sActivity).setKeepScreenOn(value);
    }

    public static void vibrate(float duration) {
        sVibrateService.vibrate((long)(duration * 1000));
    }

 	public static String getVersion() {
 		try {
 			String version = Cocos2dxActivity.getContext().getPackageManager().getPackageInfo(Cocos2dxActivity.getContext().getPackageName(), 0).versionName;
 			return version;
 		} catch(Exception e) {
 			return "";
 		}
 	}

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

    public static void preloadBackgroundMusic(final String pPath) {
        Cocos2dxHelper.sCocos2dMusic.preloadBackgroundMusic(pPath);
    }

    public static void playBackgroundMusic(final String pPath, final boolean isLoop) {
        Cocos2dxHelper.sCocos2dMusic.playBackgroundMusic(pPath, isLoop);
    }

    public static void resumeBackgroundMusic() {
        Cocos2dxHelper.sCocos2dMusic.resumeBackgroundMusic();
    }

    public static void pauseBackgroundMusic() {
        Cocos2dxHelper.sCocos2dMusic.pauseBackgroundMusic();
    }

    public static void stopBackgroundMusic() {
        Cocos2dxHelper.sCocos2dMusic.stopBackgroundMusic();
    }

    public static void rewindBackgroundMusic() {
        Cocos2dxHelper.sCocos2dMusic.rewindBackgroundMusic();
    }

    public static boolean willPlayBackgroundMusic() {
        return Cocos2dxHelper.sCocos2dMusic.willPlayBackgroundMusic();
    }

    public static boolean isBackgroundMusicPlaying() {
        return Cocos2dxHelper.sCocos2dMusic.isBackgroundMusicPlaying();
    }

    public static float getBackgroundMusicVolume() {
        return Cocos2dxHelper.sCocos2dMusic.getBackgroundVolume();
    }

    public static void setBackgroundMusicVolume(final float volume) {
        Cocos2dxHelper.sCocos2dMusic.setBackgroundVolume(volume);
    }

    public static void preloadEffect(final String path) {
        Cocos2dxHelper.getSound().preloadEffect(path);
    }

    public static int playEffect(final String path, final boolean isLoop, final float pitch, final float pan, final float gain) {
        return Cocos2dxHelper.getSound().playEffect(path, isLoop, pitch, pan, gain);
    }

    public static void resumeEffect(final int soundId) {
        Cocos2dxHelper.getSound().resumeEffect(soundId);
    }

    public static void pauseEffect(final int soundId) {
        Cocos2dxHelper.getSound().pauseEffect(soundId);
    }

    public static void stopEffect(final int soundId) {
        Cocos2dxHelper.getSound().stopEffect(soundId);
    }

    public static float getEffectsVolume() {
        return Cocos2dxHelper.getSound().getEffectsVolume();
    }

    public static void setEffectsVolume(final float volume) {
        Cocos2dxHelper.getSound().setEffectsVolume(volume);
    }

    public static void unloadEffect(final String path) {
        Cocos2dxHelper.getSound().unloadEffect(path);
    }

    public static void pauseAllEffects() {
        Cocos2dxHelper.getSound().pauseAllEffects();
    }

    public static void resumeAllEffects() {
        Cocos2dxHelper.getSound().resumeAllEffects();
    }

    public static void stopAllEffects() {
        Cocos2dxHelper.getSound().stopAllEffects();
    }

    static void setAudioFocus(boolean isAudioFocus) {
        sCocos2dMusic.setAudioFocus(isAudioFocus);
        getSound().setAudioFocus(isAudioFocus);
    }

    public static void end() {
        Cocos2dxHelper.sCocos2dMusic.end();
        Cocos2dxHelper.getSound().end();
    }

    public static void onResume() {
        sActivityVisible = true;
        if (Cocos2dxHelper.sAccelerometerEnabled) {
            Cocos2dxHelper.getAccelerometer().enableAccel();
        }
        if (Cocos2dxHelper.sCompassEnabled) {
            Cocos2dxHelper.getAccelerometer().enableCompass();
        }
    }

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
    
    public static void terminateProcess() {
        // Remove it from recent apps.
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            sActivity.finishAndRemoveTask();
        }
        android.os.Process.killProcess(android.os.Process.myPid());
    }

    private static void showDialog(final String pTitle, final String pMessage) {
        Cocos2dxHelper.sCocos2dxHelperListener.showDialog(pTitle, pMessage);
    }


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

    /**
     * Returns whether the screen has a round shape. Apps may choose to change styling based
     * on this property, such as the alignment or layout of text or informational icons.
     *
     * @return true if the screen is rounded, false otherwise
     */
    public static boolean isScreenRound() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (sActivity.getResources().getConfiguration().isScreenRound()) {
                return true;
            }
        }

        return false;
    }

    /**
     * Returns whether the window is always allowed to extend into the DisplayCutout areas on the short edges of the screen.
     *
     * @return true if the window in display cutout mode on the short edges of the screen, false otherwise
     */
    @SuppressLint("InlinedApi")
    public static boolean isCutoutEnabled() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            WindowManager.LayoutParams lp = sActivity.getWindow().getAttributes();
            return lp.layoutInDisplayCutoutMode == WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
        }

        return false;
    }

    /**
     * Returns safe insets array.
     *
     * @return array of int with safe insets values
     */
    @SuppressLint("NewApi") 
    public static int[] getSafeInsets() {
        final int[] safeInsets = new int[]{0, 0, 0, 0};
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            Window cocosWindow = sActivity.getWindow();
            DisplayCutout displayCutout = cocosWindow.getDecorView().getRootWindowInsets().getDisplayCutout();
            // Judge whether it is cutouts (aka notch) screen phone by judge cutout equle to null
            if (displayCutout != null) {
                List<Rect> rects = displayCutout.getBoundingRects();
                // Judge whether it is cutouts (aka notch) screen phone by judge cutout rects is null or zero size
                if (rects != null && rects.size() != 0) {
                    safeInsets[0] = displayCutout.getSafeInsetBottom();
                    safeInsets[1] = displayCutout.getSafeInsetLeft();
                    safeInsets[2] = displayCutout.getSafeInsetRight();
                    safeInsets[3] = displayCutout.getSafeInsetTop();
                }
            }
        }

        return safeInsets;
    }

    /**
     * Queries about whether any physical keys exist on the
     * any keyboard attached to the device and returns <code>true</code>
     * if the device does not have physical keys
     *
     * @return Returns <code>true</code> if the device have no physical keys,
     * otherwise <code>false</code> will returned.
     */
    public static boolean hasSoftKeys() {
        boolean hasSoftwareKeys = true;

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR1) {
            Display display = sActivity.getWindowManager().getDefaultDisplay();

            DisplayMetrics realDisplayMetrics = new DisplayMetrics();
            display.getRealMetrics(realDisplayMetrics);

            int realHeight = realDisplayMetrics.heightPixels;
            int realWidth = realDisplayMetrics.widthPixels;

            DisplayMetrics displayMetrics = new DisplayMetrics();
            display.getMetrics(displayMetrics);

            int displayHeight = displayMetrics.heightPixels;
            int displayWidth = displayMetrics.widthPixels;

            hasSoftwareKeys = (realWidth - displayWidth) > 0 ||
                    (realHeight - displayHeight) > 0;
        } else {
            boolean hasMenuKey = ViewConfiguration.get(sActivity).hasPermanentMenuKey();
            boolean hasBackKey = KeyCharacterMap.deviceHasKey(KeyEvent.KEYCODE_BACK);
            hasSoftwareKeys = !hasMenuKey && !hasBackKey;
        }
        return hasSoftwareKeys;
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

    private static Cocos2dxAccelerometer getAccelerometer() {
        if (null == sCocos2dxAccelerometer)
            Cocos2dxHelper.sCocos2dxAccelerometer = new Cocos2dxAccelerometer(sActivity);

        return sCocos2dxAccelerometer;
    }

    private static Cocos2dxSound getSound() {
        if (null == sCocos2dSound)
            sCocos2dSound = new Cocos2dxSound(sActivity);

        return sCocos2dSound;
    }
}
