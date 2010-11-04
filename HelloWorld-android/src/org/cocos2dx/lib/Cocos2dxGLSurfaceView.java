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
    	float x = event.getX() * event.getXPrecision();
    	float y = event.getY() * event.getYPrecision();
    	
        switch (event.getAction()){
        case MotionEvent.ACTION_DOWN:       	
        	nativeTouchesBegin(x, y);
        	result = true;
        	break;
        case MotionEvent.ACTION_UP:
        	nativeTouchesEnd(x, y);
        	result = true;
        	break;
        case MotionEvent.ACTION_CANCEL:
        	nativeTouchesCancel(x, y);
        	result = true;
        	break;
        case MotionEvent.ACTION_MOVE:
        	nativeTouchesMove(x, y);
        	result = true;
        	break;
        }
        
        return result;
    }

    Cocos2dxRenderer mRenderer;
    private static native void nativeTouchesBegin(float x, float y);
    private static native void nativeTouchesEnd(float x, float y);
    private static native void nativeTouchesMove(float x, float y);
    private static native void nativeTouchesCancel(float x, float y);
}
