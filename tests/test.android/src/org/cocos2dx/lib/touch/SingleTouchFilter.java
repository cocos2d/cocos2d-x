package org.cocos2dx.lib.touch;

import org.cocos2dx.lib.Cocos2dxRenderer;

import android.view.MotionEvent;

public class SingleTouchFilter extends TouchFilter {

    private Cocos2dxRenderer mRenderer;

    public SingleTouchFilter(Cocos2dxRenderer renderer) {
        mRenderer = renderer;
    }

    @Override
    public boolean updateTouch(MotionEvent event) {
        final float x = event.getX();
        final float y = event.getY();
        final int id = 0;

        switch (event.getAction()) {
        case MotionEvent.ACTION_DOWN:
            mRenderer.handleActionDown(id, x, y);
            return true;

        case MotionEvent.ACTION_UP:
            mRenderer.handleActionUp(id, x, y);
            return true;

        case MotionEvent.ACTION_CANCEL:
            mRenderer.handleActionCancel(id, x, y);
            return true;

        case MotionEvent.ACTION_MOVE:
            mRenderer.handleActionMove(id, x, y);
            return true;

        }

        return false;
    }

}
