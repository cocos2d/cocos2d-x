package org.cocos2dx.lib;

import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.MotionEvent;

public class Cocos2dxGLSurfaceView extends GLSurfaceView {
    public Cocos2dxGLSurfaceView(Context context) {
        super(context);
        mRenderer = new Cocos2dxRenderer();
        mRenderer.setApkPath(getApkPath(context));
        setRenderer(mRenderer);
    }

    private String getApkPath(Context ctx) {
    	PackageManager pm = ctx.getPackageManager();
		ApplicationInfo ai = null;

		try {
			ai = pm.getApplicationInfo(ctx.getPackageName(), 0);
		} catch (NameNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return ai.sourceDir;
	}

	public boolean onTouchEvent(final MotionEvent event) {
    	boolean result = false;
    	final float x = event.getX();
    	final float y = event.getY();
    	
        switch (event.getAction()){
        case MotionEvent.ACTION_DOWN:  
        	queueEvent(new Runnable() {
                // This method will be called on the rendering thread
                public void run() {
                	mRenderer.handleActionDown(x, y);
            }});

        	result = true;
        	break;
        case MotionEvent.ACTION_UP:
        	queueEvent(new Runnable() {
                // This method will be called on the rendering thread
                public void run() {
                	mRenderer.handleActionUp(x, y);
            }});

        	result = true;
        	break;
        case MotionEvent.ACTION_CANCEL:
        	queueEvent(new Runnable() {
                // This method will be called on the rendering thread
                public void run() {
                	mRenderer.handleActionCancel(x, y);
            }});
        	
        	result = true;
        	break;
        case MotionEvent.ACTION_MOVE:
        	queueEvent(new Runnable() {
                // This method will be called on the rendering thread
                public void run() {
                	mRenderer.handleActionMove(x, y);
            }});
        	
        	result = true;
        	break;
        }
        
        return result;
    }

    Cocos2dxRenderer mRenderer;
}
