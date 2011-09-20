package org.cocos2dx.lib;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView;

public class Cocos2dxRenderer implements GLSurfaceView.Renderer {
	private final static long NANOSECONDSPERSECOND = 1000000000L;
	private final static long NANOSECONDSPERMINISECOND = 1000000;
	private static long animationInterval = (long)(1.0 / 60 * NANOSECONDSPERSECOND);
	private long last;
	
    public void onSurfaceCreated(GL10 gl, EGLConfig config) { 	
    	nativeInit(Cocos2dxActivity.screenWidth, Cocos2dxActivity.screenHeight); 
    	last = System.nanoTime();
    }

    public void onSurfaceChanged(GL10 gl, int w, int h) {  	
    }
    
    public void onDrawFrame(GL10 gl) {
    	
    	long now = System.nanoTime();
    	long interval = now - last;
    	
    	// should render a frame when onDrawFrame() is called
    	// or there is a "ghost"
    	nativeRender();   	
   	
    	// fps controlling
    	if (interval < animationInterval){ 
    		try {
    			// because we render it before, so we should sleep twice time interval
    			Thread.sleep((animationInterval - interval) * 2 / NANOSECONDSPERMINISECOND);
    		} catch (Exception e){}
    	}	
    	
    	last = now;
    }
    
    public void handleActionDown(int id, float x, float y)
    {
    	nativeTouchesBegin(id, x, y);
    }
    
    public void handleActionUp(int id, float x, float y)
    {
    	nativeTouchesEnd(id, x, y);
    }
    
    public void handleActionCancel(int[] id, float[] x, float[] y)
    {
    	nativeTouchesCancel(id, x, y);
    }
    
    public void handleActionMove(int[] id, float[] x, float[] y)
    {
    	nativeTouchesMove(id, x, y);
    }
    
    public void handleKeyDown(int keyCode)
    {
    	nativeKeyDown(keyCode);
    }
    
    public void handleOnPause(){
    	nativeOnPause();
    }
    
    public void handleOnResume(){
    	nativeOnResume();
    }
    
    public static void setAnimationInterval(double interval){
    	animationInterval = (long)(interval * NANOSECONDSPERSECOND);
    }
    private static native void nativeTouchesBegin(int id, float x, float y);
    private static native void nativeTouchesEnd(int id, float x, float y);
    private static native void nativeTouchesMove(int[] id, float[] x, float[] y);
    private static native void nativeTouchesCancel(int[] id, float[] x, float[] y);
    private static native boolean nativeKeyDown(int keyCode);
    private static native void nativeRender();
    private static native void nativeInit(int w, int h);
    private static native void nativeOnPause();
    private static native void nativeOnResume();
    
    /////////////////////////////////////////////////////////////////////////////////
    // handle input method edit message
    /////////////////////////////////////////////////////////////////////////////////
    
    public void handleInsertText(final String text) {
    	nativeInsertText(text);
    }
    
    public void handleDeleteBackward() {
    	nativeDeleteBackward();
    }

	public String getContentText() {
		return nativeGetContentText();
	}
	
    private static native void nativeInsertText(String text);
    private static native void nativeDeleteBackward();
    private static native String nativeGetContentText();
}
