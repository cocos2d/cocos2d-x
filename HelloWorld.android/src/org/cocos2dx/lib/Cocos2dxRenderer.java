package org.cocos2dx.lib;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView;

public class Cocos2dxRenderer implements GLSurfaceView.Renderer {
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
    	nativeInit(Cocos2dxActivity.screenWidth, Cocos2dxActivity.screenHeight);
    }

    public void onSurfaceChanged(GL10 gl, int w, int h) {  	
    }

    public void onDrawFrame(GL10 gl) {
        nativeRender();
    }

    private static native void nativeRender();
    private static native void nativeInit(int w, int h);
}