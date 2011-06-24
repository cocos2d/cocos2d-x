/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This is a small port of the "San Angeles Observation" demo
 * program for OpenGL ES 1.x. For more details, see:
 *
 *    http://jet.ro/visuals/san-angeles-observation/
 *
 * This program demonstrates how to use a GLSurfaceView from Java
 * along with native OpenGL calls to perform frame rendering.
 *
 * Touching the screen will start/stop the animation.
 *
 * Note that the demo runs much faster on the emulator than on
 * real devices, this is mainly due to the following facts:
 *
 * - the demo sends bazillions of polygons to OpenGL without
 *   even trying to do culling. Most of them are clearly out
 *   of view.
 *
 * - on a real device, the GPU bus is the real bottleneck
 *   that prevent the demo from getting acceptable performance.
 *
 * - the software OpenGL engine used in the emulator uses
 *   the system bus instead, and its code rocks :-)
 *
 * Fixing the program to send less polygons to the GPU is left
 * as an exercise to the reader. As always, patches welcomed :-)
 */

package org.cocos2dx.lib;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.DisplayMetrics;
import android.util.Log;

public class Cocos2dxActivity extends Activity{
	public static int screenWidth;
    public static int screenHeight;
    private static Cocos2dxMusic backgroundMusicPlayer;
    private static Cocos2dxSound soundPlayer;
    private static Cocos2dxAccelerometer accelerometer;
    private static boolean accelerometerEnabled = false;
    private static Handler handler;
    private final static int HANDLER_SHOW_DIALOG = 1;
    private static String packageName;

    private static native void nativeSetPaths(String apkPath);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        // get frame size
        DisplayMetrics dm = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(dm);
        screenWidth = dm.widthPixels;
        screenHeight = dm.heightPixels;
        accelerometer = new Cocos2dxAccelerometer(this);

        // init media player and sound player
        backgroundMusicPlayer = new Cocos2dxMusic(this);
        soundPlayer = new Cocos2dxSound(this);
        
        handler = new Handler(){
        	public void handleMessage(Message msg){
        		switch(msg.what){
        		case HANDLER_SHOW_DIALOG:
        			showDialog(((DialogMessage)msg.obj).title, ((DialogMessage)msg.obj).message);
        			break;
        		}
        	}
        };
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
    
    public static int playEffect(String path){
    	return soundPlayer.playEffect(path);
    }
    
    public static void stopEffect(int soundId){
    	soundPlayer.stopEffect(soundId);
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
    
    public static void end(){
    	backgroundMusicPlayer.end();
    	soundPlayer.end();
    }
    
    public static String getCocos2dxPackageName(){
    	return packageName;
    }

    @Override
    protected void onResume() {
    	super.onResume();
    	if (accelerometerEnabled) {
    	    accelerometer.enable();
    	}
    	
    	// resume background music
    	resumeBackgroundMusic();
    }

    @Override
    protected void onPause() {
    	super.onPause();
    	if (accelerometerEnabled) {
    	    accelerometer.disable();
    	}
    	
    	// pause background music
    	pauseBackgroundMusic();
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
}

class DialogMessage {
	public String title;
	public String message;
	
	public DialogMessage(String title, String message){
		this.message = message;
		this.title = title;
	}
}
