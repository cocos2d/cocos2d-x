package org.cocos2dx.spritetest;
import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.cocos2dx.spritetest.R;


import android.opengl.GLSurfaceView;
import android.os.Bundle;

public class PerformanceSpriteTest extends Cocos2dxActivity{
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		
		// get the packageName,it's used to set the resource path
		String packageName = getApplication().getPackageName();
		super.setPackgeName(packageName);
		
		setContentView(R.layout.game_demo);
        mGLView = (Cocos2dxGLSurfaceView) findViewById(R.id.game_gl_surfaceview);

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
         System.loadLibrary("game");
     }
}
