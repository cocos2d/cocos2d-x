package org.cocos2dx.lib;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

public class Cocos2dxGLSurfaceView extends GLSurfaceView {
    public Cocos2dxGLSurfaceView(Context context) {
        super(context);
        mRenderer = new Cocos2dxRenderer();
        setRenderer(mRenderer);
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
