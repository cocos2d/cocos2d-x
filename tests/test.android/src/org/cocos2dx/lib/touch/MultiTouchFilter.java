package org.cocos2dx.lib.touch;

import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.cocos2dx.lib.Cocos2dxRenderer;

import android.content.Context;
import android.content.pm.PackageManager;
import android.view.MotionEvent;

public class MultiTouchFilter extends TouchFilter {

    private boolean mCheckedForMultitouch = false;
    private boolean mSupportsMultitouch = false;
    private Cocos2dxRenderer mRenderer;
    private Cocos2dxGLSurfaceView mView;

    public MultiTouchFilter(Cocos2dxGLSurfaceView cocos2dxGLSurfaceView,
            Cocos2dxRenderer renderer) {
        mRenderer = renderer;
        mView = cocos2dxGLSurfaceView;
    }

    @Override
    public boolean updateTouch(MotionEvent event) {

        final MotionEvent mEvent = event;
        parseTouch(mEvent);

        return true;
    }

    private void parseTouch(MotionEvent event) {

        final int pointerCount = event.getPointerCount();
        for (int i = 0; i < pointerCount; i++) {
            final int action = event.getAction();
            final int id = event.getPointerId(i);
            final int actualEvent = action & MotionEvent.ACTION_MASK;
            final float x = event.getX(i);
            final float y = event.getY(i);

            // Used for ACTION_POINTER_*
            final int pointerIndex;
            final int pointerId;

            switch (actualEvent) {

            case MotionEvent.ACTION_POINTER_DOWN:
                pointerIndex = (action & MotionEvent.ACTION_POINTER_INDEX_MASK) >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;
                pointerId = event.getPointerId(pointerIndex);

                /*
                 * Just send one handleActionDown event if there are two
                 * pointers
                 */
                if (id != pointerId) {
                    break;
                }

            case MotionEvent.ACTION_DOWN:
                mRenderer.handleActionDown(id, x, y);
                break;

            case MotionEvent.ACTION_POINTER_UP:
                pointerIndex = (action & MotionEvent.ACTION_POINTER_INDEX_MASK) >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;
                pointerId = event.getPointerId(pointerIndex);

                /*
                 * Just send one handleActionUp event if there are two pointers
                 */
                if (id != pointerId) {
                    break;
                }
            case MotionEvent.ACTION_UP:
                mRenderer.handleActionUp(id, x, y);
                break;

            case MotionEvent.ACTION_CANCEL:
                mRenderer.handleActionCancel(id, x, y);
                break;

            case MotionEvent.ACTION_MOVE:
                mRenderer.handleActionMove(id, x, y);
                break;

            }
        }
    }

    @Override
    public boolean supportsMultitouch(Context context) {
        if (!mCheckedForMultitouch) {
            PackageManager packageManager = context.getPackageManager();
            mSupportsMultitouch = packageManager
                    .hasSystemFeature("android.hardware.touchscreen.multitouch");
            mCheckedForMultitouch = true;
        }

        return mSupportsMultitouch;
    }

}
