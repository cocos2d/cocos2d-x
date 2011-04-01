package org.cocos2dx.lib;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;

public class Cocos2dxGLSurfaceView extends GLSurfaceView{
    private static final String TAG = Cocos2dxGLSurfaceView.class
            .getCanonicalName();
    private Cocos2dxRenderer mRenderer;
    private final boolean debug = false;

    public Cocos2dxGLSurfaceView(Context context) {
        super(context);
        mRenderer = new Cocos2dxRenderer();
        setFocusableInTouchMode(true);
        setRenderer(mRenderer);
    }

    public boolean onTouchEvent(final MotionEvent event) {
    	// these data are used in ACTION_MOVE and ACTION_CANCEL
    	final int pointerNumber = event.getPointerCount();
    	final int[] ids = new int[pointerNumber];
    	final float[] xs = new float[pointerNumber];
    	final float[] ys = new float[pointerNumber];

    	for (int i = 0; i < pointerNumber; i++) {
            ids[i] = event.getPointerId(i);
            xs[i] = event.getX(i);
            ys[i] = event.getY(i);                          
        }
        
        switch (event.getAction() & MotionEvent.ACTION_MASK) {
        case MotionEvent.ACTION_POINTER_DOWN:           	
        	final int idPointerDown = event.getAction() >> MotionEvent.ACTION_POINTER_ID_SHIFT;                        
            final float xPointerDown = event.getX(idPointerDown);
            final float yPointerDown = event.getY(idPointerDown);

            queueEvent(new Runnable() {
                @Override
                public void run() {
                    mRenderer.handleActionDown(idPointerDown, xPointerDown, yPointerDown);
                }
            });
            break;
            
        case MotionEvent.ACTION_DOWN:     
        	// there are only one finger on the screen
        	final int idDown = event.getPointerId(0);                            
            final float xDown = event.getX(idDown);
            final float yDown = event.getY(idDown);
            
            queueEvent(new Runnable() {
                @Override
                public void run() {
                    mRenderer.handleActionDown(idDown, xDown, yDown);
                }
            });
            break;

        case MotionEvent.ACTION_MOVE:                        
            queueEvent(new Runnable() {
                @Override
                public void run() {
                    mRenderer.handleActionMove(ids, xs, ys);
                }
            });
            break;

        case MotionEvent.ACTION_POINTER_UP:           	            	
        	final int idPointerUp = event.getAction() >> MotionEvent.ACTION_POINTER_ID_SHIFT;                        
            final float xPointerUp = event.getX(idPointerUp);
            final float yPointerUp = event.getY(idPointerUp);
            
            queueEvent(new Runnable() {
                @Override
                public void run() {
                    mRenderer.handleActionUp(idPointerUp, xPointerUp, yPointerUp);
                }
            });
            break;
            
        case MotionEvent.ACTION_UP:  
        	// there are only one finger on the screen
        	final int idUp = event.getPointerId(0);
            final float xUp = event.getX(idUp);
            final float yUp = event.getY(idUp);
            
            queueEvent(new Runnable() {
                @Override
                public void run() {
                    mRenderer.handleActionUp(idUp, xUp, yUp);
                }
            });
            break;

        case MotionEvent.ACTION_CANCEL:
            queueEvent(new Runnable() {
               @Override
                public void run() {
                    mRenderer.handleActionCancel(ids, xs, ys);
                }
            });
            break;
        }
      
        if (debug){
        	dumpEvent(event);
        }
        return true;
    }
    
 @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
    	final int kc = keyCode;
    	if (keyCode == KeyEvent.KEYCODE_BACK || keyCode == KeyEvent.KEYCODE_MENU) {
    		queueEvent(new Runnable() {
	            @Override
	            public void run() {
	                mRenderer.handleKeyDown(kc);
	            }
    		});
    		return true;
    	}
        return super.onKeyDown(keyCode, event);
    }
    // Show an event in the LogCat view, for debugging
    private void dumpEvent(MotionEvent event) {
       String names[] = { "DOWN" , "UP" , "MOVE" , "CANCEL" , "OUTSIDE" ,
          "POINTER_DOWN" , "POINTER_UP" , "7?" , "8?" , "9?" };
       StringBuilder sb = new StringBuilder();
       int action = event.getAction();
       int actionCode = action & MotionEvent.ACTION_MASK;
       sb.append("event ACTION_" ).append(names[actionCode]);
       if (actionCode == MotionEvent.ACTION_POINTER_DOWN
             || actionCode == MotionEvent.ACTION_POINTER_UP) {
          sb.append("(pid " ).append(
          action >> MotionEvent.ACTION_POINTER_ID_SHIFT);
          sb.append(")" );
       }
       sb.append("[" );
       for (int i = 0; i < event.getPointerCount(); i++) {
          sb.append("#" ).append(i);
          sb.append("(pid " ).append(event.getPointerId(i));
          sb.append(")=" ).append((int) event.getX(i));
          sb.append("," ).append((int) event.getY(i));
          if (i + 1 < event.getPointerCount())
             sb.append(";" );
       }
       sb.append("]" );
       Log.d(TAG, sb.toString());
    }
}
