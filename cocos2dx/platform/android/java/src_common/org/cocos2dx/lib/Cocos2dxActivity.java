/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

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

import java.lang.ref.WeakReference;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.res.AssetManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.DisplayMetrics;
import android.util.Log;

public class Cocos2dxActivity extends Activity{

	protected Cocos2dxGLSurfaceView mGLView;
    private static Cocos2dxMusic backgroundMusicPlayer;
    private static Cocos2dxSound soundPlayer;
    private static Cocos2dxAccelerometer accelerometer;
    private static AssetManager assetManager;
    private static boolean accelerometerEnabled = false;
    private static Handler handler;
    private final static int HANDLER_SHOW_DIALOG = 1;
    private final static int HANDLER_SHOW_EDITBOX_DIALOG = 2;
    
    private static String packageName;
    
    private static native void nativeSetPaths(String apkPath);
    private static native void nativeSetEditboxText(byte[] text);
    
    
    static class ShowDialogHandler extends Handler {
        WeakReference<Cocos2dxActivity> mActivity;

        ShowDialogHandler(Cocos2dxActivity activity) {
            mActivity = new WeakReference<Cocos2dxActivity>(activity);
        }

        @Override
        public void handleMessage(Message msg) {
        	Cocos2dxActivity theActivity = mActivity.get();
    		switch(msg.what) {
    		case HANDLER_SHOW_DIALOG:
    			theActivity.showDialog(((DialogMessage)msg.obj).title, ((DialogMessage)msg.obj).message);
    			break;
    		case HANDLER_SHOW_EDITBOX_DIALOG:
    			theActivity.onShowEditBoxDialog((EditBoxMessage)msg.obj);
    			break;
    		}
        }
    };

	public Cocos2dxGLSurfaceView getGLView() {
		return mGLView;
	}

	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        // get frame size
        DisplayMetrics dm = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(dm);
        accelerometer = new Cocos2dxAccelerometer(this);

        // init media player and sound player
        backgroundMusicPlayer = new Cocos2dxMusic(this);
        soundPlayer = new Cocos2dxSound(this);
        
        // init asset manager for jni call
        assetManager = getAssets();
        
        // init bitmap context
        Cocos2dxBitmap.setContext(this);
        
