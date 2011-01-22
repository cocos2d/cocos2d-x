package org.cocos2dx.lib;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView;

public class Cocos2dxRenderer implements GLSurfaceView.Renderer {
	private static long animationInterval = (long)(1.0 / 60 * 1000000000L);
	private long now;
	private long last;
	
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
    	now = last = System.nanoTime();
    	nativeInit(Cocos2dxActivity.screenWidth, Cocos2dxActivity.screenHeight);  	
    }

    public void onSurfaceChanged(GL10 gl, int w, int h) {  	
    }

    public void onDrawFrame(GL10 gl) {
    	now = System.nanoTime();
    	
    	if (now - last >= animationInterval){ 
    		last = now;
    		nativeRender();   		
    	}
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
    
    public static void setAnimationInterval(double interval){
    	animationInterval = (long)(interval * 1000000000L);
    }
    
    private static native void nativeTouchesBegin(float x, float y);
    private static native void nativeTouchesEnd(float x, float y);
    private static native void nativeTouchesMove(float x, float y);
    private static native void nativeTouchesCancel(float x, float y);
    private static native void nativeRender();
    private static native void nativeInit(int w, int h);
}