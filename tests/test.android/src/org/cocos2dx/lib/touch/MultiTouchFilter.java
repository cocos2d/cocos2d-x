package org.cocos2dx.lib.touch;

import java.util.ArrayList;

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

        ArrayList<Touch> tDown = null;
        ArrayList<Touch> tUp = null;
        ArrayList<Touch> tMove = null;
        ArrayList<Touch> tCancel = null;

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
                if ( null == tDown ) {
                    tDown = new ArrayList<MultiTouchFilter.Touch>(2);
                }

                tDown.add(new Touch(id, x, y));
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
                if ( null == tUp ) {
                    tUp = new ArrayList<MultiTouchFilter.Touch>(2);
                }

                tUp.add(new Touch(id, x, y));
                break;

            case MotionEvent.ACTION_CANCEL:
                if ( null == tCancel ) {
                    tCancel = new ArrayList<MultiTouchFilter.Touch>(2);
                }

                tCancel.add(new Touch(id, x, y));
                break;

            case MotionEvent.ACTION_MOVE:
                if ( null == tMove ) {
                    tMove = new ArrayList<MultiTouchFilter.Touch>(2);
                }

                tMove.add(new Touch(id, x, y));
                break;

            }
        }

        final TouchArrays arrays;
        if ( tDown != null ) {
            arrays = getArrays(tDown);
            mView.queueEvent(new Runnable() {
                public void run() {
                    mRenderer.handleActionDown(arrays.ids, arrays.xs, arrays.ys);
            }});

        } else if ( tMove != null ) {
            arrays = getArrays(tMove);
            mView.queueEvent(new Runnable() {
                public void run() {
                    mRenderer.handleActionMove(arrays.ids, arrays.xs, arrays.ys);
                }});

        } else if ( tUp != null ) {
            arrays = getArrays(tUp);
            mView.queueEvent(new Runnable() {
                public void run() {
                    mRenderer.handleActionUp(arrays.ids, arrays.xs, arrays.ys);
                }});

        } else if ( tCancel != null ) {
            arrays = getArrays(tCancel);
            mView.queueEvent(new Runnable() {
                public void run() {
                    mRenderer.handleActionCancel(arrays.ids, arrays.xs, arrays.ys);
                }});
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

    private TouchArrays getArrays(ArrayList<Touch> touches) {
        TouchArrays ret = new TouchArrays(touches.size());

        for ( int i=0 ; i < touches.size() ; i++ ) {
            ret.ids[i] = touches.get(i).id;
            ret.xs[i] = touches.get(i).x;
            ret.ys[i] = touches.get(i).y;
        }

        return ret;
    }

    private class TouchArrays {
        public int[] ids;
        public float[] xs;
        public float[] ys;

        public TouchArrays(int size) {
            ids = new int[size];
            xs = new float[size];
            ys = new float[size];
        }
    }

    private class Touch {
        public int id;
        public float x;
        public float y;

        public Touch(int id, float x, float y) {
            this.id = id;
            this.x = x;
            this.y = y;
        }
    }
}
