package org.cocos2dx.lib.touch;

import org.cocos2dx.lib.Cocos2dxRenderer;

import android.content.Context;
import android.content.pm.PackageManager;
import android.view.MotionEvent;

public class MultiTouchFilter extends TouchFilter {

    private boolean mCheckedForMultitouch = false;
    private boolean mSupportsMultitouch = false;
    private Cocos2dxRenderer mRenderer;

    public MultiTouchFilter(Cocos2dxRenderer renderer) {
        mRenderer = renderer;
    }

    @Override
    public boolean updateTouch(MotionEvent event) {

        boolean ret = false;

        final int pointerCount = event.getPointerCount();
        for (int i = 0; i < pointerCount; i++) {

            final int action = event.getAction();
            final int id = event.getPointerId(i);
            final int actualEvent = action & MotionEvent.ACTION_MASK;
            final float x = event.getX(i);
            final float y = event.getY(i);

            switch (actualEvent) {
            case MotionEvent.ACTION_DOWN:
                mRenderer.handleActionDown(id, x, y);
                ret = true;
                break;

            case MotionEvent.ACTION_UP:
                mRenderer.handleActionUp(id, x, y);
                ret = true;
                break;

            case MotionEvent.ACTION_CANCEL:
                mRenderer.handleActionCancel(id, x, y);
                ret = true;
                break;

            case MotionEvent.ACTION_MOVE:
                mRenderer.handleActionMove(id, x, y);
                ret = true;
                break;

            }
        }

        return ret;
    }

    @Override
    public boolean supportsMultitouch(Context context) {
        if (!mCheckedForMultitouch) {
            PackageManager packageManager = context.getPackageManager();
            mSupportsMultitouch = packageManager.hasSystemFeature("android.hardware.touchscreen.multitouch");
            mCheckedForMultitouch = true;
        }
        
        return mSupportsMultitouch;
    }

}
