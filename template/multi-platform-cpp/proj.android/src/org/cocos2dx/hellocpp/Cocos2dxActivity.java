package org.cocos2dx.hellocpp;

import android.app.NativeActivity;
import android.os.Bundle;

public class Cocos2dxActivity extends NativeActivity{

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		
		//1.Set the format of window for supports translucency
		//getWindow().setFormat(PixelFormat.TRANSLUCENT);
		
		//2.You need configure egl attribs in cocos\2d\platform\android\nativeactivity.cpp on some android versions(eg.4.4) for supports translucency.
		//eg:
		/*const EGLint attribs[] = {
	            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
	            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
	            EGL_BUFFER_SIZE, 32,
	            EGL_DEPTH_SIZE, 16,
	            EGL_STENCIL_SIZE, 8,
	            EGL_NONE
	    };*/
		
	}
}
