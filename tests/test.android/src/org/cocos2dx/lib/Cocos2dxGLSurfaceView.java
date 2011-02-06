package org.cocos2dx.lib;

import org.cocos2dx.lib.touch.MultiTouchFilter;
import org.cocos2dx.lib.touch.SingleTouchFilter;
import org.cocos2dx.lib.touch.TouchFilter;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.util.Log;
import android.view.MotionEvent;

public class Cocos2dxGLSurfaceView extends GLSurfaceView {
    private static final String TAG = "Cocos2dxGLSurfaceView";
    private TouchFilter mTouchFilter;
    private Cocos2dxRenderer mRenderer;

    public Cocos2dxGLSurfaceView(Context context) {
        super(context);
        mRenderer = new Cocos2dxRenderer();
        setRenderer(mRenderer);

        final int sdkVersion = Integer.parseInt(Build.VERSION.SDK);
        if (sdkVersion < Build.VERSION_CODES.ECLAIR) {
            mTouchFilter = new SingleTouchFilter(mRenderer);
            Log.i(TAG, "using SingleTouchFilter");
        } else {
            mTouchFilter = new MultiTouchFilter(mRenderer);
            Log.i(TAG, "using MultiTouchFilter");
        }
    }

    public boolean onTouchEvent(final MotionEvent event) {
    	return mTouchFilter.updateTouch(event);
    }
}