        handler = new ShowDialogHandler(this);
    }
    
    public static String getDeviceModel(){
    	return Build.MODEL;
    }
    
    public static AssetManager getAssetManager() {
    	return assetManager;
    }
    
    public static String getCurrentLanguage() {
    	String languageName = java.util.Locale.getDefault().getLanguage();
    	return languageName;
    }
    
    public static void showMessageBox(String title, String message){
    	Message msg = new Message();
    	msg.what = HANDLER_SHOW_DIALOG;
    	msg.obj = new DialogMessage(title, message);
    	
    	handler.sendMessage(msg);
    } 

    public static void enableAccelerometer() {
        accelerometerEnabled = true;
        accelerometer.enable();
    }

    public static void disableAccelerometer() {
        accelerometerEnabled = false;
        accelerometer.disable();
    }

    public static void preloadBackgroundMusic(String path){
    	backgroundMusicPlayer.preloadBackgroundMusic(path);
    }
    
    public static void playBackgroundMusic(String path, boolean isLoop){
    	backgroundMusicPlayer.playBackgroundMusic(path, isLoop);
    }
    
    public static void stopBackgroundMusic(){
    	backgroundMusicPlayer.stopBackgroundMusic();
    }
    
    public static void pauseBackgroundMusic(){
    	backgroundMusicPlayer.pauseBackgroundMusic();
    }
    
    public static void resumeBackgroundMusic(){
    	backgroundMusicPlayer.resumeBackgroundMusic();
    }
    
    public static void rewindBackgroundMusic(){
    	backgroundMusicPlayer.rewindBackgroundMusic();
    }
    
    public static boolean isBackgroundMusicPlaying(){
    	return backgroundMusicPlayer.isBackgroundMusicPlaying();
    }
    
    public static float getBackgroundMusicVolume(){
    	return backgroundMusicPlayer.getBackgroundVolume();
    }
    
    public static void setBackgroundMusicVolume(float volume){
    	backgroundMusicPlayer.setBackgroundVolume(volume);
    }
    
    public static int playEffect(String path, boolean isLoop){
    	return soundPlayer.playEffect(path, isLoop);
    }
    
    public static void stopEffect(int soundId){
    	soundPlayer.stopEffect(soundId);
    }
    
    public static void pauseEffect(int soundId){
    	soundPlayer.pauseEffect(soundId);
    }
    
    public static void resumeEffect(int soundId){
    	soundPlayer.resumeEffect(soundId);
    }
    
    public static float getEffectsVolume(){
    	return soundPlayer.getEffectsVolume();
    }
    
    public static void setEffectsVolume(float volume){
    	soundPlayer.setEffectsVolume(volume);
    }
    
    public static void preloadEffect(String path){
    	soundPlayer.preloadEffect(path);
    }
    
    public static void unloadEffect(String path){
    	soundPlayer.unloadEffect(path);
    }
    
    public static void stopAllEffects(){
    	soundPlayer.stopAllEffects();
    }
    
    public static void pauseAllEffects(){
    	soundPlayer.pauseAllEffects();
    }
    
    public static void resumeAllEffects(){
    	soundPlayer.resumeAllEffects();
    }
    
    public static void end(){
    	backgroundMusicPlayer.end();
    	soundPlayer.end();
    }
    
    public static String getCocos2dxPackageName(){
    	return packageName;
    }
    
    public static void terminateProcess(){
    	android.os.Process.killProcess(android.os.Process.myPid());
    }

    @Override
    protected void onResume() {
    	super.onResume();
    	if (accelerometerEnabled) {
    	    accelerometer.enable();
    	}
    }

    @Override
    protected void onPause() {
    	super.onPause();
    	if (accelerometerEnabled) {
    	    accelerometer.disable();
    	}
    }

    protected void setPackageName(String packageName) {
    	Cocos2dxActivity.packageName = packageName;
    	
    	String apkFilePath = "";
        ApplicationInfo appInfo = null;
        PackageManager packMgmr = getApplication().getPackageManager();
        try {
            appInfo = packMgmr.getApplicationInfo(packageName, 0);
        } catch (NameNotFoundException e) {
            e.printStackTrace();
            throw new RuntimeException("Unable to locate assets, aborting...");
        }
        apkFilePath = appInfo.sourceDir;
        Log.w("apk path", apkFilePath);

        // add this link at the renderer class
        nativeSetPaths(apkFilePath);
    }
    
    private void showDialog(String title, String message){
    	Dialog dialog = new AlertDialog.Builder(this)
	    .setTitle(title)
	    .setMessage(message)
	    .setPositiveButton("Ok",
	    new DialogInterface.OnClickListener()
	    {
	    	public void onClick(DialogInterface dialog, int whichButton){
	    		
	    	}
	    }).create();

	    dialog.show();
    }

    private static void showEditBoxDialog(String title, String content, int inputMode, int inputFlag, int returnType, int maxLength)
    {   
    	Message msg = new Message();
    	msg.what = HANDLER_SHOW_EDITBOX_DIALOG;
    	msg.obj = new EditBoxMessage(title, content, inputMode, inputFlag, returnType, maxLength);
    	handler.sendMessage(msg);
    }
    
    private void onShowEditBoxDialog(EditBoxMessage msg)
    {	
		Dialog dialog = new Cocos2dxEditBoxDialog(this, msg);
		dialog.show();
    }
    
    public void setEditBoxResult(String editResult)
    {
		Log.i("editbox_content", editResult);
	
        try
        {
        	final byte[] bytesUTF8 = editResult.getBytes("UTF8");
            // pass utf8 string from editbox activity to native.
        	// Should invoke native method in GL thread.
        	mGLView.queueEvent(new Runnable() {
                @Override
                public void run() {
                	nativeSetEditboxText(bytesUTF8);
                }
            });
        }
        catch (java.io.UnsupportedEncodingException e)
        {
            e.printStackTrace();
        } 
    }
}

class DialogMessage {
	public String title;
	public String message;
	
	public DialogMessage(String title, String message){
		this.message = message;
		this.title = title;
	}
}

class EditBoxMessage {
	public String title;
	public String content;
	public int inputMode;
	public int inputFlag;
	public int returnType;
	public int maxLength;
	
	public EditBoxMessage(String title, String content, int inputMode, int inputFlag, int returnType, int maxLength){
		this.content = content;
		this.title = title;
		this.inputMode = inputMode;
		this.inputFlag = inputFlag;
		this.returnType = returnType;
		this.maxLength = maxLength;
	}
}
