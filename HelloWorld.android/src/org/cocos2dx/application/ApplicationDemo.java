package org.cocos2dx.application;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;


import android.opengl.GLSurfaceView;
import android.os.Bundle;

public class ApplicationDemo extends Cocos2dxActivity{
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		
        mGLView = new Cocos2dxGLSurfaceView(this);
        setContentView(mGLView);
	}
	
	 @Override
	 protected void onPause() {
	     super.onPause();
	     mGLView.onPause();
	 }

	 @Override
	 protected void onResume() {
	     super.onResume();
	     mGLView.onResume();
	 }
	 
	 
	 private GLSurfaceView mGLView;
	
     static {
    	 System.loadLibrary("cocos2d");
         System.loadLibrary("helloworld");
     }
}
