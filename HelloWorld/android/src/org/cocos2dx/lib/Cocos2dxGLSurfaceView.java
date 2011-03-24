package org.cocos2dx.lib;

import org.cocos2dx.lib.touch.metalev.multitouch.controller.MultiTouchController;
import org.cocos2dx.lib.touch.metalev.multitouch.controller.MultiTouchController.MultiTouchObjectCanvas;
import org.cocos2dx.lib.touch.metalev.multitouch.controller.MultiTouchController.PointInfo;
import org.cocos2dx.lib.touch.metalev.multitouch.controller.MultiTouchController.PositionAndScale;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.MotionEvent;

public class Cocos2dxGLSurfaceView extends GLSurfaceView implements
        MultiTouchObjectCanvas {
    private static final String TAG = Cocos2dxGLSurfaceView.class
            .getCanonicalName();
    private MultiTouchController<Void> mTouchController;
    private Cocos2dxRenderer mRenderer;

    public Cocos2dxGLSurfaceView(Context context) {
        super(context);
        mRenderer = new Cocos2dxRenderer();
        setRenderer(mRenderer);

        mTouchController = new MultiTouchController<Void>(this);
    }

    public boolean onTouchEvent(final MotionEvent event) {
        if (mTouchController.onTouchEvent(event)) {
            final PointInfo pt = mTouchController.mCurrPt;
            final int ids[] = new int[pt.getNumTouchPoints()];
            final float xs[] = new float[pt.getNumTouchPoints()];
            final float ys[] = new float[pt.getNumTouchPoints()];

            for (int i = 0; i < pt.getNumTouchPoints(); i++) {
                ids[i] = pt.getPointerIds()[i];
                xs[i] = pt.getXs()[i];
                ys[i] = pt.getYs()[i];
                Log.d(TAG,
                        "ACTION: " + pt.getAction() + "id[i]="
                                + pt.getPointerIds()[i] + "x[i]= "
                                + pt.getXs()[i] + " y[i]= " + pt.getYs()[i]);               
            }
            
            switch (pt.getAction()) {
            case MotionEvent.ACTION_DOWN:
            case 261:
            case MotionEvent.ACTION_POINTER_DOWN:
                Log.d(TAG, "ACTION_DOWN");
                queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        mRenderer.handleActionDown(ids, xs, ys);
                    }
                });
                break;

            case MotionEvent.ACTION_MOVE:
                Log.d(TAG, "ACTION_MOVE");
                queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        mRenderer.handleActionMove(ids, xs, ys);
                    }
                });
                break;

            case MotionEvent.ACTION_UP:
            case MotionEvent.ACTION_POINTER_UP:
                Log.d(TAG, "ACTION_UP");
                queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        mRenderer.handleActionUp(ids, xs, ys);
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
            
            return true;
        }
        return false;
    }

    @Override
    public Object getDraggableObjectAtPoint(PointInfo touchPoint) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public void getPositionAndScale(Object obj,
            PositionAndScale objPosAndScaleOut) {
        // TODO Auto-generated method stub

    }

    @Override
    public boolean setPositionAndScale(Object obj,
            PositionAndScale newObjPosAndScale, PointInfo touchPoint) {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public void selectObject(Object obj, PointInfo touchPoint) {
        // TODO Auto-generated method stub

    }
}
