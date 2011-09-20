package org.my;
import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.KeyEvent;

public class LuaProjectTemplate extends Cocos2dxActivity{
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		
		// get the packageName,it's used to set the resource path
		String packageName = getApplication().getPackageName();
		super.setPackageName(packageName);
		
        mGLView = new LuaGLSurfaceView(this);
        setContentView(mGLView);

        // Get the size of the mGLView after the layout happens
        mGLView.post(new Runnable() {
            
            @Override
            public void run() {
                Cocos2dxActivity.screenHeight = mGLView.getHeight();
                Cocos2dxActivity.screenWidth = mGLView.getWidth();
            }
        });
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
         System.loadLibrary("cocosdenshion");
         System.loadLibrary("lua");
         System.loadLibrary("game");
     }
}

class LuaGLSurfaceView extends Cocos2dxGLSurfaceView{
	
	public LuaGLSurfaceView(Context context){
		super(context);
	}
	
	public boolean onKeyDown(int keyCode, KeyEvent event) {
    	// exit program when key back is entered
    	if (keyCode == KeyEvent.KEYCODE_BACK) {
    		android.os.Process.killProcess(android.os.Process.myPid());
    	}
        return super.onKeyDown(keyCode, event);
    }
}
