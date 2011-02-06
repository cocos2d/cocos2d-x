package org.cocos2dx.lib.touch;

import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.cocos2dx.lib.Cocos2dxRenderer;

import android.view.MotionEvent;

public class SingleTouchFilter extends TouchFilter {

    private Cocos2dxRenderer mRenderer;
    private Cocos2dxGLSurfaceView mView;

    public SingleTouchFilter(Cocos2dxGLSurfaceView cocos2dxGLSurfaceView, Cocos2dxRenderer renderer) {
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
        final float x = event.getX();
        final float y = event.getY();
        final int id = 0;

        switch (event.getAction()) {
        case MotionEvent.ACTION_DOWN:
            mRenderer.handleActionDown(id, x, y);

        case MotionEvent.ACTION_UP:
            mRenderer.handleActionUp(id, x, y);

        case MotionEvent.ACTION_CANCEL:
            mRenderer.handleActionCancel(id, x, y);

        case MotionEvent.ACTION_MOVE:
            mRenderer.handleActionMove(id, x, y);
        }
    }
}
