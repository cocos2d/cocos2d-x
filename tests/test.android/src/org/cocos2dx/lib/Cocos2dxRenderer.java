package org.cocos2dx.lib;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView;
import android.util.Log;

public class Cocos2dxRenderer implements GLSurfaceView.Renderer {
	private String apkPath;

    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
    	Log.d("Cocos2dxRenderer", "nativeInit with width: " + Cocos2dxActivity.screenWidth +
    			" height: " + Cocos2dxActivity.screenHeight + " apkPath: " + apkPath);
    	nativeInit(Cocos2dxActivity.screenWidth, Cocos2dxActivity.screenHeight, apkPath);
    }

    public void onSurfaceChanged(GL10 gl, int w, int h) {  	
    }

    public void onDrawFrame(GL10 gl) {
        nativeRender();
    }
    
    public void handleActionDown(float x, float y)
    {
    	nativeTouchesBegin(x, y);
    }
    
    public void handleActionUp(float x, float y)
    {
    	nativeTouchesEnd(x, y);
    }
    
    public void handleActionCancel(float x, float y)
    {
    	nativeTouchesCancel(x, y);
    }
    
    public void handleActionMove(float x, float y)
    {
    	nativeTouchesMove(x, y);
    }

	public void setApkPath(String apkPath) {
		this.apkPath = apkPath;
	}

    private static native void nativeTouchesBegin(float x, float y);
    private static native void nativeTouchesEnd(float x, float y);
    private static native void nativeTouchesMove(float x, float y);
    private static native void nativeTouchesCancel(float x, float y);
    private static native void nativeRender();
    private static native void nativeInit(int w, int h, String apkPath);
}